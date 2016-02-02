#include "FindPath.h"
#include "GameMap.h"


// 开集
std::list<ptr_PathNode> FindPath::m_openList;
// 闭集
std::list<ptr_PathNode> FindPath::m_closeList;
// 
std::list<ptr_PathNode> FindPath::m_sourndList;



ptr_PathNode FindPath::getPath(int begin_x, int begin_y, int end_x, int end_y, bool isPixel)
{
	if (!GameMap::getInstance()->canMove(end_x, end_y))
	{
		return nullptr;
	}
	CCLOG("FindPath::getPath1");
	// 先清除下
	FindPath::clearList();

	ptr_PathNode resNode = nullptr;
	// 起点
	ptr_PathNode beginNode = ptr_PathNode(PathNode::create(begin_x, begin_y));
	// 终点
	ptr_PathNode endNode = ptr_PathNode(PathNode::create(end_x, end_y));

	// 先把起点放入开集
	FindPath::addInOpenList(beginNode);

	while (m_openList.empty() == false)
	{
		// 获取最小F的节点
		ptr_PathNode curNode = FindPath::getMinFNodeOpenList();
		// 删除此节点
		FindPath::eraseMinNodeInOpenList();
		// 放入闭集
		FindPath::addInCloseList(curNode);
		// 获取周围节点
		std::list<ptr_PathNode> nodelist = FindPath::getSourndNodeList(curNode);
		for (ptr_PathNode node : nodelist)
		{
			// 如果存在于开集中
			if (FindPath::isExistInOpenList(node) == true)
			{
				// 计算G值进行比较，如果新的G值大于与原来的，不处理；否则将当前节点设置为父节点，替换新的G值
				int g = node->calculateG(curNode);
				if (g < node->m_g)
				{
					node->setG(g);
					node->calculateF();
					node->setParent(curNode);
				}
			}
			else
			{
			// 否则直接加入开集中
				int g = node->calculateG(curNode);
				int h = node->calculateH(endNode);
				node->setG(g);
				node->setH(h);
				node->calculateF();
				node->setParent(curNode);
				FindPath::addInOpenList(node);
			}
		}
		// 如果终点出现在开集中，寻路结束
		resNode = FindPath::isFindEndNodeInOpenList(endNode);
		if (resNode)
		{
			break;
		}
	}

	CCLOG("FindPath::getPath2");
	// 逆序
	if (resNode)
	{
		resNode->retain();
		while (resNode->parent)
		{
			auto parentNode = resNode->parent;
			if (parentNode)
			{
				parentNode->setNext(resNode);
			}
			resNode = parentNode;
			resNode->retain();
			CCLOG("share_ptr usecount %d",resNode->getReferenceCount());
		}
		// 直线去重
		if (isPixel)
		{
			ptr_PathNode node = resNode;
			ptr_PathNode node1 = nullptr;
			ptr_PathNode node2 = nullptr;
			ptr_PathNode node3 = nullptr;
			while (node)
			{
				node1 = node;
				node2 = node->next;
				if (node2)
				{
					node3 = node2->next;
				}
				if (isLine(node1, node2, node3))
				{
					node1->setNext(node3);
					node3->setParent(node1);
					node2->release();
				}
				else
				{
					node = node2;
				}
			}
		}
	}
	CCLOG("FindPath::getPath3");
	return resNode;
}

bool FindPath::isExistInOpenList(ptr_PathNode node)
{
	// 注意比较的是X,Y
	struct Condition
	{
		Condition(ptr_PathNode p) :m_node(p){}

		bool operator()(ptr_PathNode ptr)
		{
			if (m_node->m_x == ptr->m_x && m_node->m_y == ptr->m_y)
			{
				return true;
			}
			return false;
		}
		ptr_PathNode m_node;
	};
	return (std::find_if(m_openList.begin(), m_openList.end(), Condition(node))) != m_openList.end();
}

bool FindPath::isExistInCloseList(ptr_PathNode node)
{
	// 注意比较的是X,Y
	struct Condition
	{
		Condition(ptr_PathNode p) :m_node(p){}

		bool operator()(const ptr_PathNode& ptr)
		{
			if (m_node->m_x == ptr->m_x && m_node->m_y == ptr->m_y)
			{
				return true;
			}
			return false;
		}
		ptr_PathNode m_node;
	};

	return std::find_if(m_closeList.begin(), m_closeList.end(), Condition(node)) != m_closeList.end();
}

void FindPath::addInCloseList(ptr_PathNode node)
{
	m_closeList.push_back(node);
}

void FindPath::addInOpenList(ptr_PathNode node)
{
	m_openList.push_back(node);
}

ptr_PathNode FindPath::getMinFNodeOpenList()
{
	// 按照F的大小排序
	struct Condition
	{
		bool operator()(const ptr_PathNode& lf,const ptr_PathNode& rt)
		{
			if (lf->m_f < rt->m_f)
			{
				return true;
			}
			return false;
		}
		ptr_PathNode m_node;
	};

	m_openList.sort(Condition());

	return *(m_openList.begin());
}

void FindPath::eraseMinNodeInOpenList()
{
	auto iter = m_openList.begin();
	if (iter != m_openList.end())
	{
		m_openList.erase(iter);
	}
}

std::list<ptr_PathNode> FindPath::getSourndNodeList(ptr_PathNode node)
{
	m_sourndList.clear();
	for (int i = -1; i <= 1; ++i)
	{
		for (int j = -1; j <= 1; ++j)
		{
			int x = node->m_x + i;
			int y = node->m_y + j;
			if (GameMap::getInstance()->canMove(x, y))
			{
				ptr_PathNode s_node = ptr_PathNode(PathNode::create(x, y));
				if (FindPath::isExistInCloseList(s_node) == false)
				{
					m_sourndList.push_back(s_node);
				}
			}
		}
	}

	return m_sourndList;
}



ptr_PathNode FindPath::isFindEndNodeInOpenList(ptr_PathNode node)
{
	struct Condition
	{
		Condition(ptr_PathNode p) :m_node(p){}

		bool operator()(const ptr_PathNode& ptr)
		{
			if (m_node->m_x == ptr->m_x && m_node->m_y == ptr->m_y)
			{
				return true;
			}
			return false;
		}
		ptr_PathNode m_node;
	};

	auto findIter = std::find_if(m_closeList.begin(), m_closeList.end(), Condition(node));
	if (findIter != m_closeList.end())
	{
		return *findIter;
	}
	return nullptr;
}

void FindPath::clearList()
{
	m_openList.clear();
	m_closeList.clear();
	m_sourndList.clear();
}

bool FindPath::isLine(ptr_PathNode node1, ptr_PathNode node2, ptr_PathNode node3)
{
	if (node1 && node2 && node3)
	{
		return  (node2->m_x - node1->m_x) * (node3->m_y - node1->m_y) == (node3->m_x - node1->m_x) * (node2->m_y - node1->m_y);
	}
	return false;
}
