#include "GameDispatcher.h"

GameDispatcher* GameDispatcher::_gGameDispatcher = nullptr;

GameDispatcher* GameDispatcher::create()
{
	GameDispatcher* dispather = new GameDispatcher;
	if (dispather)
	{
		dispather->init();
		dispather->autorelease();

	}
	return dispather;
}

bool GameDispatcher::init()
{
	_events.clear();
	_index = 0;
	_isPause = false;
	_isNextUpdate = false;
	
	Director::getInstance()->getScheduler()->schedule(CC_CALLBACK_1(GameDispatcher::checkCacheEvent, this), this, 0.0f, false, "checkCacheEvent");

	return true;
}

int GameDispatcher::addGameEventListener(int id, const GameEventCallback& callfunc, Ref* target)
{
	_index++;
	_events.push_back(Listener(id, _index, callfunc, target));
	return _index;
}

void GameDispatcher::dispatcherGameEvent(GameEvent* gEvent, Ref* pSender)
{
	if (gEvent)
	{
		vector<Listener> events = _events;
		for (auto it : events)
		{
			if (it._id == (int)(gEvent->getEventId()))
			{
				CCLOG("dispatcherGameEvent bengin %d", it._id);
				it._callfunc(pSender, gEvent);
				CCLOG("dispatcherGameEvent end    %d", it._id);
			}
		}
	}
}

void GameDispatcher::removeGameEventListener(Ref* target)
{
	auto iter = remove_if(_events.begin(), _events.end(), [=](Listener p)
	{
		if (p._target == target)
		{
			return true;
		}
		return false;
	});
	_events.erase(iter, _events.end());
}

GameDispatcher* GameDispatcher::getInstance()
{
	if (!_gGameDispatcher)
	{
		_gGameDispatcher = GameDispatcher::create();
		_gGameDispatcher->retain();
	}
	return _gGameDispatcher;
}

void GameDispatcher::dispatcherGameEventAndPause(GameEvent* gEvent, bool isCache /*= true*/)
{
	// 是否缓存
	if (isCache == true && _isPause == true)
	{
		// 判断是否缓存有
		auto iter = std::find(_cacheEvents.begin(), _cacheEvents.end(), gEvent);
		if (iter != _cacheEvents.end())
		{
			return;
		}
		gEvent->retain();
		_cacheEvents.push_back(gEvent);
	}
	else
	{
		_isPause = true;
		dispatcherGameEvent(gEvent, this);
	}
}

void GameDispatcher::resumOnce()
{
	if (_isNextUpdate == false)
	{
		_isNextUpdate = true;
		//auto scheduler = Director::getInstance()->getScheduler();
		//if (scheduler && scheduler->isScheduled("checkCacheEvent",this) == false)
		//{
		//	Director::getInstance()->getScheduler()->schedule(CC_CALLBACK_1(GameDispatcher::checkCacheEvent, this), this, 0.0f, 1, 0.0f, false, "checkCacheEvent");
		//}
	}
	//this->scheduleOnce(schedule_selector(GameDispatcher::checkCacheEvent), 0.01f);
	//Director::getInstance()->getScheduler()->schedule(schedule_selector(GameDispatcher::checkCacheEvent), this, 0.0f, false);
}

void GameDispatcher::checkCacheEvent(float dt)
{
	if (_isNextUpdate == true)
	{
		_isNextUpdate = false;
		if (_cacheEvents.empty() == false)
		{
			int s = _cacheEvents.size();
			GameEvent* gEvent = _cacheEvents[0];
			dispatcherGameEvent(gEvent, this);
			CC_SAFE_RELEASE_NULL(gEvent);
			_cacheEvents.erase(_cacheEvents.begin());
		}
		else
		{
			doEmptyEvent();
		}
	}

}

void GameDispatcher::doEmptyEvent()
{
	_isPause = false;
	auto gEvent = GameEvent::create((GameEventId)AnimEventEmpty_ID);
	dispatcherGameEvent(gEvent, this);
}

bool GameDispatcher::getIsCacheEvents()
{
	return !(_cacheEvents.empty());
}

void GameDispatcher::cancelPaused()
{
	_isPause = false;
}

void GameDispatcher::clearCacheEvents()
{
	for (auto it :_cacheEvents)
	{
		it->release();
	}
	_cacheEvents.clear();
}

GameDispatcher::~GameDispatcher()
{
	Director::getInstance()->getScheduler()->unscheduleAllForTarget(this);
}

void GameDispatcher::sendEventToTarget(GameEvent* gEvent, Ref* target)
{
	if (gEvent)
	{
		vector<Listener> events = _events;
		for (auto it : events)
		{
			if (it._target == target && it._id == (int)(gEvent->getEventId()))
			{
				it._callfunc(this, gEvent);
			}
		}
	}
}

