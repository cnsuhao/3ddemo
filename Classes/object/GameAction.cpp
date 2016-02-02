#include "GameAction.h"
#include "GameMap.h"


GameAnimate::GameAnimate():
Animate(),
_func(nullptr),
_object(nullptr)
{

}

GameAnimate::~GameAnimate()
{

}


GameAnimate* GameAnimate::create(Animation *animation)
{
	GameAnimate *animate = new (std::nothrow) GameAnimate();
	animate->initWithAnimation(animation);
	animate->autorelease();

	return animate;
}


void GameAnimate::stop(void)
{
	if (_func)
	{
		_func(_object);
	}
	// 检测队列是否为空
	if (_object)
	{
		_object->getActionDispatcher()->resumOnce();
	}
	Animate::stop();
}

void GameAnimate::update(float t)
{
	if (t < 1.0f) {
		t *= _animation->getLoops();

		// new loop?  If so, reset frame counter
		unsigned int loopNumber = (unsigned int)t;
		if (loopNumber > _executedLoops) {
			_nextFrame = 0;
			_executedLoops++;
		}

		// new t for animations
		t = fmodf(t, 1.0f);
	}

	auto frames = _animation->getFrames();
	auto numberOfFrames = frames.size();
	SpriteFrame *frameToDisplay = nullptr;

	for (int i = _nextFrame; i < numberOfFrames; i++) {
		float splitTime = _splitTimes->at(i);

		if (splitTime <= t) {
			AnimationFrame* frame = frames.at(i);
			frameToDisplay = frame->getSpriteFrame();
			static_cast<Sprite*>(_target)->setSpriteFrame(frameToDisplay);
			_object->updateOtherAnim(i, t);
			const ValueMap& dict = frame->getUserInfo();
			if (!dict.empty())
			{
				if (_frameDisplayedEvent == nullptr)
					_frameDisplayedEvent = new (std::nothrow) EventCustom(AnimationFrameDisplayedNotification);

				_frameDisplayedEventInfo.target = _target;
				_frameDisplayedEventInfo.userInfo = &dict;
				_frameDisplayedEvent->setUserData(&_frameDisplayedEventInfo);
				Director::getInstance()->getEventDispatcher()->dispatchEvent(_frameDisplayedEvent);
			}
			_nextFrame = i + 1;
		}
		// Issue 1438. Could be more than one frame per tick, due to low frame rate or frame delta < 1/FPS
		else {
			break;
		}
	}
}

void GameAnimate::setGameObject(GameObject* object)
{
	_object = object;
}

void GameAnimate::setCallBack(GameEventCallback1 func)
{
	_func = func;
}



//GameRunAnimate----------------------------------------------------------

GameRunAnimate::GameRunAnimate() :
Animate(),
_isDone(false),
_isFindPath(false),
_pathNode(nullptr)
{
	_firstTick = true;
}

GameRunAnimate::~GameRunAnimate()
{
	if (_pathNode)
	{
		_pathNode->clear();
		_pathNode = nullptr;
	}
}


GameRunAnimate* GameRunAnimate::create(GameObject* object)
{
	GameRunAnimate *animate = new (std::nothrow) GameRunAnimate();
	//animate->initWithAnimation(animation);
	animate->_object = object;
	animate->autorelease();

	return animate;
}


void GameRunAnimate::stop(void)
{
	// 检测队列是否为空
	if (_object)
	{
		_object->getActionDispatcher()->resumOnce();
		_object->updateData();
	}
	_object = nullptr;
	//Animate::stop();
}

void GameRunAnimate::update(float t)
{
	if (_animation == nullptr) return;
	// if t==1, ignore. Animation should finish with t==1
	if (t < 1.0f) {
		t *= _animation->getLoops();

		// new loop?  If so, reset frame counter
		unsigned int loopNumber = (unsigned int)t;
		if (loopNumber > _executedLoops) {
			_nextFrame = 0;
			_executedLoops++;
		}

		// new t for animations
		t = fmodf(t, 1.0f);
	}
	else
	{
		// 完成
		// _isDone = true;
		// return;
	}

	// 移动位置
	Point curp = _object->getPosition();
	Point nexp = curp + _d * (t - _t);
	_object->setPosition(nexp);
	if (_object->getObjectType() == ObjectType::mainplayer)
	{
		GameMap::getInstance()->adjustPosition();
	}
	_t = t;
	// 动画帧刷新
	auto frames = _animation->getFrames();
	auto numberOfFrames = frames.size();
	SpriteFrame *frameToDisplay = nullptr;

	for (int i = _nextFrame; i < numberOfFrames; i++) {
		float splitTime = _splitTimes->at(i);

		if (splitTime <= t) {
			AnimationFrame* frame = frames.at(i);
			frameToDisplay = frame->getSpriteFrame();
			static_cast<Sprite*>(_target)->setSpriteFrame(frameToDisplay);
			_object->updateOtherAnim(i, t);
			const ValueMap& dict = frame->getUserInfo();
			if (!dict.empty())
			{
				if (_frameDisplayedEvent == nullptr)
					_frameDisplayedEvent = new (std::nothrow) EventCustom(AnimationFrameDisplayedNotification);

				_frameDisplayedEventInfo.target = _target;
				_frameDisplayedEventInfo.userInfo = &dict;
				_frameDisplayedEvent->setUserData(&_frameDisplayedEventInfo);
				Director::getInstance()->getEventDispatcher()->dispatchEvent(_frameDisplayedEvent);
			}
			_nextFrame = i + 1;
		}
		// Issue 1438. Could be more than one frame per tick, due to low frame rate or frame delta < 1/FPS
		else {
			break;
		}
	}
}


void GameRunAnimate::startWithTarget(Node *target)
{
	// 初始化数据
	this->checkState();

	ActionInterval::startWithTarget(target);
	Sprite *sprite = static_cast<Sprite*>(target);

	CC_SAFE_RELEASE(_origFrame);
	if (_animation)
	{
		if (_animation->getRestoreOriginalFrame())
		{
			_origFrame = sprite->getSpriteFrame();
			_origFrame->retain();
		}
	}
	else
	{
		CCLOG("animation is null");
	}
}

void GameRunAnimate::checkState()
{
	_nextFrame = 0;
	_executedLoops = 0;
	_d = Point::ZERO;
	_t = 0;
	_elapsed = 0;

	_object->updateData();
	_startPos = _object->getPosition();
	Point nowPos = _object->getObjectData()->m_pos;
	Size mapSize = GameMap::getInstance()->getMapSize();
	if (_isFindPath)
	{
		bool isCached = _object->getActionDispatcher()->getIsCacheEvents();
		if (!_firstTick && isCached)
		{
			_isDone = true;
			return;
		}
		//
		if (_pathNode && _pathNode->next)
		{
			_pathNode = _pathNode->nextNode();
			_tilePos = Point(_pathNode->m_x, _pathNode->m_y);
			_dir = getDirByPoint(Point(nowPos.x, mapSize.height - nowPos.y), Point(_tilePos.x, mapSize.height - _tilePos.y));
			_endPos = GameMap::getInstance()->convertTilePosToNodePos(_tilePos);
			_object->setDirNoUpdate(_dir);
		} 
		else
		{
			_isDone = true;
			return;
		}
	}
	else
	{
		_dir = _object->getDir();
		_tilePos = _object->getObjectData()->m_pos;
		_tilePos = getNextPostion(_tilePos, _dir);
		if (!GameMap::getInstance()->canMove(_tilePos.x, _tilePos.y))
		{
			_isDone = true;
			return;
		}
		_endPos = GameMap::getInstance()->convertTilePosToNodePos(_tilePos);
	}

	auto animation = _object->getAnimation();
	if (animation)
	{
		this->initWithAnimation(animation);
	}
	else
	{
		CCLOG("getAnimation  null");
	}
	// 坐标 
	_d = _endPos - _startPos;
	_object->setTilePos(_tilePos);
	// 时间
	ActDir dir = _object->getDir();
	if (dir == ActDir::DIR_DOWNRIGHT || dir == ActDir::DIR_LEFTDOWN || dir == ActDir::DIR_LEFTUP || dir == ActDir::DIR_UPRIGHT)
	{
		float d = _animation->getDelayPerUnit();
		this->_animation->setDelayPerUnit(d * 1.414);
	}
}

void GameRunAnimate::setPathNode(ptr_PathNode node)
{
	_pathNode = node;
}

void GameRunAnimate::setIsFindPath(bool isFind)
{
	_isFindPath = isFind;
}

bool GameRunAnimate::isDone(void) const
{
	return _isDone;
}

void GameRunAnimate::step(float dt)
{
	if (_firstTick)
	{
		_firstTick = false;
		_elapsed = 0;
	}
	else
	{
		_elapsed += dt;
	}

	this->update(MAX(0,                                  // needed for rewind. elapsed could be negative
		MIN(1, _elapsed /
		MAX(_duration, FLT_EPSILON)   // division by 0
		)
		)
		);

	// 判断结束
	if (_elapsed >= _duration)
	{
		if (_isFindPath)
		{
			this->checkState();
		}
		else
		{
			_isDone = true;
		}
	}
}
