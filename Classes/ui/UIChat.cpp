#include "UIChat.h"
#include "UIManager.h"
#include "RichTextBox.h"
#pragma execution_character_set("utf-8")

UIChat::UIChat() :
_editbox(nullptr),
_chatlist(nullptr)
{

}

UIChat::~UIChat()
{

}

bool UIChat::init()
{
	_csbRoot = dynamic_cast<Layout*>(GUIReader::getInstance()->widgetFromBinaryFile("ui/chatui/chatui.csb"));
	if (!_csbRoot)
	{
		return false;
	}
	_csbPlist.push_back("ui/chatui/chatui0.plist");
	// 输入，用于定位
	Layout* input = dynamic_cast<Layout*>(Helper::seekWidgetByName(_csbRoot, "input"));
	_editbox = ui::EditBox::create(input->getContentSize(), "ui/common/touming.png");
	_editbox->setAnchorPoint(Point::ZERO);
	_editbox->setFontSize(22);
	input->addChild(_editbox);
	_chatlist = dynamic_cast<ListView*>(Helper::seekWidgetByName(_csbRoot, "list"));
	// 关闭按钮
	Button* closebtn = dynamic_cast<Button*>(Helper::seekWidgetByName(_csbRoot, "closebtn"));
	if (closebtn)
	{
		closebtn->addClickEventListener(CC_CALLBACK_1(UIChat::onCloseBtnTouchClickCallBack, this));
	}
	Button* sendbtn = dynamic_cast<Button*>(Helper::seekWidgetByName(_csbRoot, "sendbtn"));
	if (sendbtn)
	{
		sendbtn->addClickEventListener(CC_CALLBACK_1(UIChat::onSendBtnTouchClickCallBack, this));
	}

	this->addChild(_csbRoot);
	
	return true;
}

void UIChat::onCloseBtnTouchClickCallBack(Ref* sender)
{
	this->hide();
}
void UIChat::onSendBtnTouchClickCallBack(Ref* sender)
{
	string msgStr = _editbox->getText();
	auto parse = RichTextParse::create();
	parse->parseTextString(msgStr);
	auto richText = parse->formatText();
	//richText->setIsAutoHeight(true);
	richText->ignoreContentAdaptWithSize(false);
	int _width = _chatlist->getContentSize().width;
	richText->setContentSize(Size(_width, 100));
	richText->formatText();
	_chatlist->pushBackCustomItem(richText);
}


