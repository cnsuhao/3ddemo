#ifndef _GAMEACTION_H
#define _GAMEACTION_H

#include "CocosHead.h"
#include "GameObject.h"
#include "FindPath.h"


class GameAnimate:public Animate
{
public:
	GameAnimate();

	virtual ~GameAnimate();

	static GameAnimate* create(Animation *animation);
	// 完成的时候检测动作队列
	virtual void stop(void);
	// 每帧刷新
	virtual void update(float t);
	// 关联对象
	void setGameObject(GameObject* object);

	void setCallBack(GameEventCallback1 func);
private:

	// 动作目标
	GameObject*			_object;
	GameEventCallback1  _func;
};




class GameRunAnimate :public Animate
{
public:
	GameRunAnimate();

	virtual ~GameRunAnimate();

	static GameRunAnimate* create(GameObject* object);
	// 完成的时候检测动作队列
	virtual void stop(void);
	// 每帧刷新
	virtual void update(float t);
	// 启动
	virtual void startWithTarget(Node *target) override;
	// 检测状态
	void checkState();
	// 寻路
	void setPathNode(ptr_PathNode node);
	// 是否寻路
	void setIsFindPath(bool isFind);
	// 完成
	virtual bool isDone(void) const override;
	// 刷新
	virtual void step(float dt) override;
private:
	// 动作目标
	GameObject* _object;
	// 开始坐标
	Point _startPos;
	// 结束坐标
	Point _endPos;
	// 移动完成格子坐标
	Point _tilePos;

	// 寻路节点
	ptr_PathNode _pathNode;
	// 寻路
	bool		_isFindPath;
	// 方向
	ActDir		_dir;
	// 是否完成 
	bool		_isDone;
	// 时间百分比
	float		_t;
	// 移动差
	Point		_d;
};













#endif