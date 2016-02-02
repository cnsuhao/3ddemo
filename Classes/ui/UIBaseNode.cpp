#include "UIBaseNode.h"
#include "GameEvent.h"
#include "UIManager.h"

UIBaseNode::UIBaseNode()
{
	_csbRoot = nullptr;
	_csbFrame = nullptr;
	_isVisible = false;
	_initfunc = nullptr;
}

UIBaseNode::~UIBaseNode()
{
	for (int i = 0; i < _csbPlist.size(); ++i)
	{
		SpriteFrameCache::getInstance()->removeSpriteFramesFromFile(_csbPlist[i]);
	}
	_csbPlist.clear();
	auto gameEvet = GameEvent::create(GameEventId::ui_destroy);
	UIManager::getInstance()->getDispatcher()->dispatcherGameEvent(gameEvet, this);
	TextureCache::getInstance()->removeUnusedTextures();
}

void UIBaseNode::show()
{
	_isVisible = true;
	this->setVisible(true);

	// 取消删除
	this->unschedule(schedule_selector(UIBaseNode::scheduleRemoveCsb));
	if (_csbRoot == nullptr && _initfunc)
	{
		_initfunc();
	}
	auto gameEvet = GameEvent::create(GameEventId::ui_show);
	UIManager::getInstance()->getDispatcher()->sendEventToTarget(gameEvet, this);
}

void UIBaseNode::hide()
{
	_isVisible = false;
	this->setVisible(false);
	auto gameEvet = GameEvent::create(GameEventId::ui_hide);
	UIManager::getInstance()->getDispatcher()->sendEventToTarget(gameEvet, this);
	if (_csbRoot && _initfunc)
	{
		// 定时删除
		this->scheduleOnce(schedule_selector(UIBaseNode::scheduleRemoveCsb), 5.0f);
	}
}

bool UIBaseNode::init()
{
	return true;
}

bool UIBaseNode::isShow()
{
	return _isVisible;
}

void UIBaseNode::update(float delta)
{

}

void UIBaseNode::setCsbRoot(Layout* csb)
{
	_csbRoot = csb;
	Size uiSize = UIManager::getInstance()->getUISize();
	_csbRoot->setContentSize(uiSize);
}

void UIBaseNode::addCsbPlist(string plist)
{
	_csbPlist.push_back(plist);
}

void UIBaseNode::setCsbFrame(Widget* frame)
{
	_csbFrame = frame;
}

void UIBaseNode::setInitCsbFunc(initcsbfunc initfunc)
{
	_initfunc = initfunc;
}

void UIBaseNode::scheduleRemoveCsb(float delta)
{
	if (_csbRoot)
	{
		this->removeChild(_csbRoot);
		for (auto plist:_csbPlist)
		{
			SpriteFrameCache::getInstance()->removeSpriteFramesFromFile(plist);
		}
		_csbPlist.clear();
		_csbRoot = nullptr;
		_csbFrame = nullptr;
		TextureCache::getInstance()->removeUnusedTextures();
	}
}
