#ifndef UIRocker_h__
#define UIRocker_h__



#include "UIBaseNode.h"


class UIRocker :public UIBaseNode
{
public:

	UIRocker();

	~UIRocker();

	bool init();

	CREATE_FUNC(UIRocker);

	void onRockerTouchClickCallBack(Ref* sender,Widget::TouchEventType touchType);

	void updateRockerPos(Point pos);


	void update(float dt);
private:

	ImageView* _imgFrame;
	ImageView* _imgCenter;
	Point	   _centerPos;
	float	   _r;
	float	   _rotation;

};
#endif // UIRocker_h__

