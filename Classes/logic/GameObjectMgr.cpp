#include "GameObjectMgr.h"
#include "ObjectDataMgr.h"
#include "ShaderMgr.h"
#include "GameAI.h"
#include "UISelTarget.h"
#include "UIManager.h"
#include "GameMap.h"
GameObjectMgr* GameObjectMgr::_sGameObjectMgr = nullptr;

GameObjectMgr::GameObjectMgr()
{

}

GameObjectMgr::~GameObjectMgr()
{
	
}

GameObjectMgr* GameObjectMgr::getInstance()
{
	if (!_sGameObjectMgr)
	{
		_sGameObjectMgr = new GameObjectMgr;
		_sGameObjectMgr->init();
	}
	return _sGameObjectMgr;
}

void GameObjectMgr::destroyInstance()
{
	if (_sGameObjectMgr)
	{
		_sGameObjectMgr->removeFromParent();
		CC_SAFE_RELEASE_NULL(_sGameObjectMgr);
	}
}

void GameObjectMgr::loadObjects()
{
	this->removeAllChildren();
	/*
	// 主玩家
	auto data = ObjectDataMgr::getInstance()->getMainObjectData();
	m_mainPlayer = GamePlayer::create(data);
	m_mainPlayer->setObjectType(ObjectType::mainplayer);
	m_mainPlayer->initHPBar();
	m_mainPlayer->initName();
	m_mainPlayer->refreshHPBar();
	this->addChild(m_mainPlayer);
	m_mainPlayer->setPositionForMap();
	m_mainPlayer->updateAnim();
	m_mainPlayer->setDoSkill(DoSkill::create(m_mainPlayer));
	*/
	// 其他玩家
	auto playlist = ObjectDataMgr::getInstance()->getPlayList();
	for (auto data: playlist)
	{
		GamePlayer* player = GamePlayer::create(data);
		player->setObjectType(ObjectType::otherplayer);
		player->initHPBar();
		player->initName();
		player->refreshHPBar();
		this->addChild(player);
		player->setPositionForMap();
		player->updateAnim();
		player->setDoSkill(DoSkill::create(player));
		m_otherPlayerList.push_back(player);
		GameAIInitiative* ai = GameAIInitiative::create();
		ai->setRect(data->m_rect);
		ai->setAttach(player);
		ai->addSelfListener();
		ai->runAI();
		int isFight = RandomHelper::random_int(1, 10);
		if (isFight > 8)
		{
			player->getDoSkill()->setIsAutoFight(true);
		}
	}
}

GamePlayer* GameObjectMgr::getMainGamePlayer()
{
	return m_mainPlayer;
}

bool GameObjectMgr::init()
{

	return true;
}

GameObject* GameObjectMgr::getNearGameObject(GameObject* obj)
{
	GameObject* nearObj = nullptr;
	float distance = -1;
	Point mypos = obj->getObjectData()->m_pos;
	for (auto it:m_otherPlayerList)
	{
		if (obj != it && it->getObjectData()->m_isLive)
		{
			float d = mypos.distance(it->getObjectData()->m_pos);
			if (distance < 0 || d < distance)
			{
				distance = d;
				nearObj = it;
			}
		}
	}

	return nearObj;
}

bool GameObjectMgr::clickGameObjec(Point pt)
{
	pt = m_mainPlayer->getParent()->convertToNodeSpace(pt);
	for (auto it:m_otherPlayerList)
	{
		Rect rc = it->getBoundingBox();
		if (it->getBoundingBox().containsPoint(pt))
		{
			m_mainPlayer->setTarget(it);
			return true;
		}
	}
	return false;
}

void GameObjectMgr::clearGameOjects()
{
	m_mainPlayer = nullptr;
	m_otherPlayerList.clear();
}


bool nodeComparisonLessObject(Node* n1, Node* n2)
{
	GameObject* obj1 = dynamic_cast<GameObject*>(n1);
	GameObject* obj2 = dynamic_cast<GameObject*>(n2);

	if (obj1 && obj2)
	{
		return  obj1->getTilePos().y < obj2->getTilePos().y;
	}
	
	return false;
}

void GameObjectMgr::sortAllChildren()
{
	if (_reorderChildDirty) {
		std::sort(std::begin(_children), std::end(_children), nodeComparisonLessObject);
		_reorderChildDirty = false;
	}
}

void GameObjectMgr::setReorderChildDirty(bool isRecorder)
{
	_reorderChildDirty = isRecorder;
}

bool GameObjectMgr::isExistGameObject(GameObject* obj, Point pt)
{
	if (m_mainPlayer != nullptr && m_mainPlayer != obj && m_mainPlayer->getTilePos() == pt)
	{
		return true;
	}
	for (auto object:m_otherPlayerList)
	{
		if (object != obj && object->getTilePos() == pt)
		{
			return true;
		}
	}
	return false;
}

void GameObjectMgr::mainPlayerGoToFarestChuanSongPT()
{
	Point pt = GameMap::getInstance()->getFarestChuanSongPoint();
	if (pt != Point::ZERO)
	{
		m_mainPlayer->moveTo(pt);
	}
}




