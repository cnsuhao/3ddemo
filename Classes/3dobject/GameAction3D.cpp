#include "GameAction3D.h"
#include "GameObject3D.h"
#include "GameMap.h"

GameAnimation3D* GameAnimation3D::create(const std::string& filename, int began, int end)
{
	GameAnimation3D* anim = new GameAnimation3D();
	if (anim)
	{
		anim->initWithFile(filename,"");
		anim->_beganFrame = began;
		anim->_endFrame = end;
		anim->autorelease();
	}
	return anim;
}



GameAnimate3D::GameAnimate3D():
Animate3D(),
_func(nullptr),
_object(nullptr)
{

}

GameAnimate3D::~GameAnimate3D()
{

}

GameAnimate3D* GameAnimate3D::create(GameAnimation3D *animation)
{
	GameAnimate3D *animate = nullptr;
	if (animation)
	{
		int beganIndex = animation->getBeganFrame();
		int endIndex = animation->getEndFrame();
		animate = new (std::nothrow) GameAnimate3D();
		animate->initWithFrames(animation, beganIndex, endIndex, g_frameRate);
		animate->autorelease();
	}
	return animate;
}


void GameAnimate3D::stop(void)
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
	Animate3D::stop();
}

void GameAnimate3D::update(float t)
{
	Animate3D::update(t);
}

void GameAnimate3D::setGameObject(GameObject3D* object)
{
	_object = object;
}

void GameAnimate3D::setCallBack(GameEventCallback1 func)
{
	_func = func;
}



//GameRunAnimate3D----------------------------------------------------------

GameRunAnimate3D::GameRunAnimate3D() :
GameAnimate3D(),
_isDone(false),
_pathNode(nullptr),
_isFindPath(false)
{
	_firstTick = true;
}

GameRunAnimate3D::~GameRunAnimate3D()
{

}


GameRunAnimate3D* GameRunAnimate3D::create(GameObject3D* object)
{
	GameRunAnimate3D *animate = new (std::nothrow) GameRunAnimate3D();
	if (animate)
	{
		auto animation = object->getAnimition3D();
		int beganIndex = animation->getBeganFrame();
		int endIndex = animation->getEndFrame();
		animate->initWithFrames(animation, beganIndex, endIndex, g_frameRate);
		animate->_object = object;
		animate->autorelease();
	}
	return animate;
}


void GameRunAnimate3D::stop(void)
{
	// 检测队列是否为空
	if (_object)
	{
		_object->getActionDispatcher()->resumOnce();
		_object->updateData();
	}
	_object = nullptr;
	GameAnimate3D::stop();
}

void GameRunAnimate3D::update(float t)
{
	if (_object)
	{
		this->checkMove();
	}
	GameAnimate3D::update(t);
}


void GameRunAnimate3D::startWithTarget(Node *target)
{
	changeDirForNextFindPath();
	Animate3D::startWithTarget(target);
}


bool GameRunAnimate3D::isDone(void) const
{
	return _isDone;
}

void GameRunAnimate3D::step(float dt)
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
		_isDone = false;
		_elapsed = 0.0f;
	}
}

void GameRunAnimate3D::setPathNode(ptr_PathNode node)
{
	_pathNode = node;
}

void GameRunAnimate3D::setIsFindPath(bool isFind)
{
	_isFindPath = isFind;
}

void GameRunAnimate3D::changeDirForNextFindPath()
{
	if (_isFindPath)
	{
		if (_pathNode == nullptr || _pathNode->next == nullptr)
		{
			_isDone = true;
			return;
		}
		_pathNode = _pathNode->nextNode();
		_nextPoint = GameMap::getInstance()->convertTilePosToNodePos(Point(_pathNode->m_x, _pathNode->m_y));
		Point nowPoint = _object->getTilePos();
		float dir = getDir3DYByPoint(nowPoint, _nextPoint);
		_object->setDir(dir);
	}
}

void GameRunAnimate3D::checkMove()
{
	if (_isFindPath)
	{
		float speed = _object->getSpeed();
		Point nowPoint = _object->getTilePos();
		float distance = nowPoint.distance(_nextPoint);
		if (distance < speed)
		{
			changeDirForNextFindPath();
		}
		bool isCached = _object->getActionDispatcher()->getIsCacheEvents();
		if (isCached || _isDone)
		{
			_isDone = true;
			return;
		}
	}
	// 移动
	float speed = _object->getSpeed();
	Point pos = _object->getTilePos();
	Point dir = _object->getDir2D();
	pos += dir * speed;
	if (GameMap::getInstance()->canMovePixel(pos.x, pos.y))
	{
		_object->setTilePos(pos);
	}
}
