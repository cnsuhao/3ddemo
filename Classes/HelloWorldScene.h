#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
using namespace ui;
class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
	// ≥ı ºªØµÿÕº
	void initTerrain();
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	bool onTouchBegan(Touch* touch, Event* evt);
	void onTouchMoved(Touch* touch, Event* evt);
	void updateCamera(float dt);

	void initAdujstPanel();
	void adjustHeightButtonTouchEvent(Ref* ref, Widget::TouchEventType eventType);

	void initSprite3D();
private:

	Camera* _mapCamera;
	Terrain* _terrain;
	float		_x = 0;
	float		_y = 0;
	float		_z = 0;
	float		_per = 1.0f;
	float		_scale = 1.0f;
	float		_height = 200.0f * _scale;
	Vec3		_cameraPos;
	Vec3		_cameraRotate;
	Sprite3D*   _sprite;
};

#endif // __HELLOWORLD_SCENE_H__
