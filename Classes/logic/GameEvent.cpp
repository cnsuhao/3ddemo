#include "GameEvent.h"


GameEvent* GameEvent::create(const GameEventId& id)
{
	GameEvent* ptr = new GameEvent;
	if (ptr)
	{
		ptr->init(id);
		ptr->autorelease();
	}

	return ptr;
}

void GameEvent::init(GameEventId id)
{
	_id = id;

	_paramStr = "";
	_paramInt1 = 0;
	_paramInt2 = 0;
}

GameEventId GameEvent::getEventId()
{
	return _id;
}

void GameEvent::setParamStr(string str)
{
	_paramStr = str;
}

std::string GameEvent::getParamStr()
{
	return _paramStr;
}

void GameEvent::setParamInt1(int value)
{
	_paramInt1 = value;
}

int GameEvent::getParamInt1()
{
	return _paramInt1;
}


void GameEvent::setParamInt2(int value)
{
	_paramInt2 = value;
}

int GameEvent::getParamInt2()
{
	return _paramInt2;
}

void UICreateEvent::setUIType(int type)
{
	_uitype = type;
}

int UICreateEvent::getUIType()
{
	return _uitype;
}

void UICreateEvent::setUIBaseNode(UIBaseNode* node)
{
	_node = node;
}

UIBaseNode* UICreateEvent::getUIBaseNode()
{
	return _node;
}

UICreateEvent* UICreateEvent::create(const GameEventId& id)
{
	UICreateEvent* ptr = new UICreateEvent;
	if (ptr)
	{
		ptr->init(id);
		ptr->autorelease();
	}

	return ptr;
}


GameAnimEvent* GameAnimEvent::create()
{
	GameAnimEvent* ptr = new GameAnimEvent;
	if (ptr)
	{
		ptr->init((GameEventId)AnimEventState_ID);
		ptr->autorelease();
	}
	return ptr;
}

void GameAnimEvent::copy(GameAnimEvent* gEvent)
{
	m_animState = gEvent->m_animState;
	m_dir = gEvent->m_dir;
	m_effectId = gEvent->m_effectId;
	m_skillId = gEvent->m_skillId;
	m_callBack = gEvent->m_callBack;
	
}

void GameAnimEvent::init(GameEventId id)
{
	GameEvent::init(id);

	m_dir = ActDir::DIR_DOWN;
	m_effectId = 0;
	m_skillId = 0;
	m_callBack = nullptr;
}

GameFindPathEvent* GameFindPathEvent::create()
{
	GameFindPathEvent* ptr = new GameFindPathEvent;
	if (ptr)
	{
		ptr->init((GameEventId)FindPathEvent_ID);
		ptr->autorelease();
	}
	return ptr;
}
