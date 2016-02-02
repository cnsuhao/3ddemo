#include "UISkilPanel.h"
#include "GameScene.h"
#include "UIManager.h"
#include "GameAtlasMgr.h"
#include "GameObjectMgr.h"
#include "ObjectDataMgr.h"
#include "GameAI.h"
#pragma execution_character_set("utf-8")

UISkillPanel::UISkillPanel()
{

}

UISkillPanel::~UISkillPanel()
{

}

bool UISkillPanel::init()
{
	auto csbRoot = dynamic_cast<Layout*>(GUIReader::getInstance()->widgetFromBinaryFile("ui/skillpanel/skillpanel.csb"));
	if (!csbRoot)
	{
		return false;
	}
	this->setCsbRoot(csbRoot);
	float scale = UIManager::getInstance()->getFullHeightScale();
	_csbPlist.push_back("ui/skillpanel/skillpanel0.plist");

	int myjob = ObjectDataMgr::getInstance()->getMainPlayerJob();
	int skill[3][3] = 
	{ 
		1,	3,	9,
		10, 5,	8,
		7,	11,	12,
	};
	int id = 0;
	// 技能按键
	for (int i = 0; i < btn_nums; ++i)
	{
		_btn_skill[i] = dynamic_cast<Button*>(Helper::seekWidgetByName(_csbRoot, StringUtils::format("btn_skill%d",i)));
		if (_btn_skill[i])
		{
			if (i > 0)
			{
				id = skill[myjob - 1][i - 1];
			}
			_btn_skill[i]->setTag(id);
			_btn_skill[i]->addClickEventListener(CC_CALLBACK_1(UISkillPanel::onSkillBtnTouchClickCallBack, this));

			ImageView* icon = dynamic_cast<ImageView*>(_btn_skill[i]->getChildByName("icon"));
			if (icon)
			{
				icon->loadTexture(StringUtils::format("icon/skill_%d.png", i + (myjob - 1) * 3));
			}
		}
	}
	this->addChild(_csbRoot);
	this->setLocalZOrder((int)UIZorder::order_mainfront);
	return true;
}

void UISkillPanel::onSkillBtnTouchClickCallBack(Ref* sender)
{
	Button* btn = dynamic_cast<Button*>(sender);
	if (btn)
	{
		GamePlayer* mainPlayer = GameObjectMgr::getInstance()->getMainGamePlayer();
		if (mainPlayer)
		{
			mainPlayer->getDoSkill()->doSkillById(btn->getTag());
		}
	}

}

void UISkillPanel::show()
{
	UIBaseNode::show();
}

void UISkillPanel::hide()
{
	UIBaseNode::hide();
}


