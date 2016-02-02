#ifndef UISelTarget_h__
#define UISelTarget_h__

#include "UIBaseNode.h"
#include "GameObjectMgr.h"

class UISelTarget :public UIBaseNode
{
public:

	UISelTarget();

	~UISelTarget();

	bool init();

	CREATE_FUNC(UISelTarget);

	void refreshTargetInfo();

	void onHPChangeEvent(Ref* pSender, GameEvent* gEvent);

	void onSelTargetEvent(Ref* pSender, GameEvent* gEvent);

	void onLoadEndEvent(Ref* pSender, GameEvent* gEvent);

private:

	LoadingBar* _hpBar;
	LoadingBar* _mpBar;
	Text*		_hpText;
	Text*		_mpText;
	Text*		_nameText;
	GameObject*	_target;

};
#endif // UISelTarget_h__

