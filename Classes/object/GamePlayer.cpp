#include "GamePlayer.h"
#include "GameAction.h"
#include "FindPath.h"
#include "GameEffect.h"
#include "GameMap.h"
#include "Global.h"
#include "GameAI.h"
#include "UIManager.h"
#include "UIWorldMap.h"
GamePlayer::GamePlayer():
GameObject(),
m_weapon(nullptr),
m_hair(nullptr),
m_weaponAnim(nullptr),
m_hairAnim(nullptr),
m_skillid(0),
m_effectid(0),
m_target(nullptr),
m_callFunc(nullptr),
m_findPathEvent(nullptr)
{

}

GamePlayer::~GamePlayer()
{
	CC_SAFE_RELEASE_NULL(m_findPathEvent);
	CC_SAFE_RELEASE_NULL(m_weaponAnim);
	CC_SAFE_RELEASE_NULL(m_hairAnim);
}

GamePlayer* GamePlayer::create(ObjectData* data)
{
	GamePlayer* player = new GamePlayer();
	player->autorelease();
	player->init(data);

	return player;
}

bool GamePlayer::init(ObjectData* data)
{
	bool isRes = true;

	do 
	{
		isRes = GameObject::init(data);
		CC_BREAK_IF(!isRes);
		m_weapon = Sprite::create();
		m_weapon->setAnchorPoint(Point::ZERO);
		m_weapon->setLocalZOrder(-1);
		this->addChild(m_weapon);
		m_weapon->setPosition(Point::ZERO);

		m_hair = Sprite::create();
		m_hair->setAnchorPoint(Point::ZERO);
		this->addChild(m_hair);
		m_hair->setPosition(Point::ZERO);

		m_findPathEvent = GameFindPathEvent::create();
		m_findPathEvent->retain();
	} while (0);
	return isRes;
}

void GamePlayer::onAnimEvent(Ref* pSender, GameEvent* gEvent)
{
	GameAnimEvent* animEvent = dynamic_cast<GameAnimEvent*>(gEvent);
	if (animEvent)
	{
		m_dir = animEvent->m_dir;
		m_animState = animEvent->m_animState;
		m_skillid = animEvent->m_skillId;
		m_effectid = animEvent->m_effectId;
		m_callFunc = animEvent->m_callBack;
		m_animEvent->copy(animEvent);
		updateAnim();

		// 改变方向等操作，需要检测
		if (m_animState == ActMotion::stand)
		{
			this->m_actionDispatcher->resumOnce();
		}
	}
}

void GamePlayer::onEmptyEvent(Ref* pSender, GameEvent* gEvent)
{
	if (m_animState != ActMotion::stand && m_animState != ActMotion::die)
	{
		m_animState = ActMotion::stand;
		updateAnim();
	}
}

Animation* GamePlayer::getAnimation()
{
	CC_SAFE_RELEASE_NULL(m_hairAnim);
	m_hairAnim = GameAtlasMgr::getInstance()->getHairAnimationByIdAndStateAndDir(m_data->m_hairId, m_animState, m_dir);
	CC_SAFE_RETAIN(m_hairAnim);
	CC_SAFE_RELEASE_NULL(m_weaponAnim);
	m_weaponAnim	= GameAtlasMgr::getInstance()->getWeaponAnimationByIdAndStateAndDir(m_data->m_weaponId, m_animState, m_dir);
	CC_SAFE_RETAIN(m_weaponAnim);
	m_dressAnim		= GameAtlasMgr::getInstance()->getHumAnimationByIdAndStateAndDir(m_data->m_dressId, m_animState, m_dir);
	return m_dressAnim;
}

void GamePlayer::updateAnim()
{
	do
	{
		Animation* animation = getAnimation();
		CC_BREAK_IF(animation == nullptr);
		this->stopAllActions();
		this->setSpriteFrame(animation->getFrames().at(0)->getSpriteFrame());
		
		switch (m_animState)
		{
			case ActMotion::stand:
			{
				GameAnimate* animate = GameAnimate::create(animation);
				animate->setGameObject(this);
				this->runAction(RepeatForever::create(animate));
				//this->m_actionDispatcher->cancelPaused();
			}
				break;
			case ActMotion::walk:
			{
				GameRunAnimate* animate = GameRunAnimate::create(this);
				this->runAction(animate);
			}
				break;
			case ActMotion::hit:
			{
				doHit();
			}
				break;
			case ActMotion::bighit:
			{

			}
				break;
			case ActMotion::magic:
			{
                doMagic();
			}
				break;
			case ActMotion::die:
			{
				GameAnimate* animate = GameAnimate::create(animation);
				animate->setGameObject(this);
				this->runAction(animate);
			}
				break;
			default:
				break;
		}
		// 刷新武器
		if (m_weapon && m_weaponAnim)
		{
			m_weapon->setSpriteFrame(m_weaponAnim->getFrames().at(0)->getSpriteFrame());
		}
		// 刷新武器
		if (m_hair && m_hairAnim)
		{
			m_hair->setSpriteFrame(m_hairAnim->getFrames().at(0)->getSpriteFrame());
		}
	} while (0);
}

void GamePlayer::onFindPathEvent(Ref* pSender, GameEvent* gEvent)
{
	// 寻路
	GameFindPathEvent* findPath = dynamic_cast<GameFindPathEvent*>(gEvent);
	if (findPath)
	{
		ptr_PathNode node = FindPath::getPath(m_pos.x, m_pos.y, findPath->m_targetPoint.x, findPath->m_targetPoint.y);
		if (node)
		{
			CCLOG("onFindPathEvent1  %d    %d",(int) findPath->m_targetPoint.x, (int)findPath->m_targetPoint.y);
			this->setAnimStateNoUpdate(ActMotion::walk);
			this->stopAllActions();
			GameRunAnimate* animate = GameRunAnimate::create(this);
			animate->setIsFindPath(true);
			animate->setPathNode(node);
			this->runAction(animate);

			CCLOG("onFindPathEvent2  %d    %d", (int)findPath->m_targetPoint.x, (int)findPath->m_targetPoint.y);

			if (m_objectType == ObjectType::mainplayer)
			{
				UIWorldMap* ui = dynamic_cast<UIWorldMap*>(UIManager::getInstance()->getUI(UIType::UI_WorldMap));
				if (ui && ui->isVisible())
				{
					ui->setPathNode(node);
				}
			}
		}
		else
		{
			m_actionDispatcher->resumOnce();
		}
	}
}

void GamePlayer::updateOtherAnim(int index, float dt)
{
	// 刷新武器
	if (m_weapon && m_weaponAnim && index < m_weaponAnim->getFrames().size())
	{
		m_weapon->setSpriteFrame(m_weaponAnim->getFrames().at(index)->getSpriteFrame());

		if (IsWeaponFirst[(int)m_dir])
		{
			m_weapon->setLocalZOrder(0);
		}
		else
		{
			m_weapon->setLocalZOrder(-1);
		}
	}

	if (m_hair && m_hairAnim && index < m_hairAnim->getFrames().size())
	{
		m_hair->setSpriteFrame(m_hairAnim->getFrames().at(index)->getSpriteFrame());
	}
}

void GamePlayer::doSkillById(int id, GameEventCallback1 callFunc)
{
	SkillInfo info = GameAtlasMgr::getInstance()->getSkillInfoById(id);
	if (info.skilltype == SkillType::hit)
	{
		GameAnimEvent* gEvent = GameAnimEvent::create();
		gEvent->m_animState = ActMotion::hit;
		gEvent->m_dir = m_dir;
		gEvent->m_skillId = id;
		gEvent->m_effectId = info.effectId;
		gEvent->m_callBack = callFunc;
		this->m_actionDispatcher->dispatcherGameEventAndPause(gEvent);
	}
	else
	{
		GameAnimEvent* gEvent = GameAnimEvent::create();
		gEvent->m_animState = ActMotion::magic;
		gEvent->m_dir = m_dir;
		gEvent->m_skillId = id;
		gEvent->m_effectId = info.effectId;
		gEvent->m_callBack = callFunc;
		this->m_actionDispatcher->dispatcherGameEventAndPause(gEvent);
	}

}

void GamePlayer::doHit()
{
	Animation* animation = getAnimation();
	if (animation)
	{
		GameAnimate* animate = GameAnimate::create(animation);
		animate->setCallBack([=](Ref*){doHPChange(); 
		if (m_callFunc)
		{
			m_callFunc(this);
		}
		});
		animate->setGameObject(this);
		this->runAction(animate);
		// 特效
		if (m_skillid != 0 && m_effectid != 0)
		{
			// 获取动画
			vector<EffectAnim> effectanims = GameAtlasMgr::getInstance()->getEffectAnimationByIdAndStateAndDir(m_effectid, m_dir);
			if (effectanims.empty()) return;
			EffectAnim effect1 = effectanims[0];
			GameEffectAnim* effect = GameEffectAnim::create(this, effect1.anim);
			if (effect)
			{
				effect->start();
			}
		}
	}
}

void GamePlayer::doMagic()
{
	Animation* animation = getAnimation();
	if (animation)
	{
		GameAnimate* animate = GameAnimate::create(animation);
		animate->setCallBack(m_callFunc);
		animate->setGameObject(this);
		// 特效
		if (m_skillid != 0 && m_effectid != 0)
		{
			// 获取动画
			vector<EffectAnim> effectanims = GameAtlasMgr::getInstance()->getEffectAnimationByIdAndStateAndDir(m_effectid, m_dir, (int)m_dir * 2);
			if (effectanims.empty()) return;
			// 分类1 爆炸-----------------------------------------------------------
			if (effectanims.size() == 1)
			{
				// 爆炸
				EffectAnim effectinfo = effectanims[0];
				if (effectinfo.effect == EffectType::hit)
				{
					auto func = [=](){
						Node* effectNode = GameMap::getInstance()->getEffectNode();
						GameEffectHitAnim* effect = GameEffectHitAnim::create(effectNode, effectinfo.anim);
						if (effect)
						{
							effect->setGameObject(this);
							effect->setSkillIdAndDirForPosition(m_skillid, m_dir, m_pos);
							effect->start();
							effectinfo.anim->release();
						}

						doHPChange();
					};
					effectinfo.anim->retain();

					CallFunc* callfunc = CallFunc::create(func);
					Sequence* sequence = Sequence::create(animate, callfunc, nullptr);
					this->runAction(sequence);
					return;
				}
			}

			// 分类2 起手 爆炸-----------------------------------------------------------
			if (effectanims.size() == 2)
			{
				// 起手
				EffectAnim effectinfo1 = effectanims[0];
				GameEffectAnim* effect1 = GameEffectAnim::create(this, effectinfo1.anim);
				if (effect1)
				{
					effect1->start();
				}
				// 爆炸
				EffectAnim effectinfo2 = effectanims[1];
				if (effectinfo2.effect == EffectType::hit)
				{
					auto func = [=](){
						Node* effectNode = GameMap::getInstance()->getEffectNode();
						GameEffectHitAnim* effect = GameEffectHitAnim::create(effectNode, effectinfo2.anim);
						if (effect)
						{
							effect->setGameObject(this);
							effect->setSkillIdAndDirForPosition(m_skillid, m_dir, m_pos);
							effect->start();
							effectinfo2.anim->release();
						}
						doHPChange();
					};
					effectinfo2.anim->retain();
					CallFunc* callfunc = CallFunc::create(func);
					Sequence* sequence = Sequence::create(animate, callfunc, nullptr);
					this->runAction(sequence);
					return;
				}
			}
			// 分类3 起手 飞行 爆炸------------------------------------------------------
			if (effectanims.size() == 3)
			{
				// 起手
				EffectAnim effectinfo1 = effectanims[0];
				GameEffectAnim* effect1 = GameEffectAnim::create(this, effectinfo1.anim);
				if (effect1)
				{
					effect1->start();
				}
				// 爆炸
				GameEventCallback1 baozhafunc = nullptr;
				EffectAnim effectinfo3 = effectanims[2];
				if (effectinfo3.effect == EffectType::hit)
				{
					baozhafunc = [=](Ref*){
						Node* effectNode = GameMap::getInstance()->getEffectNode();
						GameEffectHitAnim* effect = GameEffectHitAnim::create(effectNode, effectinfo3.anim);
						if (effect)
						{
							effect->setGameObject(this);
							effect->setSkillIdAndDirForPosition(m_skillid, m_dir, m_pos);
							effect->start();
							effectinfo3.anim->release();
						}
						doHPChange();
					};
					effectinfo3.anim->retain();
				}
				// 飞行
				EffectAnim effectinfo2 = effectanims[1];
				if (effectinfo2.effect == EffectType::fly)
				{
					auto func = [=](){
						Node* effectNode = GameMap::getInstance()->getEffectNode();
						GameEffectFlyAnim* effect = GameEffectFlyAnim::create(effectNode, effectinfo2.anim);
						if (effect)
						{
							effect->setGameObject(this);
							effect->setEndCallBack(baozhafunc);
							effect->setSkillIdAndDirForPosition(m_skillid, m_dir, m_pos);
							effect->start();
							effectinfo2.anim->release();
						}
					};
					effectinfo2.anim->retain();
					CallFunc* callfunc = CallFunc::create(func);
					Sequence* sequence = Sequence::create(animate, callfunc, nullptr);
					this->runAction(sequence);
					return;
				}

			}

		}
	}
}

void GamePlayer::moveTo(Point pt)
{
	m_findPathEvent->m_targetPoint = pt;
	this->m_actionDispatcher->dispatcherGameEventAndPause(m_findPathEvent);
}

void GamePlayer::setTarget(GameObject* obj)
{
	if (m_objectType == ObjectType::mainplayer)
	{
		if (m_target)
		{
			m_target->setIsSelect(false);
		}
		m_target = obj;
		if (m_target)
		{
			m_target->setIsSelect(true);
		}
	}
	else
	{
		m_target = obj;
	}

	GameEvent* gEvent = GameEvent::create(GameEventId::sel_target);
	m_logicDispatcher->dispatcherGameEvent(gEvent, this);
}

GameObject* GamePlayer::getTarget()
{
	return m_target;
}

void GamePlayer::setDoSkill(DoSkill* doSkill)
{
	m_doSkill = doSkill;
}

DoSkill* GamePlayer::getDoSkill()
{
	return m_doSkill;
}

void GamePlayer::doHPChange()
{
	if (m_target)
	{
		int hp = RandomHelper::random_int(10, 200);
		GameEvent* gEvent = GameEvent::create((GameEventId)HPChangeEvent_ID);
		gEvent->setParamInt1(-hp);
		m_target->getLogicDispatcher()->dispatcherGameEvent(gEvent, this);
		if (m_target->getObjectData()->m_isLive == false)
		{
			setTarget(nullptr);
		}
	}
}


