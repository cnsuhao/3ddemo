#ifndef GamePlayer_h__
#define GamePlayer_h__

#include "GameObject.h"

class DoSkill;

class GamePlayer:public GameObject
{
public:
	GamePlayer();

	virtual ~GamePlayer();

	static GamePlayer* create(ObjectData* data);

	void doSkillById(int id, GameEventCallback1 callFunc = nullptr);

	void moveTo(Point pt);

	void setTarget(GameObject* obj);

	GameObject* getTarget();

	void setDoSkill(DoSkill* doSkill);

	DoSkill* getDoSkill();
public:
	virtual bool init(ObjectData* data);

	virtual void onAnimEvent(Ref* pSender, GameEvent* gEvent);

	virtual void onEmptyEvent(Ref* pSender, GameEvent* gEvent);

	virtual Animation* getAnimation();

	virtual void updateAnim();

	virtual void onFindPathEvent(Ref* pSender, GameEvent* gEvent);

	virtual void updateOtherAnim(int index, float dt);
private:

	void doHit();

	void doMagic();

	void doHPChange();
private:
	// 武器
	Sprite*		m_weapon;
	Sprite*		m_hair;
	Animation*	m_weaponAnim;
	Animation*	m_hairAnim;
	int			m_skillid;
	int			m_effectid;
	GameObject* m_target;
	GameFindPathEvent* m_findPathEvent;
	GameEventCallback1 m_callFunc;
};





#endif // GamePlayer_h__