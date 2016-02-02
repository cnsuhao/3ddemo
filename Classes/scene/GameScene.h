#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "CocosHead.h"
#include "GameEvent.h"

class GameScene : public cocos2d::Layer
{
public:

	GameScene();

	~GameScene();
 
    static cocos2d::Scene* createScene();

    virtual bool init();

	void loadResourceMap();

	void loadImageAsyncCallBack(Texture2D* tex);

	CREATE_FUNC(GameScene);

	// 触摸事件
	virtual bool onTouchBegan(Touch *touch, Event *unusedEvent);
	virtual void onTouchMoved(Touch *touch, Event *unusedEvent);
	virtual void onTouchEnded(Touch *touch, Event *unusedEvent);
	virtual void onTouchCancelled(Touch *touch, Event *unusedEvent);

	void onUpdateMyPosEvent(Ref* pSender, GameEvent* gEvent);
	void onChangeMapEvent(Ref* pSender, GameEvent* gEvent);
	// 显示主ui
	void showMainUI();
	void beginLoadScene(float dt);
	void endLoadScene(float dt);
	void load3DObject();
	void createRoleCamera();
private:
	int _loadIndex;
	int _loadMaxNum;
	Camera*	_roleCamera;
	EventListenerTouchOneByOne* _touchListener;
};

#endif // __HELLOWORLD_SCENE_H__
