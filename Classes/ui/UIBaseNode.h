#ifndef __UIBASE_H__
#define __UIBASE_H__

#include "CocosHead.h"

typedef std::function<void()> initcsbfunc;
class UIBaseNode:public Node
{
public:

	UIBaseNode();
	virtual ~UIBaseNode();

	virtual void show();
	virtual void hide();
	virtual bool init();
	virtual bool isShow();
	virtual void update(float delta);

	CREATE_FUNC(UIBaseNode);

	void setCsbRoot(Layout* csb);
	void addCsbPlist(string plist);
	void setCsbFrame(Widget* frame);
	
	void scheduleRemoveCsb(float delta);
	void setInitCsbFunc(initcsbfunc initfunc);
protected:

	Layout* _csbRoot;
	Widget* _csbFrame;
	vector<string> _csbPlist;
	bool _isVisible;
	initcsbfunc	_initfunc;
};






#endif