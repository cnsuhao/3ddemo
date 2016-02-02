#include "GameObject3DMgr.h"
#include "ObjectData3DMgr.h"
#include "ShaderMgr.h"
#include "GameAI.h"
#include "UISelTarget.h"
#include "UIManager.h"
#include "GameMap.h"
GameObject3DMgr* GameObject3DMgr::_sGameObject3DMgr = nullptr;

GameObject3DMgr::GameObject3DMgr()
{

}

GameObject3DMgr::~GameObject3DMgr()
{
	
}

GameObject3DMgr* GameObject3DMgr::getInstance()
{
	if (!_sGameObject3DMgr)
	{
		_sGameObject3DMgr = new GameObject3DMgr;
		_sGameObject3DMgr->init();
	}
	return _sGameObject3DMgr;
}

void GameObject3DMgr::destroyInstance()
{
	if (_sGameObject3DMgr)
	{
		_sGameObject3DMgr->removeFromParent();
		CC_SAFE_RELEASE_NULL(_sGameObject3DMgr);
	}
}

void GameObject3DMgr::loadObjects()
{
	// this->removeAllChildren();
	// 主玩家
	auto data = ObjectData3DMgr::getInstance()->getMainObjectData();
	m_mainPlayer = GameObject3D::create(data);
	m_mainPlayer->setObjectType(ObjectType::mainplayer);
	m_mainPlayer->initHPBar();
	m_mainPlayer->initName();
	m_mainPlayer->refreshHPBar();
	this->addChild(m_mainPlayer);
	m_mainPlayer->updateAnim();
	m_mainPlayer->setScale(2.5f);
	m_mainPlayer->setCameraMask(4);
	m_mainPlayer->setPositionForMap();
	// 调整摄像机位置
	adjustCameraPosition();
	// 其他玩家
	auto playlist = ObjectData3DMgr::getInstance()->getPlayList();
	for (auto data : playlist)
	{
		GameObject3D* player = GameObject3D::create(data);
		player->setObjectType(ObjectType::otherplayer);
		player->initHPBar();
		player->initName();
		player->setScale(2.5f);
		player->refreshHPBar();
		this->addChild(player);
		player->setPositionForMap();
		player->updateAnim();
		player->setCameraMask(4);
		m_otherPlayerList.push_back(player);
		if (m_otherPlayerList.size() > 2)
		{
			break;
		}
	}
	// 监听主角位置改变
	m_mainPlayer->getLogicDispatcher()->addGameEventListener((int)GameEventId::update_pos, CC_CALLBACK_2(GameObject3DMgr::onUpdateMainPlayerPosEvent, this), this);

	// 调整摄像机位置
	adjustCameraPosition();
}

GameObject3D* GameObject3DMgr::getMainGamePlayer()
{
	return m_mainPlayer;
}

bool GameObject3DMgr::init()
{
	Size winSize = Director::getInstance()->getWinSize();
	m_mainPlayerCamera = Camera::createPerspective(60.0f, winSize.width / winSize.height, 0.1f, 1000.0f);
	m_mainPlayerCamera->setCameraFlag(CameraFlag::USER1);
	m_mainPlayerCamera->setPosition3D(Vec3::ZERO);
	m_mainPlayerCamera->setRotation3D(m_cameraRotate);
	m_mainPlayerCamera->setDepth(2);
	this->addChild(m_mainPlayerCamera);

	auto touchlistener = EventListenerTouchOneByOne::create();
	touchlistener->onTouchBegan = CC_CALLBACK_2(GameObject3DMgr::onTouchBegan, this);
	touchlistener->onTouchMoved = CC_CALLBACK_2(GameObject3DMgr::onTouchMoved, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchlistener, this);

	return true;
}

void GameObject3DMgr::adjustCameraPosition()
{
	if (m_mainPlayer && m_mainPlayerCamera)
	{
		Vec3 pos = m_mainPlayer->getPosition3D();
		m_mainPlayerCamera->setPosition3D(pos + m_cameraDist);
	}
}

void GameObject3DMgr::onUpdateMainPlayerPosEvent(Ref* pSender, GameEvent* gEvent)
{
	// 调整摄像机位置
	adjustCameraPosition();
	// 调整地图位置
	GameMap::getInstance()->adjustPosition();
}


bool GameObject3DMgr::onTouchBegan(Touch* touch, Event* evt)
{
	return true;
}

void GameObject3DMgr::onTouchMoved(Touch* touch, Event* evt)
{
	Point pre = touch->getPreviousLocation();
	Point now = touch->getLocation();

	Point dir = now - pre;

	float dirY = m_mainPlayer->getDir();
	dirY += dir.x;
	m_mainPlayer->setDir(dirY);
}

Camera* GameObject3DMgr::getObject3DCamera()
{
	return m_mainPlayerCamera;
}






