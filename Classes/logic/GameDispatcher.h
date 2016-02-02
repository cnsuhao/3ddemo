#ifndef __GAMEDISPATCHER_H__
#define __GAMEDISPATCHER_H__

#include "CocosHead.h"
#include "GameEvent.h"

typedef std::function<void(Ref*, GameEvent*)> GameEventCallback;
struct Listener
{
	GameEventCallback	_callfunc;
	int					_id;
	int					_index;
	Ref*				_target;
	Listener(int id, int index, GameEventCallback func, Ref* target = nullptr) :_id(id), _index(index), _callfunc(func), _target(target){};
};
class GameDispatcher:public Node
{
public:
	GameDispatcher(){};

	virtual ~GameDispatcher();

	static GameDispatcher* create();

	bool init();

	void dispatcherGameEvent(GameEvent* gEvent,Ref* pSender);

	void dispatcherGameEventAndPause(GameEvent* gEvent, bool isCache = true);

	int addGameEventListener(int id, const GameEventCallback& callfunc, Ref* target = nullptr);

	void removeGameEventListener(Ref* target);

	void resumOnce();

	bool getIsCacheEvents();

	static GameDispatcher* getInstance();

	void doEmptyEvent();

	void cancelPaused();

	void clearCacheEvents();

	void sendEventToTarget(GameEvent* gEvent, Ref* target);
private:

	void checkCacheEvent(float dt);
private:
	bool				_isNextUpdate;
	bool				_isPause;
	int					_index;
	vector<Listener>	_events;
	vector<GameEvent*>	_cacheEvents;
	static GameDispatcher* _gGameDispatcher;
};






#endif