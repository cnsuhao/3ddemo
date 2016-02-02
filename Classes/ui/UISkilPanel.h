#ifndef __UISkillPanel__
#define __UISkillPanel__


#include "UIBaseNode.h"
#include "DownManager.h"

class UISkillPanel :public UIBaseNode
{
public:

	static const int btn_nums = 4;

	UISkillPanel();

	virtual ~UISkillPanel();

	virtual bool init();

	virtual void show();

	virtual void hide();

	CREATE_FUNC(UISkillPanel);


	void onSkillBtnTouchClickCallBack(Ref* sender);

private:

	Button*	_btn_skill[btn_nums];

};

#endif // !__UILogin__