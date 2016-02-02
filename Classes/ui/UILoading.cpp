#include "UILoading.h"
#include "GameScene.h"
#include "UIManager.h"
#pragma execution_character_set("utf-8")

UILoading::UILoading() :
_loadBar(NULL),
_loadtext(NULL),
_delta(1),
_destPercent(0),
_isScroll(false)
{

}

UILoading::~UILoading()
{

}

bool UILoading::init()
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
	_csbFrame->setScale(scale);
	this->addChild(_csbRoot);
	if (_loadtext)
	{
		_loadtext->setVisible(false);
	}

	this->setLocalZOrder((int)UIZorder::order_load);
	return true;
}

void UILoading::update(float delta)
{
	int curPercent = _loadBar->getPercent();
	if (curPercent < _destPercent)
	{
		curPercent += _delta;
		_delta++;
		if (curPercent > 100)
		{
			curPercent = 100;
		}
		_loadBar->setPercent(curPercent);
	}
	else
	{
		if (curPercent == 100)
		{
			_isScroll = false;
			this->unscheduleUpdate();
			this->hide();
		}
	}
}

void UILoading::scrollToPercent(int percent)
{
	_delta = 1;
	_destPercent = percent;
	if (_isScroll == false)
	{
		this->scheduleUpdate();
		_isScroll = true;
	}
}

void UILoading::show()
{
	UIBaseNode::show();
	_loadBar->setPercent(0);
}


