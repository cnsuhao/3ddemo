#include "GameEffect.h"
#include "GameAtlasMgr.h"
#include "GameMap.h"
GameEffectBase::GameEffectBase():
m_effect(nullptr),
m_parent(nullptr),
m_action(nullptr),
m_nextType(EffectType::nil),
m_endCallFunc(nullptr)
{

}

GameEffectBase::~GameEffectBase()
{

}

bool GameEffectBase::init()
{
	bool isRes = false;
	do 
	{
		CC_BREAK_IF(!Node::init());
		isRes = true;
	} while (0);

	return isRes;
}

void GameEffectBase::setEndCallBack(GameEventCallback1 func)
{
	m_endCallFunc = func;
}

void GameEffectBase::animRunEnd(Ref* pSender)
{
	if (m_endCallFunc)
	{
		m_endCallFunc(pSender);
	}
	this->removeFromParentAndCleanup(true);
}

EffectType GameEffectBase::getNextEffectType()
{
	return m_nextType;
}

GameEffectAnim::GameEffectAnim():
GameEffectBase()
{

}

GameEffectAnim::~GameEffectAnim()
{

}

GameEffectAnim* GameEffectAnim::create(Node* obj, Animation* anim)
{
	GameEffectAnim* effect = new GameEffectAnim;
	if (effect)
	{
		effect->autorelease();
		effect->init(obj, anim);
	}
	return effect;
}

void GameEffectAnim::start()
{
	m_parent->addChild(this, -1);
	m_effect->runAction(m_action);
}

void GameEffectAnim::end()
{
	m_effect->stopAllActions();
	this->removeFromParent();
}

bool GameEffectAnim::init(Node* obj, Animation* anim)
{
	GameEffectBase::init();
	m_parent = obj;
	if (anim)
	{
		m_effect = Sprite::createWithSpriteFrame(anim->getFrames().at(0)->getSpriteFrame());
		m_effect->setAnchorPoint(Point::ZERO);
		m_effect->setPosition(Point::ZERO);
		m_effect->setBlendFunc(BlendFunc::ADDITIVE);
		auto action1 = Animate::create(anim);
		auto action2 = CallFuncN::create(CC_CALLBACK_1(GameEffectAnim::animRunEnd,this));
		m_action = Sequence::create(action1, action2, nullptr);
		this->addChild(m_effect);
	}
	return true;
}

void GameEffectAnim::setGameObject(GamePlayer* player)
{
	m_player = player;
}

GameEffectHitAnim::GameEffectHitAnim():
GameEffectAnim()
{

}

GameEffectHitAnim::~GameEffectHitAnim()
{

}

GameEffectHitAnim* GameEffectHitAnim::create(Node* node, Animation* anim)
{
	GameEffectHitAnim* effect = new GameEffectHitAnim;
	if (effect)
	{
		effect->autorelease();
		effect->init(node, anim);
	}
	return effect;
}


void GameEffectHitAnim::setSkillIdAndDirForPosition(int id, ActDir dir, Point pt)
{
	SkillInfo info = GameAtlasMgr::getInstance()->getSkillInfoById(id);
	if (info.isValid)
	{
		if (m_player && m_player->getTarget())
		{
			Point ds = m_player->getTarget()->getObjectData()->m_pos;
			ds = GameMap::getInstance()->convertTilePosToNodePos(ds);
			this->setPosition(ds);
		}
		else
		{
			Point ds = getNextPostion(pt, dir, info.distance);
			ds = GameMap::getInstance()->convertTilePosToNodePos(ds);
			this->setPosition(ds);
		}
	}
}



GameEffectFlyAnim::GameEffectFlyAnim() :
GameEffectAnim(),
m_speed(0.002f),
m_target(nullptr)
{

}

GameEffectFlyAnim::~GameEffectFlyAnim()
{
	if (m_target)
	{
		m_target->getLogicDispatcher()->removeGameEventListener(this);
	}
}



GameEffectFlyAnim* GameEffectFlyAnim::create(Node* node, Animation* anim)
{
	GameEffectFlyAnim* effect = new GameEffectFlyAnim;
	if (effect)
	{
		effect->autorelease();
		effect->init(node, anim);
	}
	return effect;
}


void GameEffectFlyAnim::setSkillIdAndDirForPosition(int id, ActDir dir, Point pt)
{
	SkillInfo info = GameAtlasMgr::getInstance()->getSkillInfoById(id);
	if (info.isValid)
	{
		m_targetpt = getNextPostion(pt, dir, info.distance);
		m_nowpt = GameMap::getInstance()->convertTilePosToNodePos(pt);
		if (m_player && m_player->getTarget())
		{
			m_targetpt = m_player->getTarget()->getObjectData()->m_pos;
		}
		m_targetpt = GameMap::getInstance()->convertTilePosToNodePos(m_targetpt);
		this->setPosition(m_nowpt);

		auto action1 = MoveTo::create(m_speed * m_nowpt.distance(m_targetpt), m_targetpt);
		auto action2 = CallFuncN::create(CC_CALLBACK_1(GameEffectAnim::animRunEnd, this));
		m_nodeAnim = Sequence::create(action1, action2, nullptr);
	}
}

void GameEffectFlyAnim::start()
{
	m_parent->addChild(this, -1);
	m_effect->runAction(m_action);
	this->runAction(m_nodeAnim);

	if (m_player && m_player->getTarget())
	{
		m_target = m_player->getTarget();
		m_target->getLogicDispatcher()->addGameEventListener((int)GameEventId::update_pos, CC_CALLBACK_2(GameEffectFlyAnim::onUpdateTargetPosEvent, this), this);
	}
}

bool GameEffectFlyAnim::init(Node* obj, Animation* anim)
{
	GameEffectBase::init();
	m_parent = obj;
	if (anim)
	{
		m_effect = Sprite::createWithSpriteFrame(anim->getFrames().at(0)->getSpriteFrame());
		m_effect->setAnchorPoint(Point::ZERO);
		m_effect->setPosition(Point::ZERO);
		m_effect->setBlendFunc(BlendFunc::ADDITIVE);
		m_action = RepeatForever::create(Animate::create(anim));

		this->addChild(m_effect);
	}
	return true;
}

void GameEffectFlyAnim::onUpdateTargetPosEvent(Ref* pSender, GameEvent* gEvent)
{
	if (m_player && m_player->getTarget())
	{
		m_targetpt = m_player->getTarget()->getObjectData()->m_pos;
	}
	m_nowpt = this->getPosition();
	m_targetpt = GameMap::getInstance()->convertTilePosToNodePos(m_targetpt);
	auto action1 = MoveTo::create(m_speed * m_nowpt.distance(m_targetpt), m_targetpt);
	auto action2 = CallFuncN::create(CC_CALLBACK_1(GameEffectAnim::animRunEnd, this));
	m_nodeAnim = Sequence::create(action1, action2, nullptr);
	this->stopAllActions();
	this->runAction(m_nodeAnim);
}
