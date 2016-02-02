#ifndef _GAMEACTION3D_H
#define _GAMEACTION3D_H

#include "CocosHead.h"
#include "Global.h"
#include "FindPath.h"
class GameObject3D;

// 主要为了存储开始，结束帧位置
class GameAnimation3D :public Animation3D
{
public:
	static GameAnimation3D* create(const std::string& filename,int began, int end);
	int getBeganFrame(){ return _beganFrame; }
	int getEndFrame(){ return _endFrame; }
private:
	int _beganFrame;
	int _endFrame;
};

// 主要为了动画结束时处理回调
class GameAnimate3D :public Animate3D
{
public:
	GameAnimate3D();
	virtual ~GameAnimate3D();

	static GameAnimate3D* create(GameAnimation3D *animation);
	// 完成的时候检测动作队列
	virtual void stop(void);
	// 每帧刷新
	virtual void update(float t);
	// 关联对象
	void setGameObject(GameObject3D* object);
	// 结束回调
	void setCallBack(GameEventCallback1 func);
private:
	// 动作目标
	GameObject3D* _object;
	GameEventCallback1  _func;
};

// 处理动画同时位置的移动 
class GameRunAnimate3D :public GameAnimate3D
{
public:
	GameRunAnimate3D();
	virtual ~GameRunAnimate3D();

	static GameRunAnimate3D* create(GameObject3D* object);
	// 完成的时候检测动作队列
	virtual void stop(void);
	// 每帧刷新
	virtual void update(float t);
	// 启动
	virtual void startWithTarget(Node *target) override;
	// 检测状态
	void checkMove();
	// 完成
	virtual bool isDone(void) const override;
	// 刷新
	virtual void step(float dt) override;
	// 寻路
	void setPathNode(ptr_PathNode node);
	// 是否寻路
	void setIsFindPath(bool isFind);
	// 更改方向
	void changeDirForNextFindPath();
private:
	// 动作目标
	GameObject3D* _object;
	// 是否完成 
	bool		_isDone;
	// 寻路节点
	ptr_PathNode _pathNode;
	// 寻路
	bool		_isFindPath;
	// 目标
	Point		_nextPoint;
};













#endif