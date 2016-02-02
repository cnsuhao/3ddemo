#include "UISelTarget.h"
#include "GameScene.h"
#include "UIManager.h"

#pragma execution_character_set("utf-8")

UISelTarget::UISelTarget()
{
	_target = nullptr;
	_hpBar = nullptr;
	_mpBar = nullptr;
	_hpText = nullptr;
	_mpText = nullptr;
	_nameText = nullptr;
}

UISelTarget::~UISelTarget()
{

}

bool UISelTarget::init()
{
	auto csbRoot = dynamic_cast<Layout*>(GUIReader::getInstance()->widgetFromBinaryFile("ui/seltarget/seltarget.csb"));
	if (!csbRoot)
	{
		return false;
	}
	this->setCsbRoot(csbRoot);
	_csbPlist.push_back("ui/seltarget/seltarget0.plist");
	_csbFrame = dynamic_cast<Widget*>(Helper::seekWidgetByName(_csbRoot, "frame"));
	_hpBar = dynamic_cast<LoadingBar*>(Helper::seekWidgetByName(_csbRoot,"hpbar"));
	_mpBar = dynamic_cast<LoadingBar*>(Helper::seekWidgetByName(_csbRoot, "mpbar"));
	_hpText = dynamic_cast<Text*>(Helper::seekWidgetByName(_csbRoot, "hptext"));
	_mpText = dynamic_cast<Text*>(Helper::seekWidgetByName(_csbRoot, "mptext"));
	_nameText = dynamic_cast<Text*>(Helper::seekWidgetByName(_csbRoot, "name"));
	this->addChild(_csbRoot);
	this->setLocalZOrder((int)UIZorder::order_mainfront);

	UIManager::getInstance()->getDispatcher()->addGameEventListener((int)GameEventId::load_end, CC_CALLBACK_2(UISelTarget::onLoadEndEvent, this), this);

	return true;
}


void UISelTarget::refreshTargetInfo()
{
	if (_target)
	{
		int hp = _target->getObjectData()->m_hp;
		int hp_m = _target->getObjectData()->m_hpMax;
		int mp = _target->getObjectData()->m_mp;
		int mp_m = _target->getObjectData()->m_mpMax;
		_hpBar->setPercent(100.0f * hp / hp_m);
		_mpBar->setPercent(100.0f * mp / mp_m);
		_hpText->setString(StringUtils::format("%d/%d", hp, hp_m));
		_mpText->setString(StringUtils::format("%d/%d", mp, mp_m));
		_nameText->setString(_target->getObjectData()->m_name);
	}
}

void UISelTarget::onHPChangeEvent(Ref* pSender, GameEvent* gEvent)
{
	refreshTargetInfo();
}

void UISelTarget::onSelTargetEvent(Ref* pSender, GameEvent* gEvent)
{
	if (_target)
	{
		_target->getLogicDispatcher()->removeGameEventListener(this);
	}
	_target = GameObjectMgr::getInstance()->getMainGamePlayer()->getTarget();
	if (_target)
	{
		_target->getLogicDispatcher()->addGameEventListener(HPChangeEvent_ID, CC_CALLBACK_2(UISelTarget::onHPChangeEvent, this), this);
		show();
		refreshTargetInfo();
	}
	else
	{
		hide();
	}
}

void UISelTarget::onLoadEndEvent(Ref* pSender, GameEvent* gEvent)
{
	_target = nullptr;

	GamePlayer* mainPlayer = GameObjectMgr::getInstance()->getMainGamePlayer();
	if (mainPlayer)
	{
		mainPlayer->getLogicDispatcher()->addGameEventListener((int)GameEventId::sel_target, CC_CALLBACK_2(UISelTarget::onSelTargetEvent, this), this);
	}
}


