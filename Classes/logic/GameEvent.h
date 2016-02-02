#ifndef __GAMEEVENT_H__
#define __GAMEEVENT_H__

#include "CocosHead.h"
#include "UIBaseNode.h"
#include "GameAtlasMgr.h"

#define AnimEventState_ID		1000

#define AnimEventEmpty_ID		1001

#define AdjustMapPosEvent_ID	1002

#define FindPathEvent_ID		1003

#define HPChangeEvent_ID		1004

enum class GameEventId
{
	event_nil			= 0,
	ui_create			= 1,
	ui_show				= 2,
	ui_hide				= 3,
	ui_destroy			= 4,
	grid_changeshow		= 5,
	update_mypos		= 6,
	update_pos			= 7,
	hp_change			= 8,
	sel_target			= 9,
	update_autostate	= 10,
	change_map			= 11,
	load_end			= 12,
	began_changemypos	= 13,
};



class GameEvent:public Ref
{
public:

	GameEvent() :_id(GameEventId::event_nil){};

	virtual ~GameEvent(){};

	static GameEvent* create(const GameEventId& id);

	virtual void init(GameEventId id);

	GameEventId getEventId();

	void setParamStr(string str);

	string getParamStr();

	void setParamInt1(int value);

	int getParamInt1();

	void setParamInt2(int value);

	int getParamInt2();

public:

	GameEventId _id;
	string		_paramStr;
	int			_paramInt1;
	int			_paramInt2;


};


class UICreateEvent :public GameEvent
{
public:

	UICreateEvent() :GameEvent(), _node(nullptr), _uitype(0){};

	virtual ~UICreateEvent(){};

	static UICreateEvent* create(const GameEventId& id);

	void setUIType(int type);
	int	 getUIType();

	void setUIBaseNode(UIBaseNode* node);
	UIBaseNode* getUIBaseNode();
private:

	UIBaseNode* _node;
	int			_uitype;
};

class GameAnimEvent :public GameEvent
{
public:

	GameAnimEvent() :GameEvent(){};

	virtual ~GameAnimEvent(){};

	static GameAnimEvent* create();

	virtual void init(GameEventId id);

	void copy(GameAnimEvent* gEvent);
	// 动作状态
	ActMotion	m_animState;
	// 方向 
	ActDir		m_dir;
	// 特效
	int			m_effectId;
	// 技能
	int			m_skillId;
	// 3d方向
	float		m_3dDir;
	//
	GameEventCallback1 m_callBack;
};



class GameFindPathEvent :public GameEvent
{
public:

	GameFindPathEvent():GameEvent(){};

	virtual ~GameFindPathEvent(){};

	static GameFindPathEvent* create();
	

	// 位置
	Point		m_targetPoint;

private:


};



#endif