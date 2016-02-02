#ifndef GameObjectMgr_h__
#define GameObjectMgr_h__



#include "CocosHead.h"
#include "GamePlayer.h"

class GameObjectMgr:public Node
{
public:
	enum class RoleZorder
	{
		order_mainpalyer	= 200,
		order_other			= 100,
	};

	GameObjectMgr();

	virtual ~GameObjectMgr();

	static GameObjectMgr* getInstance();

	static void destroyInstance();

	void loadObjects();

	GamePlayer* getMainGamePlayer();

	bool init();

	GameObject* getNearGameObject(GameObject* obj);

	bool clickGameObjec(Point pt);

	void clearGameOjects();

	virtual void sortAllChildren();

	void setReorderChildDirty(bool isRecorder);

	bool isExistGameObject(GameObject* obj,Point pt);

	void mainPlayerGoToFarestChuanSongPT();

private:

	static GameObjectMgr* _sGameObjectMgr;
	// 主玩家
	GamePlayer*			m_mainPlayer;
	// 玩家列表
	vector<GamePlayer*>	m_otherPlayerList;

};

#endif // GameObjectMgr_h__

