#include "UIMiniMap.h"
#include "GameScene.h"
#include "UIManager.h"
#include "GameAtlasMgr.h"
#include "GameObject3DMgr.h"
#include "ObjectData3DMgr.h"
#include "GameAI.h"
#pragma execution_character_set("utf-8")

UIMiniMap::UIMiniMap():
UIBaseNode(),
m_posText(nullptr)
{
	
}

UIMiniMap::~UIMiniMap()
{

}

bool UIMiniMap::init()
{
	auto csbRoot = dynamic_cast<Layout*>(GUIReader::getInstance()->widgetFromBinaryFile("ui/minimap/minimap.csb"));
	if (!csbRoot)
	{
		return false;
	}
	this->setCsbRoot(csbRoot);
	float scale = UIManager::getInstance()->getFullHeightScale();
	_csbPlist.push_back("ui/minimap/minimap0.plist");

	m_posText = dynamic_cast<Text*>(Helper::seekWidgetByName(_csbRoot, "Label_pos"));
	if (m_posText)
	{
		m_posText->setFontSize(18);
	}
	Button* transBtn = dynamic_cast<Button*>(Helper::seekWidgetByName(_csbRoot, "chuansongbtn"));
	if (transBtn)
	{
		transBtn->addClickEventListener(CC_CALLBACK_1(UIMiniMap::onTransBtnTouchClickCallBack, this));
	}
	Button* autoBtn = dynamic_cast<Button*>(Helper::seekWidgetByName(_csbRoot, "zhandoubtn"));
	if (autoBtn)
	{
		autoBtn->addClickEventListener(CC_CALLBACK_1(UIMiniMap::onAutoBtnTouchClickCallBack, this));
	}
	ImageView* bkImg = dynamic_cast<ImageView*>(Helper::seekWidgetByName(_csbRoot, "Image_quan"));
	if (bkImg)
	{
		bkImg->setTouchEnabled(true);
		bkImg->addClickEventListener(CC_CALLBACK_1(UIMiniMap::onMapPanelTouchClickCallBack, this));
	}
	m_slider = dynamic_cast<Slider*>(Helper::seekWidgetByName(_csbRoot, "slider"));
	if (m_slider)
	{
		m_slider->setVisible(false);
		m_slider->addEventListener(CC_CALLBACK_2(UIMiniMap::onSliderTouchEventCallBack, this));
	}
	m_speedText = dynamic_cast<Text*>(Helper::seekWidgetByName(_csbRoot,"speedText"));
	this->addChild(_csbRoot);
	this->setLocalZOrder((int)UIZorder::order_mainfront);
	// 监听主角位置改变
	auto mainPlayer = GameObject3DMgr::getInstance()->getMainGamePlayer();
	if (mainPlayer)
	{
		mainPlayer->getLogicDispatcher()->addGameEventListener((int)GameEventId::update_pos, CC_CALLBACK_2(UIMiniMap::onUpdateMainPlayerPosEvent, this), this);
	}
	// 初始化信息
	updateMainPlayerPos();
	updateMainPlayerSpeed();
	return true;
}

void UIMiniMap::updateMainPlayerPos()
{
	auto mainPlayer = GameObject3DMgr::getInstance()->getMainGamePlayer();
	if (mainPlayer && m_posText)
	{
		Point point = mainPlayer->getTilePos();
		string str = StringUtils::format("(%d,%d)",(int) point.x, (int)point.y);
		m_posText->setString(str);
	}
}

void UIMiniMap::onUpdateMainPlayerPosEvent(Ref* pSender, GameEvent* gEvent)
{
	updateMainPlayerPos();
}


void UIMiniMap::show()
{
	UIBaseNode::show();
}

void UIMiniMap::hide()
{
	UIBaseNode::hide();
}

void UIMiniMap::onMapPanelTouchClickCallBack(Ref* sender)
{
	bool isVisible = m_slider->isVisible();
	m_slider->setVisible(!isVisible);
	auto gEvent = GameEvent::create(GameEventId::grid_changeshow);
	UIManager::getInstance()->getDispatcher()->dispatcherGameEvent(gEvent, this);
}

void UIMiniMap::onSliderTouchEventCallBack(Ref* sender, Slider::EventType stype)
{
	if (stype == Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		auto mainPlayer = GameObject3DMgr::getInstance()->getMainGamePlayer();
		if (mainPlayer)
		{
			float speed = m_slider->getPercent();
			mainPlayer->setSpeed(speed);
			m_speedText->setString(StringUtils::format("%f", speed));
		}
	}
}

void UIMiniMap::updateMainPlayerSpeed()
{
	auto mainPlayer = GameObject3DMgr::getInstance()->getMainGamePlayer();
	if (mainPlayer)
	{
		float speed = mainPlayer->getSpeed();
		m_slider->setPercent(speed);
		m_speedText->setString(StringUtils::format("%f", speed));
	}
}


void UIMiniMap::onAutoBtnTouchClickCallBack(Ref* sender)
{

}

void UIMiniMap::onTransBtnTouchClickCallBack(Ref* sender)
{

}
