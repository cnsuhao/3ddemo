#include "AppDelegate.h"
#include "LoginScene.h"
#include "CCLuaEngine.h"
#include "Global.h"
#include "lua_module_register.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("My Game");
        director->setOpenGLView(glview);
    }

	FileUtils::getInstance()->setXXTEAKeyAndSign("xxteakey", "xxteasign");
	glview->setFrameSize(960, 640);
	glview->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::NO_BORDER);
    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 30);

	// lua
	LuaEngine* pEngine = LuaEngine::getInstance();
	pEngine->addSearchPath("lua");
	pEngine->addSearchPath("lua/src");
	pEngine->addSearchPath("lua/cocos");
	ScriptEngineManager::getInstance()->setScriptEngine(pEngine);

	LuaStack* stack = pEngine->getLuaStack();
	stack->setXXTEAKeyAndSign("xxteakey", strlen("xxteakey"), "xxteasign", strlen("xxteasign"));
	lua_State* L = stack->getLuaState();

	lua_module_register(L);
    // create a scene. it's an autorelease object
    auto scene = LoginScene::createScene();

	//auto scene = HelloWorld::createScene();
    // run
	director->runWithScene(scene);

	stack->executeScriptFile("lua/src/main.lua");
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
