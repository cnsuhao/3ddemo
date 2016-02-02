#ifndef __UILoading__
#define __UILoading__


#include "UIBaseNode.h"


class UILoading :public UIBaseNode
{
public:

	UILoading();

	~UILoading();

	bool init();

	CREATE_FUNC(UILoading);

	void scrollToPercent(int percent);

	virtual void update(float delta);

	virtual void show();
private:

	LoadingBar* _loadBar;
	Text* _loadtext;
	int _delta;
	int _destPercent;
	bool _isScroll;
};

#endif // !UIUpdate