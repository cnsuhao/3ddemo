#ifndef __UIUpdate__
#define __UIUpdate__


#include "UIBaseNode.h"
#include "DownManager.h"

class UIUpdate :public UIBaseNode
{
public:

	UIUpdate();

	~UIUpdate();

	bool init();

	CREATE_FUNC(UIUpdate);

	void ErrorCallback(int code);

	void ProgressCallback(int percent);

	void SuccessCallback(int code);

	void StateCallback(int code);

	void checkUpdate(float delta);

private:

	LoadingBar* _loadBar;

	Text* _loadtext;

	DownManager* _downManager;

};

#endif // !UIUpdate