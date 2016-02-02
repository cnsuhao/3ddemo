#include "GameObject.h"
#include "GameAtlasMgr.h"
#include "GameMap.h"
#include "UIManager.h"
#include "GameAI.h"
#include "GameObjectMgr.h"
GameObject::GameObject() :Sprite()
, m_animState(ActMotion::stand)
, m_dir(ActDir::DIR_DOWN)
, m_isUpdate(false)
, m_dressAnim(nullptr)
, m_hpBar(nullptr)
, m_nameText(nullptr)
, m_hpText(nullptr)
, m_selectSprite(nullptr)
, m_objectType(ObjectType::nil)
, m_doSkill(nullptr)
, m_barBK(nullptr)
{

}


GameObject::~GameObject()
{
	CC_SAFE_RELEASE_NULL(m_animEvent);
	CC_SAFE_RELEASE_NULL(m_actionDispatcher);
	CC_SAFE_RELEASE_NULL(m_logicDispatcher);
}

bool GameObject::init(ObjectData* data)
{
	bool isRes = false;
	do 
	{
		Sprite::init();
		m_data = data;
		m_animState = m_data->m_aniState;
		m_dir = m_data->m_dir;
		m_pos = m_data->m_pos;
		
		m_actionDispatcher = GameDispatcher::create();
		m_actionDispatcher->retain();

		m_animEvent = GameAnimEvent::create();
		m_animEvent->retain();
		m_actionDispatcher->addGameEventListener(AnimEventState_ID, CC_CALLBACK_2(GameObject::onAnimEvent,this), this);
		m_actionDispatcher->addGameEventListener(AnimEventEmpty_ID, CC_CALLBACK_2(GameObject::onEmptyEvent, this), this);
		m_actionDispatcher->addGameEventListener(FindPathEvent_ID, CC_CALLBACK_2(GameObject::onFindPathEvent, this), this);

		m_logicDispatcher = GameDispatcher::create();
		m_logicDispatcher->retain();
		m_logicDispatcher->addGameEventListener(HPChangeEvent_ID, CC_CALLBACK_2(GameObject::onHPChangeEvent, this), this);
		this->setAnchorPoint(Point(0,0));
		//this->setBlendFunc(BlendFunc::ADDITIVE);
		//this->setOpacity(255);
		this->setKeepBlendFunc(true);
		isRes = true;
	} while (0);
	
	return isRes;
}



void GameObject::setAnimState(ActMotion state)
{
	if (m_animState != state)
	{
		m_animEvent->m_animState = state;
		m_animEvent->m_dir = m_dir;
		this->dispatcherAnimEvent();
	}
}

void GameObject::setDir(ActDir dir)
{
	if (m_dir != dir)
	{
		m_animEvent->m_animState = m_animState;
		m_animEvent->m_dir = dir;
		this->dispatcherAnimEvent();
	}
}

void GameObject::setDirNoUpdate(ActDir dir)
{
	if (m_dir != dir)
	{
		m_dir = dir;
	}
}

void GameObject::updateAnim()
{
	//
}

void GameObject::onAnimEvent(Ref* pSender, GameEvent* gEvent)
{
	//
}

void GameObject::onEmptyEvent(Ref* pSender, GameEvent* gEvent)
{
	//
}


GameDispatcher* GameObject::getActionDispatcher()
{
	return m_actionDispatcher;
}

void GameObject::setPositionForMap()
{
	Point pos = GameMap::getInstance()->convertTilePosToNodePos(m_pos);
	this->setPosition(pos);

	if (m_objectType == ObjectType::mainplayer)
	{
		GameMap::getInstance()->adjustPosition();
	}
}

ObjectData* GameObject::getObjectData()
{
	return m_data;
}

ActDir GameObject::getDir()
{
	return m_dir;
}

void GameObject::updateData()
{
	bool isPosChange = false;
	if (m_data->m_pos != m_pos)
	{
		isPosChange = true;
	}
	m_data->m_pos = m_pos;
	m_data->m_dir = m_dir;
	m_data->m_aniState = m_animState;

	// 刷新位置
	if (isPosChange)
	{
		if (m_objectType == ObjectType::mainplayer)
		{
			GameEvent* gEvent = GameEvent::create(GameEventId::update_mypos);
			GameDispatcher::getInstance()->dispatcherGameEvent(gEvent, this);
		}
	}
}

void GameObject::setDirAndAnimState(ActDir dir, ActMotion state)
{
	if (m_animState != state || m_dir != dir)
	{
		this->m_actionDispatcher->clearCacheEvents();
	}

	m_animEvent->m_animState = state;
	m_animEvent->m_dir = dir;
	this->dispatcherAnimEvent();
}

void GameObject::dispatcherAnimEvent()
{
	this->m_actionDispatcher->dispatcherGameEventAndPause(m_animEvent, true);
}

void GameObject::setTilePos(Point pos)
{
	if (m_pos != pos)
	{
		m_pos = pos;
		GameEvent* gEvent = GameEvent::create(GameEventId::update_pos);
		this->m_logicDispatcher->dispatcherGameEvent(gEvent, this);
		GameObjectMgr::getInstance()->setReorderChildDirty(true);
		checkAlphaState();

		if (m_objectType == ObjectType::mainplayer)
		{
			GameEvent* gEvent = GameEvent::create(GameEventId::began_changemypos);
			GameDispatcher::getInstance()->dispatcherGameEvent(gEvent, this);
		}
	}

}

void GameObject::setObjectType(ObjectType objtype)
{
	m_objectType = objtype;
}

ObjectType GameObject::getObjectType()
{
	return m_objectType;
}

void GameObject::onFindPathEvent(Ref* pSender, GameEvent* gEvent)
{

}

void GameObject::setAnimStateNoUpdate(ActMotion state)
{
	m_animState = state;
}

void GameObject::updateOtherAnim(int index, float dt)
{
	//
}

void GameObject::resetAnimState(Ref* pSender)
{
	//m_animState = ActMotion::nil;
}

void GameObject::initHPBar()
{
	if (m_hpBar || m_barBK)
	{
		m_barBK->removeFromParent();
		m_hpBar->removeFromParent();
		m_barBK = nullptr;
		m_hpBar = nullptr;
		m_hpText = nullptr;
	}
	string imgname = "";
	if (m_objectType != ObjectType::mainplayer)
	{
		imgname = "ui/others/bloodrect.png";
	}
	else
	{
		imgname = "ui/others/blue.png";
	}
	m_barBK = ImageView::create("ui/others/bloodrectback.png");
	if (m_barBK)
	{
		//m_barBK->setAnchorPoint(Point::ZERO);
		m_barBK->ignoreContentAdaptWithSize(false);
		m_barBK->setContentSize(Size(80, 10));
		m_barBK->setPosition(Point(24, 58));
		this->addChild(m_barBK);
	}
	m_hpBar = LoadingBar::create(imgname);
	m_hpBar->ignoreContentAdaptWithSize(false);
	m_hpBar->setContentSize(Size(80,10));
	//m_hpBar->setAnchorPoint(Point::ZERO);
	m_hpBar->setPosition(Point(24,58));
	this->addChild(m_hpBar);
	//
	//m_hpText = Text::create();
	//m_hpText->setFontName("fonts/AdobeHeiTi.otf");
	//m_hpText->setFontSize(10);
	//m_hpText->setPosition(Point(40,5));
	//m_hpBar->addChild(m_hpText);
}

void GameObject::refreshHPBar()
{
	if (m_hpBar && m_data)
	{
		m_hpBar->setPercent(m_data->m_hp * 100.0f / m_data->m_hpMax);
		//m_hpText->setText(StringUtils::format("%d/%d", m_data->m_hp, m_data->m_hpMax));
	}
}

void GameObject::initName()
{
	if (m_nameText)
	{
		m_nameText->removeFromParent();
		m_nameText = nullptr;
	}
	m_nameText = Text::create();
	m_nameText->setAnchorPoint(Point(0.5f,0.0f));
	m_nameText->setFontName("fonts/AdobeHeiTi.otf");
	if (m_objectType != ObjectType::mainplayer)
	{
		m_nameText->setTextColor(Color4B::RED);
		//m_nameText->enableOutline(Color4B::BLACK, 1);
	}
	else
	{
		m_nameText->setTextColor(Color4B::WHITE);
		//m_nameText->enableOutline(Color4B::BLACK, 1);
	}
	m_nameText->setFontSize(16);
	m_nameText->setPosition(Point(25, 65));
	m_nameText->setString(m_data->m_name);
	this->addChild(m_nameText);

}

ActMotion GameObject::getActState()
{
	return m_animState;
}

void GameObject::stop()
{
	this->m_actionDispatcher->clearCacheEvents();
	this->setAnimState(ActMotion::stand);
}

void GameObject::onHPChangeEvent(Ref* pSender, GameEvent* gEvent)
{
	int hp = gEvent->getParamInt1();
	if (m_data)
	{
		hp += m_data->m_hp;
		if (hp < 0)
		{
			m_doSkill->setIsAutoFight(false);
			hp = 0;
			m_data->m_isLive = false;
			//
			m_actionDispatcher->clearCacheEvents();
			setAnimState(ActMotion::die);
		}
		m_data->m_hp = hp;
		refreshHPBar();

		TextBMFont* bmFnt = TextBMFont::create();
		bmFnt->setFntFile("fonts/red.fnt");
		bmFnt->setString(StringUtils::format("%d", gEvent->getParamInt1()));
		this->addChild(bmFnt);
		bmFnt->setPosition(Point(24,30));

		MoveBy* moveby1 = MoveBy::create(0.2f, Point(30,50));
		FadeIn* fadein = FadeIn::create(0.2f);
		Spawn* spawn1 = Spawn::createWithTwoActions(moveby1, fadein);
		ScaleTo* scaleTo1 = ScaleTo::create(0.1f, 1.5f);
		ScaleTo* scaleTo2 = ScaleTo::create(0.1f, 1.0f);
		FadeOut* fadeOut = FadeOut::create(0.2f);
		MoveBy* moveby2 = MoveBy::create(0.2f, Point(0, 30));
		Spawn* spawn2 = Spawn::createWithTwoActions(moveby2, fadeOut);
		CallFunc* callFunc = CallFunc::create([=](){
			bmFnt->removeFromParent();
		}
		);
		bmFnt->runAction(Sequence::create(spawn1, scaleTo1, scaleTo2, spawn2, callFunc, nullptr));
	}
	if (m_objectType == ObjectType::mainplayer)
	{
		GameEvent* gEvent = GameEvent::create(GameEventId::hp_change);
		UIManager::getInstance()->getDispatcher()->dispatcherGameEvent(gEvent, this);
	}
}

GameDispatcher* GameObject::getLogicDispatcher()
{
	return m_logicDispatcher;
}

void GameObject::setIsSelect(bool isSel)
{
	if (!m_selectSprite)
	{
		m_selectSprite = Sprite::create("select.png");
		this->addChild(m_selectSprite, -1);
		m_selectSprite->setPosition(Point(24,0));
	}
	m_selectSprite->setVisible(isSel);
}

Point GameObject::getTilePos()
{
	return m_pos;
}

void GameObject::setIsAlpha(bool isAlpha)
{
	if (isAlpha)
	{
		this->setOpacity(150);
	}
	else
	{
		this->setOpacity(255);
	}
}

void GameObject::checkAlphaState()
{
	if (GameMap::getInstance()->isAlphaPoint(m_pos) || GameObjectMgr::getInstance()->isExistGameObject(this, Point(m_pos.x, m_pos.y + 1))|| GameObjectMgr::getInstance()->isExistGameObject(this, m_pos))
	{
		setIsAlpha(true);
	}
	else
	{
		setIsAlpha(false);
	}
}


