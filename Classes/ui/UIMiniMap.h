#ifndef __UIMINIMAP__
#define __UIMINIMAP__

#include "UIBaseNode.h"
#include "GameEvent.h"

class UIMiniMap :public UIBaseNode
{
public:

	static const int btn_nums = 4;
	UIMiniMap();
	virtual ~UIMiniMap();

	virtual bool init();
	virtual void show();
	virtual void hide();
	CREATE_FUNC(UIMiniMap);

	void updateMainPlayerPos();
	void updateMainPlayerSpeed();
public:
	void onSliderTouchEventCallBack(Ref* sender, Slider::EventType stype);
	void onAutoBtnTouchClickCallBack(Ref* sender);
	void onTransBtnTouchClickCallBack(Ref* sender);
	void onMapPanelTouchClickCallBack(Ref* sender);
	void onUpdateMainPlayerPosEvent(Ref* pSender, GameEvent* gEvent);
private:

	Text* m_posText;
	Text* m_speedText;
	Slider* m_slider;
};

#endif // !__UILogin__