#ifndef __UILogin__
#define __UILogin__


#include "UIBaseNode.h"
#include "DownManager.h"

class UILogin :public UIBaseNode
{
public:

	UILogin();

	virtual ~UILogin();

	virtual bool init();

	virtual void show();

	virtual void hide();

	CREATE_FUNC(UILogin);

	virtual void update(float delta);

	void onLoginBtnTouchClickCallBack(Ref* sender);

	void onRoleBtnTouchClickCallBack(Ref* sender);

	void onBeginBtnTouchClickCallBack(Ref* sender);

	void showSelectRole();

	void selRole(int index);
private:

	ui::EditBox* _editName;
	ui::EditBox* _editPsw;
	ImageView* _imgbk1;
	ImageView* _imgbk2;
	ImageView* _imginputbk;
	Button*	   _btnlogin;
	Layout*	   _selectroot;
	int		   _selIndex;
	Sprite*	   _role[3];

};

#endif // !__UILogin__