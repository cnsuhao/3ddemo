#include "UIManager.h"
#include "UIUpdate.h"
#include "UILogin.h"
#include "UIChat.h"
#include "UILoading.h"
#include "UIRocker.h"
#include "UISkilPanel.h"
#include "UISelTarget.h"
#include "Global.h"
#include "GameAI.h"
#include "GamePlayer.h"
#include "GameObjectMgr.h"
#include "UIWorldMap.h"
#include "UIMiniMap.h"
UIManager*  UIManager::_uiManager = NULL;

UIManager::UIManager():
_dispatcher(nullptr)
{
	
}

UIManager::~UIManager()
{
	CC_SAFE_RELEASE_NULL(_dispatcher);
}

UIManager* UIManager::getInstance()
{
	if (!_uiManager)
	{
		_uiManager = new UIManager;
		_uiManager->init();
	}
	return _uiManager;
}

void UIManager::destroyInstance()
{
	_uiManager->_uiList.clear();
	CC_SAFE_RELEASE_NULL(_uiManager);
}

UIBaseNode* UIManager::showUI(UIType uiType)
{
	UIBaseNode* base = _uiList[uiType];
	if (!base)
	{
		base = createUI(uiType);
	}
	if (base && base->isShow() == false)
	{
		base->show();
	}
	return base;
}

void UIManager::hideUI(UIType uiType)
{
	UIBaseNode* base = _uiList[uiType];
	if (base)
	{
		base->hide();
	}
}

bool UIManager::isShow(UIType uiType)
{
	UIBaseNode* base = _uiList[uiType];
	if (base)
	{
		return base->isShow();
	}
	return false;
}

UIBaseNode* UIManager::createUI(UIType uiType)
{
	UIBaseNode* base = getUI(uiType);
	if (base) return base;
	// 优先Lua
	UICreateEvent* cEvent = UICreateEvent::create(GameEventId::ui_create);
	cEvent->setUIType((int)uiType);
	GameDispatcher::getInstance()->dispatcherGameEvent(cEvent, this);
	base = cEvent->getUIBaseNode();
	// 没有再C++
	if (base == nullptr)
	{
		switch (uiType)
		{
		case UIType::UI_Update:
			base = UIUpdate::create();
			break;
		case UIType::UI_Login:
			base = UILogin::create();
			break;
		case UIType::UI_Chat:
			base = UIChat::create();
			break;
		case UIType::UI_Loading:
			base = UILoading::create();
			break;
		case UIType::UI_Rocker:
			base = UIRocker::create();
			break;
		case UIType::UI_SkillPanel:
			base = UISkillPanel::create();
			break;
		case UIType::UI_SelTarget:
			base = UISelTarget::create();
			break;
		case UIType::UI_WorldMap:
			base = UIWorldMap::create();
			break;
		case UIType::UI_MiniMap:
			base = UIMiniMap::create();
			break;
		default:
			break;
		}
	}
	// 添加进去
	if (base)
	{
		_uiList[uiType] = base;
		this->addChild(base);
	}
	return base;
}

UIBaseNode* UIManager::getUI(UIType uiType)
{
	UIBaseNode* base = _uiList[uiType];
	if (base)
	{
		return base;
	}
	return NULL;
}

void UIManager::loadUI(int percent)
{
	auto loadUI = dynamic_cast<UILoading*>(showUI(UIType::UI_Loading));
	if (loadUI)
	{
		loadUI->scrollToPercent(percent);
	}
}

bool UIManager::init()
{
	_dispatcher = GameDispatcher::create();
	_dispatcher->retain();

	// 分辨率设置缩放
	auto director = Director::getInstance();
	auto glView = director->getOpenGLView();
	auto screenSize = glView->getFrameSize();
	float scaleX = screenSize.width / designSize.width;
	float scaleY = screenSize.height / designSize.height;
	float minScale = MIN(scaleX, scaleY);
	float maxScale = MAX(scaleX, scaleY);
	_scale = minScale / maxScale;
	Size vSize = director->getVisibleSize();
	_uiSize = vSize / _scale;
	this->setScale(_scale);
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	this->setPosition(origin);

	// 横着的
	if (scaleX > scaleY)
	{
		_scaleW = 1 / _scale;
		_scaleH = 1;
	}
	else
	{
		_scaleW = 1;
		_scaleH = 1 / _scale;
	}
	return true;
}

GameDispatcher* UIManager::getDispatcher()
{
	return _dispatcher;
}

Size UIManager::getUISize()
{
	return _uiSize;
}

float UIManager::getUIScale()
{
	return _scale;
}

float UIManager::getFullScreenScale()
{
	return 1 / _scale;
}

float UIManager::getFullWidthScale()
{
	return _scaleW;
}

float UIManager::getFullHeightScale()
{
	return _scaleH;
}

void UIManager::setIsAutoFight(bool isAuto)
{
	GamePlayer* mainPlayer = GameObjectMgr::getInstance()->getMainGamePlayer();
	if (mainPlayer)
	{
		mainPlayer->getDoSkill()->setIsAutoFight(isAuto);
	}
}

void UIManager::hideWithCreate(UIType uiType)
{
	UIBaseNode* ui = createUI(uiType);
	if (ui)
	{
		ui->hide();
	}
}

void UIManager::hideAllUI()
{
	for (auto iter : _uiList)
	{
		if (iter.second && iter.second->isVisible())
		{
			iter.second->hide();
		}
	}
}
