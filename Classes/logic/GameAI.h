#include "CocosHead.h"
#include "GamePlayer.h"
#ifndef GameAI_h__
#define GameAI_h__

enum class AITYPE
{
	nil			= 0,
	initiative	= 1,//主动
	passive		= 2,//被动
};

enum class AIState
{
	nil			= 0,
	move		= 1,
	autofight	= 2,
};

class GameAIBase:public Node
{
public:
	GameAIBase();
	virtual ~GameAIBase();

	void setAttach(GamePlayer* node);
	void setRect(Rect rect);
	void runAI();
	virtual void updateAI(float dt) = 0;
	virtual bool init();
protected:
	float	m_dt;		//检测间隔
	AITYPE	m_aiType;	//AI类型
	GamePlayer*	m_attach;	//归属
	Rect	m_rect;		//活动范围
	AIState m_state;
};

// 主动AI
class GameAIInitiative :public GameAIBase
{
public:
	GameAIInitiative();
	~GameAIInitiative();

	static GameAIInitiative* create();
	virtual void updateAI(float dt);
	void attack(GameObject* obj);
	void addSelfListener();

	void onSelfHPChangeEvent(Ref* pSender, GameEvent* gEvent);
private:

};

// 释放技能
class DoSkill:public Node
{
public:
	DoSkill(){};
	~DoSkill(){};

	static DoSkill* create(GamePlayer* obj);

	bool init(GamePlayer* obj);
	void doSkillById(int id);
	void setIsAutoFight(bool isAuto);
	void onUpdateMyPosEvent(Ref* pSender, GameEvent* gEvent);
	void onUpdateTargetPosEvent(Ref* pSender, GameEvent* gEvent);
	int getCanUseSkillId();
	void releaseSkill();
	void afterReleaseSkill(Ref* pSender);
	void onSelTargetEvent(Ref* pSender, GameEvent* gEvent);
	bool getIsAutoFight(){ return m_isAutoFight; };
private:
	GamePlayer* m_gamePlayer;
	int			m_skilId;
	bool		m_isFindTarget;
	int			m_distance;
	bool		m_isAutoFight;
	bool		m_isReleaseSkill;
};





#endif // GameAI_h__
