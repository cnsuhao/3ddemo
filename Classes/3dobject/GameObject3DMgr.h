#ifndef GameObject3DMgr_h__
#define GameObject3DMgr_h__

#include "CocosHead.h"
#include "GameObject3D.h"

class GameObject3DMgr:public Node
{
public:
	enum class RoleZorder
	{
		order_mainpalyer	= 200,
		order_other			= 100,
	};

	GameObject3DMgr();

	virtual ~GameObject3DMgr();

	static GameObject3DMgr* getInstance();

	static void destroyInstance();

	void loadObjects();

	GameObject3D* getMainGamePlayer();

	bool init();

	bool onTouchBegan(Touch* touch, Event* evt);
	void onTouchMoved(Touch* touch, Event* evt);
	void updateCamera(float dt);
	void onUpdateMainPlayerPosEvent(Ref* pSender, GameEvent* gEvent);
	void adjustCameraPosition();
	Vec3 converPointToVec3(Point point);
	Camera* getObject3DCamera();
private:

	static GameObject3DMgr* _sGameObject3DMgr;
	// 主玩家
	GameObject3D*			m_mainPlayer;
	// 玩家列表
	vector<GameObject3D*>	m_otherPlayerList;
	// 摄像机
	Camera*					m_mainPlayerCamera;
	Vec3					m_cameraPos = Vec3::ZERO;
	Vec3					m_cameraDist = Vec3(0.0f, 100.0f, 100.0f);
	Vec3					m_cameraRotate = Vec3(-45.0f, 0.0f, 0.0f);
	// 调整摄像机
	float		_x = 0;
	float		_y = 0;
	float		_z = 0;
	float		_per = 1.0f;
};

#endif // GameObject3DMgr_h__

