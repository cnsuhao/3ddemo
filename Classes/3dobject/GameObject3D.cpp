#include "GameObject3D.h"
#include "GameAtlasMgr.h"
#include "GameMap.h"
#include "UIManager.h"
#include "GameAI.h"
#include "FindPath.h"
#include "GameObject3DMgr.h"
GameObject3D::GameObject3D() :Sprite3D()
, m_animState(ActMotion::stand)
, m_dir(0.0f)
, m_isUpdate(false)
, m_speed(5.0f)
, m_objectType(ObjectType::nil)
{


}


GameObject3D::~GameObject3D()
{
	CC_SAFE_RELEASE_NULL(m_animEvent);
	CC_SAFE_RELEASE_NULL(m_actionDispatcher);
	CC_SAFE_RELEASE_NULL(m_logicDispatcher);
}


GameObject3D* GameObject3D::create(ObjectData3D* data)
{
	GameObject3D* obj = new GameObject3D();
	if (obj)
	{
		obj->init(data);
		obj->autorelease();
	}

	return obj;
}


bool GameObject3D::init(ObjectData3D* data)
{
	bool isRes = false;
	do 
	{
		string file = GameAtlasMgr::getInstance()->getHum3DFileName(data->m_dressId);
		CC_BREAK_IF(Sprite3D::initWithFile(file) == false);
		m_data = data;
		m_animState = m_data->m_aniState;
		setDir(m_data->m_dir);
		setTilePos(m_data->m_pos);
		m_actionDispatcher = GameDispatcher::create();
		m_actionDispatcher->retain();
		m_animEvent = GameAnimEvent::create();
		m_animEvent->retain();
		m_findPathEvent = GameFindPathEvent::create();
		m_findPathEvent->retain();
		m_actionDispatcher->addGameEventListener(AnimEventState_ID, CC_CALLBACK_2(GameObject3D::onAnimEvent,this), this);
		m_actionDispatcher->addGameEventListener(AnimEventEmpty_ID, CC_CALLBACK_2(GameObject3D::onEmptyEvent, this), this);
		m_actionDispatcher->addGameEventListener(FindPathEvent_ID, CC_CALLBACK_2(GameObject3D::onFindPathEvent, this), this);
		m_logicDispatcher = GameDispatcher::create();
		m_logicDispatcher->retain();
		m_logicDispatcher->addGameEventListener(HPChangeEvent_ID, CC_CALLBACK_2(GameObject3D::onHPChangeEvent, this), this);
	
		isRes = true;
	} while (0);
	
	return isRes;
}



void GameObject3D::setAnimState(ActMotion state)
{
	if (m_animState != state)
	{
		bool isBreak = isCanBreak(m_animState);
		m_animEvent->m_animState = state;
		m_animEvent->m_3dDir = m_dir;
		this->m_actionDispatcher->dispatcherGameEventAndPause(m_animEvent, !isBreak);
	}
}

void GameObject3D::setDir(float dir)
{
	if (m_dir != dir || m_dir == 0.0f)
	{
		m_dir = dir;
		Mat4 x, y, r;
		Quaternion q;
		Vec3 s, t;
		float cx = CC_DEGREES_TO_RADIANS(45.0f);
		float cy = CC_DEGREES_TO_RADIANS(m_dir);
		Mat4::createRotationY(cy, &y);
		Mat4::createRotationX(cx, &x);
		Mat4::multiply(x, y, &r);
		r.decompose(&s, &q, &t);
		this->setRotationQuat(q);
	}
}


void GameObject3D::setDirAndAnimState(float dir, ActMotion state)
{
	setDir(dir);
	setAnimState(state);
}


GameAnimation3D* GameObject3D::getAnimition3D()
{
	m_anim3D = GameAtlasMgr::getInstance()->getHum3DAnimationByIdAndState(m_data->m_dressId, m_animState);

	return m_anim3D;
}

void GameObject3D::updateAnim()
{
	do
	{
		GameAnimation3D* animation = getAnimition3D();
		CC_BREAK_IF(animation == nullptr);
		this->stopAllActions();
		this->setDir(m_dir);
		switch (m_animState)
		{
		case ActMotion::stand:
		{
								 GameAnimate3D* animate = GameAnimate3D::create(animation);
								 animate->setGameObject(this);
								 this->runAction(RepeatForever::create(animate));
		}
			break;
		case ActMotion::walk:
		{
								GameRunAnimate3D* animate = GameRunAnimate3D::create(this);
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
								//TODO
		}
			break;
		case ActMotion::magic:
		{
								 doMagic();
		}
			break;
		case ActMotion::die:
		{
							   GameAnimate3D* animate = GameAnimate3D::create(animation);
							   animate->setGameObject(this);
							   this->runAction(animate);
		}
			break;
		default:
			break;
		}
	} while (0);
}

void GameObject3D::onAnimEvent(Ref* pSender, GameEvent* gEvent)
{
	GameAnimEvent* animEvent = dynamic_cast<GameAnimEvent*>(gEvent);
	if (animEvent)
	{
		m_dir = animEvent->m_3dDir;
		m_animState = animEvent->m_animState;
		m_animEvent->copy(animEvent);
		updateAnim();
	}
}

void GameObject3D::onEmptyEvent(Ref* pSender, GameEvent* gEvent)
{
	if (m_animState != ActMotion::stand && m_animState != ActMotion::die)
	{
		m_animState = ActMotion::stand;
		updateAnim();
	}
}

bool GameObject3D::isCanBreak(ActMotion state)
{
	if (state == ActMotion::stand || state == ActMotion::walk)
	{
		return true;
	}
	return false;
}



GameDispatcher* GameObject3D::getActionDispatcher()
{
	return m_actionDispatcher;
}

void GameObject3D::setPositionForMap()
{
	setTilePos(m_pos);
	if (m_objectType == ObjectType::mainplayer)
	{
		GameMap::getInstance()->adjustPosition();
	}
}

ObjectData3D* GameObject3D::getObjectData()
{
	return m_data;
}

float GameObject3D::getDir()
{
	return m_dir;
}

void GameObject3D::updateData()
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


void GameObject3D::dispatcherAnimEvent()
{
	this->m_actionDispatcher->dispatcherGameEventAndPause(m_animEvent, true);
}

void GameObject3D::setTilePos(Point pos)
{
	if (m_pos != pos)
	{
		m_pos = pos;
		this->setPosition(m_pos);

		// 更新位置通知
		if (m_objectType == ObjectType::mainplayer)
		{
			GameEvent* gEvent = GameEvent::create(GameEventId::update_pos);
			this->m_logicDispatcher->dispatcherGameEvent(gEvent, this);
			GameMap::getInstance()->adjustPosition();
		}
		//Vec3 vec3 = GameMap::getInstance()->converPointToVec3(m_pos);
		//this->setPosition3D(vec3);

		checkAlphaState();
	}
}

void GameObject3D::setObjectType(ObjectType objtype)
{
	m_objectType = objtype;
}

ObjectType GameObject3D::getObjectType()
{
	return m_objectType;
}

void GameObject3D::moveTo(Point pt)
{
	bool isBreak = isCanBreak(m_animState);
	m_findPathEvent->m_targetPoint = pt;
	this->m_actionDispatcher->dispatcherGameEventAndPause(m_findPathEvent, !isBreak);
}

void GameObject3D::onFindPathEvent(Ref* pSender, GameEvent* gEvent)
{
	// 寻路
	GameFindPathEvent* findPath = dynamic_cast<GameFindPathEvent*>(gEvent);
	if (findPath)
	{
		Point startPoint = GameMap::getInstance()->convertPixelPosToTilePos(m_pos);
		ptr_PathNode node = FindPath::getPath(startPoint.x, startPoint.y, findPath->m_targetPoint.x, findPath->m_targetPoint.y,true);
		if (node)
		{
			CCLOG("onFindPathEvent1  %d    %d", (int)findPath->m_targetPoint.x, (int)findPath->m_targetPoint.y);
			this->setAnimStateNoUpdate(ActMotion::walk);
			this->stopAllActions();
			GameRunAnimate3D* animate = GameRunAnimate3D::create(this);
			animate->setIsFindPath(true);
			animate->setPathNode(node);
			this->runAction(animate);

			CCLOG("onFindPathEvent2  %d    %d", (int)findPath->m_targetPoint.x, (int)findPath->m_targetPoint.y);
			//if (m_objectType == ObjectType::mainplayer)
			//{
			//	UIWorldMap* ui = dynamic_cast<UIWorldMap*>(UIManager::getInstance()->getUI(UIType::UI_WorldMap));
			//	if (ui && ui->isVisible())
			//	{
			//		ui->setPathNode(node);
			//	}
			//}
		}
		else
		{
			m_actionDispatcher->resumOnce();
		}
	}
}

void GameObject3D::setAnimStateNoUpdate(ActMotion state)
{
	m_animState = state;
}

void GameObject3D::resetAnimState(Ref* pSender)
{
	//m_animState = ActMotion::nil;
}

ActMotion GameObject3D::getActState()
{
	return m_animState;
}

void GameObject3D::stop()
{
	this->m_actionDispatcher->clearCacheEvents();
	this->setAnimState(ActMotion::stand);
}

Point GameObject3D::getTilePos()
{
	return m_pos;
}

float GameObject3D::getSpeed()
{
	return m_speed;
}

void GameObject3D::setSpeed(float s)
{
	m_speed = s;
}

Point GameObject3D::getDir2D()
{
	float dir = m_dir - 90.0f;
	dir = CC_DEGREES_TO_RADIANS(dir);
	Point pt;
	pt.x = cos(dir);
	pt.y = sin(dir);
	return pt;
}

GameDispatcher* GameObject3D::getLogicDispatcher()
{
	return m_logicDispatcher;
}

void GameObject3D::setIsAlpha(bool isAlpha)
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

// TODO......

void GameObject3D::onHPChangeEvent(Ref* pSender, GameEvent* gEvent)
{

}

void GameObject3D::setIsSelect(bool isSel)
{

}

void GameObject3D::checkAlphaState()
{
	if (GameMap::getInstance()->isAlphaPixelPoint(m_pos))
	{
		setIsAlpha(true);
	}
	else
	{
		setIsAlpha(false);
	}
}

void GameObject3D::setDirNoUpdate(float dir)
{

}

void GameObject3D::doHit()
{

}

void GameObject3D::doMagic()
{

}


void GameObject3D::initHPBar()
{

}

void GameObject3D::refreshHPBar()
{

}

void GameObject3D::initName()
{

}








