#ifndef DrawHelper_h__
#define DrawHelper_h__

#include "CocosHead.h"

class DrawGridNode : public Node
{
public:
	DrawGridNode();

	virtual ~DrawGridNode();

	static DrawGridNode* create(Node* parent);

	virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;

	void setGrideSize(Size gridSize);


	virtual bool init();


	bool onTouchBegan(Touch* touch, Event* evt);
	void onTouchMoved(Touch* touch, Event* evt);
	void onTouchEnded(Touch* touch, Event* evt);
	void setTextPostion(Point pt);
protected:

	void onDraw(const Mat4 &transform, uint32_t flags);
	CustomCommand	_customCommand;
	Node*			m_parentNode;
	Size			m_gridSize;
	Text*			m_text;
};
#endif // DrawHelper_h__