#include "LoginScene.h"
#include "UIManager.h"
#include "Utils.h"
#include "FileReader.h"
#include "GameAtlasMgr.h"
LoginScene::LoginScene()
{

}

LoginScene::~LoginScene()
{
	
}


Scene* LoginScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = LoginScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LoginScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	UIManager* g_uiManager = UIManager::getInstance();
	this->addChild(g_uiManager);
	GameAtlasMgr::getInstance();
	UIManager::getInstance()->showUI(UIType::UI_Login);




    return true;
}

