#include "UILogin.h"
#include "GameScene.h"
#include "UIManager.h"
#include "GameAtlasMgr.h"
#include "ObjectDataMgr.h"
#include "ShaderMgr.h"
#include "ObjectData3DMgr.h"
#pragma execution_character_set("utf-8")

UILogin::UILogin() :
_editName(nullptr),
_editPsw(nullptr),
_selectroot(nullptr)
{

}

UILogin::~UILogin()
{

}

bool UILogin::init()
{
	auto csbRoot = dynamic_cast<Layout*>(GUIReader::getInstance()->widgetFromBinaryFile("ui/loginui/loginui.csb"));
	if (!csbRoot)
	{
		return false;
	}
	this->setCsbRoot(csbRoot);
	float scale = UIManager::getInstance()->getFullHeightScale();
	_csbPlist.push_back("ui/loginui/loginui0.plist");
	
	_imgbk1 = dynamic_cast<ImageView*>(Helper::seekWidgetByName(_csbRoot, "bkimg1"));
	_imgbk1->setAnchorPoint(Point::ZERO);
	_imgbk1->setPosition(Point::ZERO);
	_imgbk1->setScale(scale);
	_imgbk2 = dynamic_cast<ImageView*>(Helper::seekWidgetByName(_csbRoot, "bkimg2"));
	_imgbk2->setAnchorPoint(Point::ZERO);
	_imgbk2->setScale(scale);
	_imgbk2->setPosition(Point(_imgbk1->getContentSize().width, 0));
	// 账号，用于定位
	Layout* name = dynamic_cast<Layout*>(Helper::seekWidgetByName(_csbRoot, "name"));
	name->setBackGroundColorType(Layout::BackGroundColorType::NONE);
	_editName = ui::EditBox::create(name->getContentSize(), "ui/common/touming.png");
	_editName->setAnchorPoint(Point::ZERO);
	_editName->setFontSize(22);
	_editName->setInputMode(ui::EditBox::InputMode::SINGLE_LINE);
	_editName->setInputFlag(ui::EditBox::InputFlag::INITIAL_CAPS_ALL_CHARACTERS);
	_editName->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
	name->addChild(_editName);
	// 密码，用于定位
	Layout* passward = dynamic_cast<Layout*>(Helper::seekWidgetByName(_csbRoot, "passward"));
	passward->setBackGroundColorType(Layout::BackGroundColorType::NONE);
	_editPsw = ui::EditBox::create(name->getContentSize(), "ui/common/touming.png");
	_editPsw->setAnchorPoint(Point::ZERO);
	_editPsw->setFontSize(22);
	_editPsw->setInputMode(ui::EditBox::InputMode::SINGLE_LINE);
	_editPsw->setInputFlag(ui::EditBox::InputFlag::PASSWORD);
	_editPsw->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
	passward->addChild(_editPsw);
	// 登陆按钮
	_btnlogin = dynamic_cast<Button*>(Helper::seekWidgetByName(_csbRoot, "loginbtn"));
	if (_btnlogin)
	{
		_btnlogin->addClickEventListener(CC_CALLBACK_1(UILogin::onLoginBtnTouchClickCallBack, this));
	}
	_imginputbk = dynamic_cast<ImageView*>(Helper::seekWidgetByName(_csbRoot, "inputbk"));
	this->addChild(_csbRoot);

	return true;
}

void UILogin::onLoginBtnTouchClickCallBack(Ref* sender)
{
	//this->hide();
	//UIManager::getInstance()->showUI(UIType::UI_Update);

	showSelectRole();
}

void UILogin::update(float delta)
{
	int posX2 = _imgbk2->getPositionX();
	if (posX2 < 0)
	{
		ImageView* temp = _imgbk1;
		_imgbk1 = _imgbk2;
		_imgbk2 = temp;
	}
	int posX1 = _imgbk1->getPositionX();
	_imgbk1->setPosition(Point(posX1 - 1, 0));
	posX2 = posX1 - 2 + _imgbk1->getContentSize().width * _imgbk1->getScaleX();
	_imgbk2->setPosition(Point(posX2, 0));
}

void UILogin::show()
{
	this->scheduleUpdate();
}

void UILogin::hide()
{
	this->unscheduleUpdate();
}

void UILogin::showSelectRole()
{
	_btnlogin->setVisible(false);
	_imginputbk->setVisible(false);
	if (_selectroot)
	{
		_selectroot->setVisible(true);
		return;
	}
	// 选角ui
	_selectroot = dynamic_cast<Layout*>(GUIReader::getInstance()->widgetFromBinaryFile("ui/selectrole/selectrole.csb"));
	_csbPlist.push_back("ui/selectrole/selectrole0.plist");
	for (int i = 0; i < 3; ++i)
	{
		auto imglayout = dynamic_cast<Layout*>(Helper::seekWidgetByName(_selectroot, StringUtils::format("role_%d", i + 1)));
		if (imglayout)
		{
			imglayout->setTag(i + 1);
			imglayout->setTouchEnabled(true);
			imglayout->addClickEventListener(CC_CALLBACK_1(UILogin::onRoleBtnTouchClickCallBack, this));
			_role[i] = Sprite::createWithSpriteFrameName(StringUtils::format("selectrole/role_%d.png", i + 1));
			_role[i]->setAnchorPoint(Point::ZERO);
			_role[i]->setPosition(Point::ZERO);
			imglayout->addChild(_role[i]);
		}
	}
	auto btnbegin = dynamic_cast<Button*>(Helper::seekWidgetByName(_selectroot, "btn_begin"));
	if (btnbegin)
	{
		btnbegin->addClickEventListener(CC_CALLBACK_1(UILogin::onBeginBtnTouchClickCallBack, this));
	}
	this->addChild(_selectroot);
	Size uiSize = UIManager::getInstance()->getUISize();
	_selectroot->setContentSize(uiSize);
	//默认选中
	selRole(1);
}

void UILogin::onRoleBtnTouchClickCallBack(Ref* sender)
{
	Node* image = dynamic_cast<Node*>(sender);
	if (image)
	{
		selRole(image->getTag());
	}
}

void UILogin::onBeginBtnTouchClickCallBack(Ref* sender)
{
	this->hide();
	// 设置角色
	ObjectData3DMgr::getInstance()->setMainData(_selIndex);
	// 跳转场景
	UIManager::destroyInstance();
	Scene* scene = GameScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

void UILogin::selRole(int index)
{
	for (int i = 0; i < 3; ++i)
	{
		_role[i]->setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP));
	}

	_selIndex = index;
	auto glProgramState = ShaderMgr::getInstance()->getStrokeGLProgramState(_role[index - 1]->getContentSize(), 1, Color3B::GREEN);
	if (glProgramState)
	{
		_role[index - 1]->setGLProgramState(glProgramState);
	}
}


