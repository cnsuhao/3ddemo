#include "GameAI.h"
#include "GameMap.h"
#include "UIManager.h"
#include "GameObjectMgr.h"
GameAIBase::GameAIBase() :Node(),
m_attach(nullptr),
m_dt(0.0f)
{
	m_state = AIState::nil;
	m_aiType = AITYPE::nil;
	m_rect	 = Rect::ZERO;
}

GameAIBase::~GameAIBase()
{

}

void GameAIBase::setAttach(GamePlayer* node)
{
	node->addChild(this);
	m_attach = node;
}

void GameAIBase::setRect(Rect rect)
{
	m_rect = rect;

	if (m_rect.size.width < 5)
	{
		m_rect.size.width = 5;
	}
	if (m_rect.size.height < 5)
	{
		m_rect.size.height = 5;
	}
}

void GameAIBase::runAI()
{
	this->schedule(schedule_selector(GameAIBase::updateAI),m_dt);
}

bool GameAIBase::init()
{
	return true;
}

GameAIInitiative::GameAIInitiative() :GameAIBase()
{
	m_dt = RandomHelper::random_int(5,20);
	m_state = AIState::move;
}

GameAIInitiative::~GameAIInitiative()
{

}

void GameAIInitiative::updateAI(float dt)
{
	ActMotion actState = m_attach->getActState();
	ObjectData* data = m_attach->getObjectData();
	if (data->m_isLive && m_state == AIState::move && m_attach->getDoSkill()->getIsAutoFight() == false)
	{
		if (actState == ActMotion::stand)
		{
			Point pt = getRandomPointInRect(m_rect);
			m_attach->moveTo(pt);
		}
	}
}

GameAIInitiative* GameAIInitiative::create()
{
	GameAIInitiative* ai = new GameAIInitiative;
	if (ai)
	{
		ai->autorelease();
	}

	return ai;
}

void GameAIInitiative::attack(GameObject* obj)
{
	m_attach->setTarget(obj);
	m_attach->getDoSkill()->setIsAutoFight(true);
}

void GameAIInitiative::addSelfListener()
{
	if (m_attach)
	{
		m_attach->getLogicDispatcher()->addGameEventListener(HPChangeEvent_ID, CC_CALLBACK_2(GameAIInitiative::onSelfHPChangeEvent, this), this);
	}
}

void GameAIInitiative::onSelfHPChangeEvent(Ref* pSender, GameEvent* gEvent)
{
	GameObject* obj = dynamic_cast<GameObject*>(pSender);
	ObjectData* data = m_attach->getObjectData();
	if (data->m_isLive && obj)
	{
		m_attach->setTarget(obj);
		m_attach->getDoSkill()->setIsAutoFight(true);
	}
}


DoSkill* DoSkill::create(GamePlayer* obj)
{
	DoSkill* doSkill = new DoSkill;
	if (doSkill)
	{
		doSkill->init(obj);
		doSkill->autorelease();
	}
	return doSkill;
}

bool DoSkill::init(GamePlayer* obj)
{
	Node::init();
	m_isReleaseSkill = false;
	m_isAutoFight = false;
	m_isFindTarget = false;
	m_skilId = 0;
	m_distance = 0;
	m_gamePlayer = obj;
	m_gamePlayer->addChild(this);
	m_gamePlayer->getLogicDispatcher()->addGameEventListener((int)GameEventId::sel_target, CC_CALLBACK_2(DoSkill::onSelTargetEvent, this), this);
	m_gamePlayer->getLogicDispatcher()->addGameEventListener((int)GameEventId::update_pos, CC_CALLBACK_2(DoSkill::onUpdateMyPosEvent, this), this);
	return true;
}

void DoSkill::doSkillById(int id)
{
	m_skilId = id;

	GameObject* target = m_gamePlayer->getTarget();
	// 没有目标直接放
	if (!target)
	{
		releaseSkill();
	}
	else
	{
		// 有目标先找目标
		m_distance = 1;
		SkillInfo info = GameAtlasMgr::getInstance()->getSkillInfoById(m_skilId);
		if (info.isValid)
		{
			m_distance = info.distance;
		}

		Point mypos = m_gamePlayer->getTilePos();
		Point targetpos = target->getTilePos();
		float distance = mypos.distance(targetpos);
		if (distance < m_distance * 1.42)
		{
			Size mapSize = GameMap::getInstance()->getMapSize();
			mypos.y = mapSize.height - mypos.y;
			targetpos.y = mapSize.height - targetpos.y;
			ActDir dir = getDirByPoint(mypos, targetpos);
			//m_gamePlayer->setDirAndAnimState(dir, ActMotion::stand);
			m_gamePlayer->setDirNoUpdate(dir);
			m_isFindTarget = false;
			releaseSkill();
		}
		else
		{
			target->getLogicDispatcher()->removeGameEventListener(this);
			target->getLogicDispatcher()->addGameEventListener((int)GameEventId::update_pos, CC_CALLBACK_2(DoSkill::onUpdateTargetPosEvent, this), this);
			m_isFindTarget = true;
			m_gamePlayer->moveTo(targetpos);
		}
	}
}

void DoSkill::onUpdateMyPosEvent(Ref* pSender, GameEvent* gEvent)
{
	//取距离
	GameObject* target = m_gamePlayer->getTarget();
	if (target && m_isFindTarget)
	{
		Point mypos = m_gamePlayer->getTilePos();
		Point targetpos = target->getTilePos();
		float distance = mypos.distance(targetpos);
		if (distance < m_distance * 1.42)
		{
			Size mapSize = GameMap::getInstance()->getMapSize();
			mypos.y = mapSize.height - mypos.y;
			targetpos.y = mapSize.height -targetpos.y;
			ActDir dir = getDirByPoint(mypos, targetpos);
			//m_gamePlayer->setDirAndAnimState(dir, ActMotion::stand);
			m_gamePlayer->setDirNoUpdate(dir);
			m_isFindTarget = false;
			releaseSkill();
		}
	}
}

void DoSkill::onUpdateTargetPosEvent(Ref* pSender, GameEvent* gEvent)
{
	GameObject* target = m_gamePlayer->getTarget();
	if (target && m_isFindTarget)
	{
		Point mypos = m_gamePlayer->getTilePos();
		Point targetpos = target->getTilePos();
		float distance = mypos.distance(targetpos);
		if (distance < m_distance * 1.42)
		{
			Size mapSize = GameMap::getInstance()->getMapSize();
			mypos.y = mapSize.height - mypos.y;
			targetpos.y = mapSize.height - targetpos.y;
			ActDir dir = getDirByPoint(mypos, targetpos);
			//m_gamePlayer->setDirAndAnimState(dir, ActMotion::stand);

			m_gamePlayer->setDirNoUpdate(dir);
			m_isFindTarget = false;
			releaseSkill();
		}
		else
		{
			m_gamePlayer->moveTo(targetpos);
		}
	}
}

void DoSkill::setIsAutoFight(bool isAuto)
{
	if (m_isAutoFight == isAuto)
	{
		return;
	}

	m_isAutoFight = isAuto;
	if (m_isAutoFight)
	{
		GameObject* target = m_gamePlayer->getTarget();
		if (target == nullptr)
		{
			target = GameObjectMgr::getInstance()->getNearGameObject(m_gamePlayer);
			m_gamePlayer->setTarget(target);
		}
		doSkillById(getCanUseSkillId());
	}
	else
	{
		m_isReleaseSkill = false;
		m_isFindTarget = false;
		m_gamePlayer->stop();
	}

	if (m_gamePlayer->getObjectType() == ObjectType::mainplayer)
	{
		GameEvent* gEvent = GameEvent::create(GameEventId::update_autostate);
		if (m_isAutoFight)
		{
			gEvent->setParamInt1(1);
		}
		else
		{
			gEvent->setParamInt1(0);
		}
		UIManager::getInstance()->getDispatcher()->dispatcherGameEvent(gEvent, this);
	}
}

int DoSkill::getCanUseSkillId()
{
	int skill[3][4] =
	{
		0, 1, 3, 9,
		0,10, 5, 8,
		0, 7, 11, 12,
	};

	int job = m_gamePlayer->getObjectData()->m_job;
	int index = RandomHelper::random_int(1, 3);

	return skill[job - 1][index];
}

void DoSkill::releaseSkill()
{
	m_gamePlayer->doSkillById(m_skilId, CC_CALLBACK_1(DoSkill::afterReleaseSkill, this));
}

void DoSkill::afterReleaseSkill(Ref* pSender)
{
	if (m_isAutoFight)
	{
		m_isReleaseSkill = false;
		doSkillById(getCanUseSkillId());
	}
}

void DoSkill::onSelTargetEvent(Ref* pSender, GameEvent* gEvent)
{
	if (m_isAutoFight)
	{
		GameObject* target = m_gamePlayer->getTarget();
		if (!target)
		{
			if (m_gamePlayer->getObjectType() == ObjectType::mainplayer)
			{
				target = GameObjectMgr::getInstance()->getNearGameObject(m_gamePlayer);
				if (target)
				{
					m_gamePlayer->setTarget(target);
				}
				else
				{
					setIsAutoFight(false);
				}
			}
			else
			{
				setIsAutoFight(false);
			}
		}
	}

}
