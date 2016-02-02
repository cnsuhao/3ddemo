#include "GameScene.h"
#include "UIManager.h"
#include "GameMap.h"
#include "Global.h"
#include "FindPath.h"
#include "ObjectDataMgr.h"
#include "GameObjectMgr.h"
#include "GameAI.h"
#include "GameObject3DMgr.h"
GameScene::GameScene():
_loadIndex(0),
_loadMaxNum(1)
{

}

GameScene::~GameScene()
{

}

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
	UIManager* g_uiManager = UIManager::getInstance();
	this->addChild(g_uiManager,(int)Zorder::order_ui);

	auto _map = GameMap::getInstance();
	this->addChild(_map, (int)Zorder::order_map);

	this->setTouchEnabled(true);
	_touchListener = EventListenerTouchOneByOne::create();
	_touchListener->setSwallowTouches(true);
	_touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	_touchListener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	_touchListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	_touchListener->onTouchCancelled = CC_CALLBACK_2(GameScene::onTouchCancelled, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener, this);
	// 跳地图事件
	GameDispatcher::getInstance()->addGameEventListener((int)GameEventId::change_map, CC_CALLBACK_2(GameScene::onChangeMapEvent, this), this);
	// 刷新主角位置事件
	GameDispatcher::getInstance()->addGameEventListener(int(GameEventId::update_mypos), CC_CALLBACK_2(GameScene::onUpdateMyPosEvent, this), this);

	// 首次加载地图
	this->loadResourceMap();
	// 创建RoleCamera 
	this->createRoleCamera();
    return true;
}



bool GameScene::onTouchBegan(Touch *touch, Event *unusedEvent)
{
	// 选人
	//if (GameObjectMgr::getInstance()->clickGameObjec(touch->getLocation()))
	//{
	//	return true;
	//}
	// 寻路
	GameMap::getInstance()->runMoveArrowAnim(touch->getLocation());
	Point point = GameMap::getInstance()->convertWorldPosToTilePos(touch->getLocation());
	auto mainPlayer = GameObject3DMgr::getInstance()->getMainGamePlayer();
	if (GameMap::getInstance()->canMove(point.x,point.y))
	{
		//mainPlayer->getDoSkill()->setIsAutoFight(false);
		mainPlayer->moveTo(point);
	}
	
	return true;
}

void GameScene::onTouchMoved(Touch *touch, Event *unusedEvent)
{

}

void GameScene::onTouchEnded(Touch *touch, Event *unusedEvent)
{

}

void GameScene::onTouchCancelled(Touch *touch, Event *unusedEvent)
{

}

void GameScene::onUpdateMyPosEvent(Ref* pSender, GameEvent* gEvent)
{
	auto myData = ObjectDataMgr::getInstance()->getMainObjectData();
	if (myData)
	{
		GameMap::getInstance()->checkIsChuanSongPoint(myData->m_pos);
	}
}

void GameScene::onChangeMapEvent(Ref* pSender, GameEvent* gEvent)
{
	auto mainData = ObjectDataMgr::getInstance()->getMainObjectData();
	if (mainData)
	{
		mainData->m_mapId = gEvent->getParamStr();
	}
	this->scheduleOnce(schedule_selector(GameScene::beginLoadScene), 0.0f);
}


void GameScene::beginLoadScene(float dt)
{
	loadResourceMap();
}

void GameScene::loadResourceMap()
{
	ArmatureDataManager::getInstance()->destroyInstance();
	// 隐藏所有UI
	UIManager::getInstance()->hideAllUI();
	// 清理资源
	GameMap::getInstance()->clearResources();
	// 开始Loading
	UIManager::getInstance()->loadUI(0);
	_loadIndex = 0;
	auto images = GameMap::getInstance()->getMapImages();
	if (images.size() > 0)
	{
		_loadMaxNum = images.size();
		for (auto image : images)
		{
			TextureCache::getInstance()->addImageAsync(image, CC_CALLBACK_1(GameScene::loadImageAsyncCallBack, this));
		}
	}
	else
	{
		UIManager::getInstance()->loadUI(100);
	}
}

void GameScene::loadImageAsyncCallBack(Texture2D* tex)
{
	_loadIndex++;
	UIManager::getInstance()->loadUI(_loadIndex * 100.0f / _loadMaxNum);
	if (_loadIndex == _loadMaxNum)
	{
		// 下一帧刷新
		this->scheduleOnce(schedule_selector(GameScene::endLoadScene), 0.0f);
	}
}

void GameScene::endLoadScene(float dt)
{
	GameMap::getInstance()->setTileMap();
	GameMap::getInstance()->loadObjects();
	showMainUI();
	TextureCache::getInstance()->removeUnusedTextures();
	auto gEvent = GameEvent::create(GameEventId::load_end);
	UIManager::getInstance()->getDispatcher()->dispatcherGameEvent(gEvent, this);
}

void GameScene::showMainUI()
{
	UIManager::getInstance()->showUI(UIType::UI_MiniMap);
	UIManager::getInstance()->showUI(UIType::UI_RoleHead);
	UIManager::getInstance()->showUI(UIType::UI_Rocker);
	UIManager::getInstance()->showUI(UIType::UI_SkillPanel);
	UIManager::getInstance()->hideWithCreate(UIType::UI_SelTarget);
}

void GameScene::load3DObject()
{
	GameObject3DMgr* mgr = GameObject3DMgr::getInstance();
	if (mgr)
	{
		mgr->loadObjects();
		this->addChild(mgr);
	}
}

void GameScene::createRoleCamera()
{
	_roleCamera = Camera::create();
	_roleCamera->setCameraFlag(CameraFlag::USER2);
	this->addChild(_roleCamera);
	_roleCamera->setDepth(3);
	float z = _roleCamera->getPosition3D().z;
	_roleCamera->setPositionZ(z + 0);
}










