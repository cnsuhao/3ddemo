#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

#include "CocosHead.h"
#include "GameAtlasMgr.h"
#include "ObjectData.h"
#include "GameDispatcher.h"

class DoSkill;
class GameObject:public Sprite
{
public:
	GameObject();

	virtual ~GameObject();

	virtual bool init(ObjectData* data);
	// 设置动画状态
	void setAnimState(ActMotion state);
	void setAnimStateNoUpdate(ActMotion state);
	ActMotion getActState();
	// 设置方向
	void setDir(ActDir dir);
	// 设置方向
	void setDirNoUpdate(ActDir dir);
	// 设置方向
	void setDirAndAnimState(ActDir dir, ActMotion state);
	// 设置数据
	void setObjectData(const ObjectData* data);
	// 动作事件派发
	GameDispatcher* getActionDispatcher();

	// 逻辑事件派发
	GameDispatcher* getLogicDispatcher();
	// 停下来
	void stop();
	// 设置数据
	ObjectData* getObjectData();
	// 获取方向
	ActDir getDir();
	// 更新数据
	void updateData();
	// 设置地图位置
	void setTilePos(Point pos);
	Point getTilePos();
	// 设置类型
	void setObjectType(ObjectType objtype);
	// 获取类型
	ObjectType getObjectType();
	// 设置透明状态
	void setIsAlpha(bool isAlpha);
	// 检测透明状态
	void checkAlphaState();

	void resetAnimState(Ref* pSender);
	void initHPBar();
	void initName();
	void refreshHPBar();
	void setIsSelect(bool isSel);
	void onHPChangeEvent(Ref* pSender, GameEvent* gEvent);
public:

	virtual void onAnimEvent(Ref* pSender, GameEvent* gEvent);

	virtual void onEmptyEvent(Ref* pSender, GameEvent* gEvent);

	virtual void onFindPathEvent(Ref* pSender, GameEvent* gEvent);

	virtual Animation* getAnimation() = 0;

	// 更新动画
	virtual void updateAnim() = 0;

	virtual void updateOtherAnim(int index, float dt);

	virtual void dispatcherAnimEvent();

	virtual void setPositionForMap();
protected:

	// 动作状态
	ActMotion	m_animState;
	// 方向 
	ActDir		m_dir;
	// 位置
	Point		m_pos;
	// 是否刷新
	bool		m_isUpdate;
	// 数据
	ObjectData* m_data;
	// 动作事件派发
	GameDispatcher* m_actionDispatcher;
	// 逻辑事件派发
	GameDispatcher* m_logicDispatcher;
	// 动作变化事件
	GameAnimEvent* m_animEvent;
	// 角色类型
	ObjectType	 m_objectType;
	Animation*	 m_dressAnim;
	// 血条 
	ImageView*	 m_barBK;
	LoadingBar*  m_hpBar;
	Text*		 m_nameText;
	Text*		 m_hpText;
	// 选中图片
	Sprite*		 m_selectSprite;
	// 释放技能
	DoSkill*	m_doSkill;
};





#endif