#include "UIUpdate.h"
#include "GameScene.h"
#include "UIManager.h"
#pragma execution_character_set("utf-8")

UIUpdate::UIUpdate():
_loadBar(NULL),
_loadtext(NULL)
{

}

UIUpdate::~UIUpdate()
{

}

bool UIUpdate::init()
{
	auto csbRoot = dynamic_cast<Layout*>(GUIReader::getInstance()->widgetFromBinaryFile("ui/update/update.csb"));
	if (!csbRoot)
	{
		return false;
	}
	auto scale = UIManager::getInstance()->getFullScreenScale();
	this->setCsbRoot(csbRoot);
	_csbPlist.push_back("ui/update/update0.plist");
	_csbFrame = dynamic_cast<Widget*>(Helper::seekWidgetByName(_csbRoot, "frame"));
	_loadBar = dynamic_cast<LoadingBar*>(Helper::seekWidgetByName(_csbRoot,"bar"));
	_loadtext = dynamic_cast<Text*>(Helper::seekWidgetByName(_csbRoot, "text"));
	this->addChild(_csbRoot);
	_csbFrame->setScale(scale);

	// 创建更新
	_downManager = DownManager::create();
	_downManager->setErrorCallback(CC_CALLBACK_1(UIUpdate::ErrorCallback,this));
	_downManager->setProgressCallback(CC_CALLBACK_1(UIUpdate::ProgressCallback, this));
	_downManager->setSuccessCallback(CC_CALLBACK_1(UIUpdate::SuccessCallback, this));
	_downManager->setStateCallback(CC_CALLBACK_1(UIUpdate::StateCallback, this));
	_downManager->retain();
	_loadtext->setString("正在检查更新...");

	this->scheduleOnce(schedule_selector(UIUpdate::checkUpdate),0.5f);
	return true;
}



void UIUpdate::ErrorCallback(int code)
{
	CCLOG("ErrorCallback%d", code);
	string tipmsg = "";
	switch (code)
	{
	case (int)DownManager::ErrorCode::CREATE_FILE:
	{
		tipmsg = "创建文件失败";
	}
		break;

	case (int)DownManager::ErrorCode::NETWORK:
	{
		tipmsg = "网络错误";
	}
		break;
	case (int)DownManager::ErrorCode::UNCOMPRESS:
	{
		tipmsg = "解压失败";
	}
		break;
	}
	_loadtext->setString(tipmsg);

	CC_SAFE_RELEASE_NULL(_downManager);
	UIManager::destroyInstance();
	// 跳转场景
	Scene* scene = GameScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

void UIUpdate::ProgressCallback(int percent)
{
	int index = _downManager->getDownIndex();
	int maxnum = _downManager->getMaxDownNum();
	_loadBar->setPercent(percent);
	_loadtext->setString(StringUtils::format("正在下载(%d/%d)", index, maxnum));
}

void UIUpdate::SuccessCallback(int code)
{
	_loadtext->setString("更新成功");
	CC_SAFE_RELEASE_NULL(_downManager);

	UIManager::destroyInstance();
	// 跳转场景
	Scene* scene = GameScene::createScene();
	Director::getInstance()->replaceScene(scene);

	//this->hide();
}

void UIUpdate::StateCallback(int code)
{
	CCLOG("UIUpdate state %d", code);
}

void UIUpdate::checkUpdate(float delta)
{
	// 检测更新
	_downManager->update();
}
