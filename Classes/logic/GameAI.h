#include "CocosHead.h"
#include "GamePlayer.h"
#ifndef GameAI_h__
#define GameAI_h__

enum class AITYPE
{
	nil			= 0,
	initiative	= 1,//����
	passive		= 2,//����
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
	float	m_dt;		//�����
	AITYPE	m_aiType;	//AI����
	GamePlayer*	m_attach;	//����
	Rect	m_rect;		//���Χ
	AIState m_state;
};

// ����AI
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

// �ͷż���
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
