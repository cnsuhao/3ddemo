#ifndef __UIMANAGER_H__
#define __UIMANAGER_H__


#include "UIBaseNode.h"
#include "GameDispatcher.h"


enum class UIZorder
{
	order_mainbk	=	0,
	order_main		=	100,
	order_mainfront =	500,
	order_load		=	1000,
};

enum class UIType
{
	UI_Update		= 1,
	UI_Login		= 2,
	UI_Chat			= 3,
	UI_Loading		= 4,
	UI_RoleHead		= 5,
	UI_Rocker		= 6,
	UI_MiniMap		= 7,
	UI_SkillPanel	= 8,
	UI_SelTarget	= 9,
	UI_WorldMap		= 10,
};

class UIManager :public Node
{
public:

	UIManager();

	~UIManager();

	static UIManager* getInstance();

	static void destroyInstance();

	bool init();

	UIBaseNode* showUI(UIType uiType);

	void hideUI(UIType uiType);

	bool isShow(UIType uiType);

	void hideWithCreate(UIType uiType);

	UIBaseNode* createUI(UIType uiType);

	UIBaseNode* getUI(UIType uiType);

	void loadUI(int percent);

	void hideAllUI();

	GameDispatcher* getDispatcher();
	// 获取ui大小
	Size getUISize();
	// 获取ui缩放
	float getUIScale();
	// 获取全屏缩放
	float getFullScreenScale();
	// 获取横屏缩放
	float getFullWidthScale();
	// 获取纵屏缩放
	float getFullHeightScale();
	// 设置自动战斗
	void setIsAutoFight(bool isAuto);

	CREATE_FUNC(UIManager);
private:

	static UIManager* _uiManager;
	GameDispatcher* _dispatcher;
	map<UIType, UIBaseNode*> _uiList;

	float _scale;
	Size  _uiSize;
	float _scaleW;
	float _scaleH;
};











#endif // !