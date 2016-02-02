#include "UIRocker.h"
#include "GameScene.h"
#include "UIManager.h"
#include "GameObject3DMgr.h"
#pragma execution_character_set("utf-8")

UIRocker::UIRocker()
{

}

UIRocker::~UIRocker()
{

}

bool UIRocker::init()
{
	auto csbRoot = dynamic_cast<Layout*>(GUIReader::getInstance()->widgetFromBinaryFile("ui/rocker/rocker.csb"));
	if (!csbRoot)
	{
		return false;
	}
	auto scale = UIManager::getInstance()->getFullHeightScale();
	this->setCsbRoot(csbRoot);
	_csbPlist.push_back("ui/rocker/rocker0.plist");
	_csbFrame = dynamic_cast<Widget*>(Helper::seekWidgetByName(_csbRoot, "frame"));
	_imgFrame = dynamic_cast<ImageView*>(Helper::seekWidgetByName(_csbRoot,"img_bk"));
	_imgCenter = dynamic_cast<ImageView*>(Helper::seekWidgetByName(_csbRoot, "img_center"));
	this->addChild(_csbRoot);
	this->setLocalZOrder((int)UIZorder::order_mainfront);


	_imgCenter->setTouchEnabled(true);
	_imgCenter->addTouchEventListener(CC_CALLBACK_2(UIRocker::onRockerTouchClickCallBack,this));
	_centerPos = _imgCenter->getPosition();
	_r = _imgFrame->getContentSize().width / 2;

	return true;
}

void UIRocker::onRockerTouchClickCallBack(Ref* sender, Widget::TouchEventType touchType)
{
	Point pos = Point::ZERO;
	if (touchType == Widget::TouchEventType::BEGAN)
	{
		this->scheduleUpdate();
		pos = _csbFrame->convertToNodeSpace(_imgCenter->getTouchBeganPosition());
		updateRockerPos(pos);
	}
	else if (touchType == Widget::TouchEventType::MOVED)
	{
		pos = _csbFrame->convertToNodeSpace(_imgCenter->getTouchMovePos());
		updateRockerPos(pos);
	}
	else if (touchType == Widget::TouchEventType::ENDED || touchType == Widget::TouchEventType::CANCELED)
	{
		//
		_imgCenter->setPosition(_centerPos);
		this->unscheduleUpdate();
		auto mainPlayer = GameObject3DMgr::getInstance()->getMainGamePlayer();
		if (mainPlayer)
		{
			mainPlayer->stop();
		}
	}
}

void UIRocker::updateRockerPos(Point pos)
{
	// 角度
	Point d_pos = pos - _centerPos;
	float rotation = d_pos.getAngle();
	//是否在范围内
	if (d_pos.x * d_pos.x + d_pos.y * d_pos.y > _r * _r)
	{
		pos.x = _centerPos.x + _r * cos(rotation);
		pos.y = _centerPos.y + _r * sin(rotation);
	}

	rotation = rotation * 180.0f / 3.14f + 90.f;
	_rotation = rotation < 0 ? rotation + 360 : rotation;
	_imgCenter->setPosition(pos);

}

void UIRocker::update(float dt)
{
	auto mainPlayer = GameObject3DMgr::getInstance()->getMainGamePlayer();
	if (mainPlayer)
	{
		mainPlayer->setDirAndAnimState(_rotation, ActMotion::walk);
	}
}



