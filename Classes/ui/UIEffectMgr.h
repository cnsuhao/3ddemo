#ifndef UIEffectMgr_h__
#define UIEffectMgr_h__


#include "CocosHead.h"


class UIEffectMgr:public Ref
{
public:
	static UIEffectMgr* getInstance();
	static void destroyInstance();
	void init();
	void playEffect(string name, Node* parent, Point pt = Point::ZERO, bool isLoop = false, float scale = 1.0f);
	string getFullFileName(string name);
	Armature* createEffect(string name);
	void movementEventCallFunc(Armature *armature, MovementEventType movementType, const std::string& movementID);
private:
	UIEffectMgr(){};
	~UIEffectMgr(){};
	static UIEffectMgr* g_UIEffectMgr;
	const int EFFECT_NODE_TAG = 88888;
};
#endif // UIEffectMgr_h__

