#ifndef __UIChat__
#define __UIChat__


#include "UIBaseNode.h"


class UIChat :public UIBaseNode
{
public:

	UIChat();

	virtual ~UIChat();

	virtual bool init();

	CREATE_FUNC(UIChat);

	void onCloseBtnTouchClickCallBack(Ref* sender);

	void onSendBtnTouchClickCallBack(Ref* sender);
private:

	ui::EditBox* _editbox;
	ListView* _chatlist;

};

#endif // !__UILogin__