#ifndef _GAMEOBJECT3D_H
#define _GAMEOBJECT3D_H

#include "CocosHead.h"
#include "GameAtlasMgr.h"
#include "ObjectData3D.h"
#include "GameDispatcher.h"
#include "GameAction3D.h"

class GameObject3D:public Sprite3D
{
public:
	GameObject3D();
	virtual ~GameObject3D();
	static GameObject3D* create(ObjectData3D* data);
	virtual bool init(ObjectData3D* data);
	// 设置动画状态
	void setAnimState(ActMotion state);
	void setAnimStateNoUpdate(ActMotion state);
	ActMotion getActState();
	// 设置方向
	void setDir(float dir);
	// 设置方向
	void setDirNoUpdate(float dir);
	// 设置方向
	void setDirAndAnimState(float dir, ActMotion state);
	// 设置数据
	void setObjectData(const ObjectData3D* data);
	// 动作事件派发
	GameDispatcher* getActionDispatcher();
	// 逻辑事件派发
	GameDispatcher* getLogicDispatcher();
	// 停下来
	void stop();
	// 设置数据
	ObjectData3D* getObjectData();
	// 获取方向
	float getDir();
	// 更新数据
	void updateData();
	// 设置地图位置
	void setTilePos(Point pos);
	Point getTilePos();
	// 设置类型
	void setObjectType(ObjectType objtype);
	// 获取类型
	ObjectType getObjectType();
	// 速度
	float getSpeed();
	void setSpeed(float s);
	Point getDir2D();
	// 设置透明状态
	void setIsAlpha(bool isAlpha);
	void moveTo(Point pt);
	// 检测透明状态
	void checkAlphaState();
	// 当前状态是否可被打断
	bool isCanBreak(ActMotion state);
	void resetAnimState(Ref* pSender);
	// 名字血条信息
	void initHPBar();
	void initName();
	void refreshHPBar();
	void setIsSelect(bool isSel);
	void onHPChangeEvent(Ref* pSender, GameEvent* gEvent);
	GameAnimation3D* getAnimition3D();
	void updateAnim();
	void setPositionForMap();
private:
	void onAnimEvent(Ref* pSender, GameEvent* gEvent);
	void onEmptyEvent(Ref* pSender, GameEvent* gEvent);
	void onFindPathEvent(Ref* pSender, GameEvent* gEvent);
	void dispatcherAnimEvent();
private:
	// 普攻
	void doHit();
	// 魔法
	void doMagic();
protected:

	// 动作状态
	ActMotion	m_animState;
	// 方向 
	float		m_dir;
	// 位置
	Point		m_pos;
	// 是否刷新
	bool		m_isUpdate;
	// 数据
	ObjectData3D* m_data;
	// 动作事件派发
	GameDispatcher* m_actionDispatcher;
	// 逻辑事件派发
	GameDispatcher* m_logicDispatcher;
	// 动作变化事件
	GameAnimEvent* m_animEvent;
	// 角色类型
	ObjectType	 m_objectType;
	// 动画anim
	GameAnimation3D* m_anim3D;
	GameFindPathEvent* m_findPathEvent;
	// 速度
	float	m_speed;
};





#endif