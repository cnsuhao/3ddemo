#ifndef GameEffect_h__
#define GameEffect_h__

#include "CocosHead.h"
#include "Global.h"
#include "GameObject.h"
#include "GameEvent.h"
#include "GameAtlasMgr.h"
#include "GamePlayer.h"
class GameEffectBase:public Node
{
public:
	GameEffectBase();

	~GameEffectBase();

	virtual bool init();

	void setEndCallBack(GameEventCallback1 func);

	void animRunEnd(Ref* pSender);

	virtual void start()	= 0;

	virtual void end()		= 0;

	EffectType getNextEffectType();
protected:
	EffectType			m_nextType;
	Action*				m_action;
	Sprite*				m_effect;
	Node*				m_parent;
	GameEventCallback1	m_endCallFunc;
};


// 一般类动画
class GameEffectAnim:public GameEffectBase
{
public:
	GameEffectAnim();

	~GameEffectAnim();

	static GameEffectAnim* create(Node* obj, Animation* anim);

	virtual bool init(Node* obj, Animation* anim);

	virtual void start();

	virtual void end();

	void setGameObject(GamePlayer* player);
protected:

	GamePlayer* m_player;
};


// 击中动画
class GameEffectHitAnim :public GameEffectAnim
{
public:
	GameEffectHitAnim();

	~GameEffectHitAnim();

	static GameEffectHitAnim* create(Node* node, Animation* anim);

	void setSkillIdAndDirForPosition(int id, ActDir dir, Point pt);
};



// 飞行动画
class GameEffectFlyAnim :public GameEffectAnim
{
public:
	GameEffectFlyAnim();

	~GameEffectFlyAnim();

	static GameEffectFlyAnim* create(Node* node, Animation* anim);

	void setSkillIdAndDirForPosition(int id, ActDir dir, Point pt);

	virtual void start();

	virtual bool init(Node* obj, Animation* anim);

	void onUpdateTargetPosEvent(Ref* pSender, GameEvent* gEvent);
private:
	float	m_speed;
	Point	m_nowpt;
	Point	m_targetpt;
	Action*	m_nodeAnim;
	GameObject* m_target;

};

#endif // GameEffect_h__

