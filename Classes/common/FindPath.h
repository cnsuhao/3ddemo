#ifndef FindPath_h__
#define FindPath_h__

#include "CocosHead.h"

const int zhi_step = 10;
const int xie_step = 14;

class PathNode;

typedef PathNode* ptr_PathNode;

class PathNode:public Ref
{
public:

	static PathNode* create(int x, int y)
	{
		PathNode* node = new PathNode(x, y);
		if (node)
		{
			node->autorelease();
		}

		return node;
	}

	PathNode(int x, int y):m_x(x),m_y(y)
	{
		m_g = m_h = m_f = 0;
		parent = nullptr;
		next = nullptr;
	};
	// 位置
	int m_x, m_y;
	// 权重
	int m_g, m_h, m_f;

	// 父节点
	ptr_PathNode parent;
	// 子节点
	ptr_PathNode next;
	// 计算G值-------到起点的花费
	int calculateG(ptr_PathNode node)
	{
		return ((abs(this->m_x - node->m_x) + abs(this->m_y - node->m_y)) == 2 ? xie_step : zhi_step) + node->m_g;
	}
	// 计算H值-------到终点的花费
	int calculateH(ptr_PathNode node)
	{
		return (abs(this->m_x - node->m_x) + abs(this->m_y - node->m_y)) * zhi_step;
	}
	// 计算F值
	void calculateF()
	{
		this->m_f = this->m_g + this->m_h;
	}

	void setG(int g){ m_g = g; }

	void setH(int h){ m_h = h; }

	void setParent(ptr_PathNode node){ parent = node; }

	void setNext(ptr_PathNode node){ next = node; }

	ptr_PathNode nextNode()
	{
		ptr_PathNode node = next;
		this->release();
		return node;
	}

	void clear()
	{
		ptr_PathNode node = this;
		do 
		{
			ptr_PathNode next = node->next;
			node->release();
			node = next;
		} while (node);
	}
};


class FindPath
{
public:
	// 找路
	static ptr_PathNode getPath(int begin_x, int begin_y, int end_x, int end_y, bool isPixel = false);
private:
	// 是否在开集
	static bool isExistInOpenList(ptr_PathNode node);
	// 是否在闭集
	static bool isExistInCloseList(ptr_PathNode node);
	// 添加入闭集
	static void addInCloseList(ptr_PathNode node);
	// 添加入开集
	static void addInOpenList(ptr_PathNode node);
	// 按照F值排序
	static ptr_PathNode getMinFNodeOpenList();
	// 删除最小F节点
	static void eraseMinNodeInOpenList();
	// 获取周围点
	static std::list<ptr_PathNode> getSourndNodeList(ptr_PathNode node);
	// 查找结束
	static ptr_PathNode isFindEndNodeInOpenList(ptr_PathNode node);
	// 清空
	static void clearList();
	// 是否直线
	static bool isLine(ptr_PathNode node1, ptr_PathNode node2, ptr_PathNode node3);
	// 开集
	static std::list<ptr_PathNode> m_openList;
	// 闭集
	static std::list<ptr_PathNode> m_closeList;
	// 
	static std::list<ptr_PathNode> m_sourndList;
};

#endif // FindPath_h__
