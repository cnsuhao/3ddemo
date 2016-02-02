#ifndef __LOGIN_SCENE_H__
#define __LOGIN_SCENE_H__

#include "CocosHead.h"


class LoginScene : public cocos2d::Layer
{
public:

	LoginScene();

	~LoginScene();
 
    static cocos2d::Scene* createScene();

    virtual bool init();
    

	CREATE_FUNC(LoginScene);

private:


};

#endif // __HELLOWORLD_SCENE_H__
