#include "DrawHelper.h"

DrawGridNode::DrawGridNode()
{

}


DrawGridNode::~DrawGridNode()
{

}


void DrawGridNode::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	_customCommand.init(_globalZOrder);
	_customCommand.func = CC_CALLBACK_0(DrawGridNode::onDraw, this, transform, flags);
	renderer->addCommand(&_customCommand);

	Node::draw(renderer, transform, flags);
}

void DrawGridNode::onDraw(const Mat4 &transform, uint32_t flags)
{
	Director* director = Director::getInstance();
	director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);

	CHECK_GL_ERROR_DEBUG();

	DrawPrimitives::setPointSize(5);
	DrawPrimitives::setDrawColor4B(255, 0, 0, 255);
	
	Size parentSize = m_parentNode->getContentSize();

	for (int i = 0; i < parentSize.width / m_gridSize.width; ++i)
	{
		DrawPrimitives::drawLine(Point(i* m_gridSize.width, 0), Point(i* m_gridSize.width, parentSize.height));
	}
	for (int j = 0; j < parentSize.height / m_gridSize.height; ++j)
	{
		DrawPrimitives::drawLine(Point(0, j * m_gridSize.height), Point(parentSize.width, j * m_gridSize.height));
	}
	
	CHECK_GL_ERROR_DEBUG();

	//end draw
	director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

DrawGridNode* DrawGridNode::create(Node* parent)
{
	DrawGridNode* drawNode = new DrawGridNode;
	if (drawNode)
	{
		drawNode->init();
		drawNode->autorelease();
		drawNode->m_parentNode = parent;
	}
	return drawNode;
}

void DrawGridNode::setGrideSize(Size gridSize)
{
	m_gridSize = gridSize;
}

bool DrawGridNode::init()
{
	Node::init();
	m_text = Text::create();
	m_text->setFontSize(20);
	m_text->setTextColor(Color4B::GREEN);
	this->addChild(m_text);
	auto touchlistener = EventListenerTouchOneByOne::create();
	touchlistener->onTouchBegan = CC_CALLBACK_2(DrawGridNode::onTouchBegan, this);
	touchlistener->onTouchMoved = CC_CALLBACK_2(DrawGridNode::onTouchMoved, this);
	touchlistener->onTouchEnded = CC_CALLBACK_2(DrawGridNode::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchlistener, this);

	return true;
}

bool DrawGridNode::onTouchBegan(Touch* touch, Event* evt)
{
	setTextPostion(touch->getLocation());
	return true;
}
void DrawGridNode::onTouchMoved(Touch* touch, Event* evt)
{
	setTextPostion(touch->getLocation());
}
void DrawGridNode::onTouchEnded(Touch* touch, Event* evt)
{
	m_text->setVisible(false);
}

void DrawGridNode::setTextPostion(Point pt)
{
	Point localPos = this->convertToNodeSpace(pt);
	m_text->setVisible(true);
	m_text->setPosition(localPos);
	m_text->setString(StringUtils::format("(%d,%d)", (int)localPos.x, (int)localPos.y));
}
