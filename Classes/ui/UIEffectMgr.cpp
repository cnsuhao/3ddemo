#include "UIEffectMgr.h"


UIEffectMgr* UIEffectMgr::g_UIEffectMgr = nullptr;

UIEffectMgr* UIEffectMgr::getInstance()
{
	if (!g_UIEffectMgr)
	{
		g_UIEffectMgr = new UIEffectMgr;
		g_UIEffectMgr->init();
	}

	return g_UIEffectMgr;
}

void UIEffectMgr::destroyInstance()
{
	ArmatureDataManager::getInstance()->destroyInstance();
	CC_SAFE_RELEASE_NULL(g_UIEffectMgr);
}


void UIEffectMgr::init()
{

}

void UIEffectMgr::playEffect(string name, Node* parent, Point pt, bool isLoop, float scale)
{
	auto effect = createEffect(name);
	if (effect && parent)
	{
		effect->setScale(scale);
		effect->setTag(EFFECT_NODE_TAG);
		effect->setPosition(pt);
		parent->addChild(effect, 100);
		effect->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_3(UIEffectMgr::movementEventCallFunc,this));
		effect->getAnimation()->play(name, -1, isLoop);
	}
}

void UIEffectMgr::movementEventCallFunc(Armature *armature, MovementEventType movementType, const std::string& movementID)
{
	if (movementType == COMPLETE)
	{
		//
		armature->removeFromParent();
	}
}

std::string UIEffectMgr::getFullFileName(string name)
{
	return StringUtils::format("uieffect/%s/%s.csb",name.c_str(),name.c_str());
}

Armature* UIEffectMgr::createEffect(string name)
{
	string csbfile = getFullFileName(name);
	ArmatureDataManager::getInstance()->addArmatureFileInfo(csbfile);
	return Armature::create(name);
}
