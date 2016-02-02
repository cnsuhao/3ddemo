#include "GameAtlasMgr.h"
#include "FileReader.h"
#include "tinyxml2/tinyxml2.h"

GameAtlasMgr* GameAtlasMgr::_GameAtlasMgr = nullptr;

GameAtlasMgr::GameAtlasMgr()
{

}

GameAtlasMgr::~GameAtlasMgr()
{

}

GameAtlasMgr* GameAtlasMgr::getInstance()
{
	if (!_GameAtlasMgr)
	{
		_GameAtlasMgr = new GameAtlasMgr;
		_GameAtlasMgr->init();
	}
	return _GameAtlasMgr;
}

void GameAtlasMgr::loadHumAtlasConfig()
{
	FileReader* reader = new FileReader;
	reader->readFromTxt(hum_config);
	while (reader->isEof())
	{
		AtlasConfig config;
		config.id = reader->getValue("id").asInt();
		config.file = reader->getValue("file").asString();
		int type = (int)ActMotion::stand;
		do 
		{
			ActionInfo info;
			info.type = (ActMotion)type;
			info.beginframe = reader->getValue("frame").asInt();
			info.framecount = reader->getValue("count").asInt();
			info.dir = reader->getValue("dir").asInt();
			info.delay = reader->getValue("delay").asInt();
			config.info.push_back(info);
			reader->moveNextRow();
			type++;
		} while (reader->isEof() && reader->getValue("id").asString() == "");

		_humAtlasConfig.insert(make_pair(config.id, config));

		loadAltasDesc(config.file, StringUtils::format("hum/%s.xml", config.file.c_str()));
	}
	CC_SAFE_DELETE(reader);
}


void GameAtlasMgr::loadWeaponAtlasConfig()
{
	FileReader* reader = new FileReader;
	reader->readFromTxt(weapon_config);
	while (reader->isEof())
	{
		AtlasConfig config;
		config.id = reader->getValue("id").asInt();
		config.file = reader->getValue("file").asString();
		int type = (int)ActMotion::stand;
		do
		{
			ActionInfo info;
			info.type = (ActMotion)type;
			info.beginframe = reader->getValue("frame").asInt();
			info.framecount = reader->getValue("count").asInt();
			info.dir = reader->getValue("dir").asInt();
			info.delay = reader->getValue("delay").asInt();
			config.info.push_back(info);
			reader->moveNextRow();
			type++;
		} while (reader->isEof() && reader->getValue("id").asString() == "");

		_weaponAtlasConfig.insert(make_pair(config.id, config));

		loadAltasDesc(config.file, StringUtils::format("weapon/%s.xml", config.file.c_str()));
	}
	CC_SAFE_DELETE(reader);
}

void GameAtlasMgr::destroyInstance()
{
	CC_SAFE_DELETE(_GameAtlasMgr);
}

void GameAtlasMgr::loadAltasDesc(const string& key, const string& filename)
{
	AtlasInfo info;
	string data = FileUtils::getInstance()->getStringFromFile(filename);
	// XML
	tinyxml2::XMLDocument* document = new tinyxml2::XMLDocument;
	tinyxml2::XMLError error = document->Parse(data.c_str());
	if (error != 0)
	{
		CCLOG("loadfile %s error!", filename.c_str());
		CC_SAFE_DELETE(document);
		return;
	}
	tinyxml2::XMLElement* root = document->RootElement();
	if (root)
	{
		info.path = filename.substr(0, filename.rfind('/') + 1) + root->Attribute("imagePath");
		tinyxml2::XMLElement* element = root->FirstChildElement();
		while (element)
		{
			AtlasDesc desc;
			desc.id = element->IntAttribute("Name");
			desc.x = element->IntAttribute("X");
			desc.y = element->IntAttribute("Y");
			desc.w = element->IntAttribute("Width");
			desc.h = element->IntAttribute("Height");
			desc.cx = element->IntAttribute("OX");
			desc.cy = element->IntAttribute("OY");
			info.desc.insert(make_pair(desc.id, desc));
			element = element->NextSiblingElement();
		}
	}
	_atlasInfo.insert(make_pair(key, info));
	CC_SAFE_DELETE(document);
}

Animation* GameAtlasMgr::getHumAnimationByIdAndStateAndDir(int id, ActMotion motion, ActDir dir)
{
	Animation* anim = nullptr;
	do 
	{
		auto it = _humAtlasConfig.find(id);
		CC_BREAK_IF(it == _humAtlasConfig.end());
		auto tex = TextureCache::getInstance()->addImage("hum/" + it->second.file + ".png");
		CC_BREAK_IF(tex == nullptr);
		auto info = it->second.getActionInfo(motion);
		int id = info.beginframe + info.framecount * (int)dir;
		Vector<SpriteFrame*> frames;
		Point offset = Point::ZERO;
		for (int i = id; i < id + info.framecount; ++i)
		{
			AtlasDesc desc = getAtlasDescById(it->second.file, i);
			SpriteFrame* sframe = SpriteFrame::createWithTexture(tex, Rect(desc.x,desc.y,desc.w,desc.h));
			//if (offset == Point::ZERO)
			{
				offset = Point(desc.cx, -(desc.cy + desc.h));
			}
			sframe->setOffset(offset);
			frames.pushBack(sframe);
		}
		anim = Animation::createWithSpriteFrames(frames);
		anim->setDelayPerUnit(info.delay / 1000.0f);
	} while (0);
	return anim;
}

AtlasDesc GameAtlasMgr::getAtlasDescById(const string& key, const int& id)
{
	auto it1 = _atlasInfo.find(key);
	if (it1 != _atlasInfo.end())
	{
		auto it2 = it1->second.desc.find(id);
		if (it2 != it1->second.desc.end())
		{
			return it2->second;
		}
	}
	return AtlasDesc();
}

Animation* GameAtlasMgr::getWeaponAnimationByIdAndStateAndDir(int id, ActMotion motion, ActDir dir)
{
	Animation* anim = nullptr;
	do
	{
		auto it = _weaponAtlasConfig.find(id);
		CC_BREAK_IF(it == _weaponAtlasConfig.end());
		auto tex = TextureCache::getInstance()->addImage("weapon/" + it->second.file + ".png");
		CC_BREAK_IF(tex == nullptr);
		auto info = it->second.getActionInfo(motion);
		int id = info.beginframe + info.framecount * (int)dir;
		Vector<SpriteFrame*> frames;
		Point offset = Point::ZERO;
		for (int i = id; i < id + info.framecount; ++i)
		{
			AtlasDesc desc = getAtlasDescById(it->second.file, i);
			SpriteFrame* sframe = SpriteFrame::createWithTexture(tex, Rect(desc.x, desc.y, desc.w, desc.h));
			offset = Point(desc.cx, -(desc.cy + desc.h));
			sframe->setOffset(offset);
			frames.pushBack(sframe);
		}
		anim = Animation::createWithSpriteFrames(frames);
		anim->setDelayPerUnit(info.delay / 1000.0f);
	} while (0);
	return anim;
}

void GameAtlasMgr::init()
{
	loadHumAtlasConfig();
	loadWeaponAtlasConfig();
	loadSkillInfoConfig();
	loadEffectAtlasConfig();
	loadHairAtlasConfig();
	loadHumAction3DInfoConfig();
	// 清空文理
	Director::getInstance()->getScheduler()->schedule(schedule_selector(GameAtlasMgr::removeUnUseTextures), this, 30.0f, false);
}

void GameAtlasMgr::loadEffectAtlasConfig()
{
	FileReader* reader = new FileReader;
	reader->readFromTxt(effect_config);
	while (reader->isEof())
	{
		AtlasConfig config;
		config.id = reader->getValue("id").asInt();
		config.file = reader->getValue("file").asString();
		int type = (int)ActMotion::stand;
		do
		{
			ActionInfo info;
			info.effecttype = (EffectType)reader->getValue("action").asInt();
			info.beginframe = reader->getValue("frame").asInt();
			info.framecount = reader->getValue("count").asInt();
			info.dir = reader->getValue("dir").asInt();
			info.delay = reader->getValue("delay").asInt();
			config.info.push_back(info);
			reader->moveNextRow();
			type++;
		} while (reader->isEof() && reader->getValue("id").asString() == "");

		_effectAtlasConfig.insert(make_pair(config.id, config));

		loadAltasDesc(config.file, StringUtils::format("effect/%s.xml", config.file.c_str()));
	}
	CC_SAFE_DELETE(reader);
}

void GameAtlasMgr::loadHairAtlasConfig()
{
	FileReader* reader = new FileReader;
	reader->readFromTxt(hair_config);
	while (reader->isEof())
	{
		AtlasConfig config;
		config.id = reader->getValue("id").asInt();
		config.file = reader->getValue("file").asString();
		int type = (int)ActMotion::stand;
		do
		{
			ActionInfo info;
			info.type = (ActMotion)type;
			info.beginframe = reader->getValue("frame").asInt();
			info.framecount = reader->getValue("count").asInt();
			info.dir = reader->getValue("dir").asInt();
			info.delay = reader->getValue("delay").asInt();
			config.info.push_back(info);
			reader->moveNextRow();
			type++;
		} while (reader->isEof() && reader->getValue("id").asString() == "");

		_hairAtlasConfig.insert(make_pair(config.id, config));

		loadAltasDesc(config.file, StringUtils::format("hair/%s.xml", config.file.c_str()));
	}
	CC_SAFE_DELETE(reader);
}


vector<EffectAnim> GameAtlasMgr::getEffectAnimationByIdAndStateAndDir(int id, ActDir dir /*= ActDir::DIR_UP*/, int dir16 /*= 0*/)
{
	vector<EffectAnim> anims;
	Animation* anim = nullptr;
	do
	{
		auto it = _effectAtlasConfig.find(id);
		CC_BREAK_IF(it == _effectAtlasConfig.end());
		auto tex = TextureCache::getInstance()->addImage("effect/" + it->second.file + ".png");
		CC_BREAK_IF(tex == nullptr);
		for (auto info : it->second.info)
		{
			int curdir = 0;
			if (info.dir == 8)
			{
				curdir = (int)dir;
			}
			else if (info.dir == 16)
			{
				curdir = dir16;
			}
			EffectType effect = info.effecttype;
			int id = info.beginframe + info.framecount * curdir;
			Vector<SpriteFrame*> frames;
			Point offset = Point::ZERO;
			for (int i = id; i < id + info.framecount; ++i)
			{
				AtlasDesc desc = getAtlasDescById(it->second.file, i);
				SpriteFrame* sframe = SpriteFrame::createWithTexture(tex, Rect(desc.x, desc.y, desc.w, desc.h));
				offset = Point(desc.cx, -(desc.cy + desc.h));
				sframe->setOffset(offset);
				frames.pushBack(sframe);
			}
			anim = Animation::createWithSpriteFrames(frames);
			anim->setDelayPerUnit(info.delay / 1000.0f);
			anims.push_back(EffectAnim(effect, anim));
		}

	} while (0);
	return anims;
}

void GameAtlasMgr::loadSkillInfoConfig()
{
	FileReader* reader = new FileReader;
	reader->readFromTxt(skill_config);
	while (reader->isEof())
	{
		SkillInfo config;
		config.isValid = true;
		config.distance = reader->getValue("distance").asInt();
		config.skillId = reader->getValue("id").asInt();
		config.effectId = reader->getValue("effect").asInt();
		config.skilltype = (SkillType)reader->getValue("type").asInt();
		_skillInfo.insert(make_pair(config.skillId, config));
		reader->moveNextRow();
	}
	CC_SAFE_DELETE(reader);
}

SkillInfo GameAtlasMgr::getSkillInfoById(int id)
{
	auto iter = _skillInfo.find(id);
	if (iter != _skillInfo.end())
	{
		return iter->second;
	}
	return SkillInfo();
}

void GameAtlasMgr::removeUnUseTextures(float dt)
{
	//TextureCache::getInstance()->removeUnusedTextures();
}

Animation* GameAtlasMgr::getHairAnimationByIdAndStateAndDir(int id, ActMotion motion, ActDir dir)
{
	Animation* anim = nullptr;
	do
	{
		auto it = _hairAtlasConfig.find(id);
		CC_BREAK_IF(it == _hairAtlasConfig.end());
		auto tex = TextureCache::getInstance()->addImage("hair/" + it->second.file + ".png");
		CC_BREAK_IF(tex == nullptr);
		auto info = it->second.getActionInfo(motion);
		int id = info.beginframe + info.framecount * (int)dir;
		Vector<SpriteFrame*> frames;
		Point offset = Point::ZERO;
		for (int i = id; i < id + info.framecount; ++i)
		{
			AtlasDesc desc = getAtlasDescById(it->second.file, i);
			SpriteFrame* sframe = SpriteFrame::createWithTexture(tex, Rect(desc.x, desc.y, desc.w, desc.h));
			offset = Point(desc.cx, -(desc.cy + desc.h));
			sframe->setOffset(offset);
			frames.pushBack(sframe);
		}
		anim = Animation::createWithSpriteFrames(frames);
		anim->setDelayPerUnit(info.delay / 1000.0f);
	} while (0);
	return anim;
}

void GameAtlasMgr::loadHumAction3DInfoConfig()
{
	FileReader* reader = new FileReader;
	reader->readFromTxt(hum3d_config);
	while (reader->isEof())
	{
		Action3DConfig config;
		config.id = reader->getValue("id").asInt();
		config.file = reader->getValue("file").asString();
		int type = (int)ActMotion::stand;
		do
		{
			Action3DInfo info;
			info.type = (ActMotion)type;
			info.beginframe = reader->getValue("began").asInt();
			info.endframe = reader->getValue("end").asInt();
			config.info.push_back(info);
			reader->moveNextRow();
			type++;
		} while (reader->isEof() && reader->getValue("id").asString() == "");

		_action3DInfo.insert(make_pair(config.id, config));
	}
	CC_SAFE_DELETE(reader);
}

std::string GameAtlasMgr::getHum3DFileName(int id)
{
	string file = "";
	auto it = _action3DInfo.find(id);
	if (it != _action3DInfo.end())
	{
		file = hum3d_dir + it->second.file + ".c3b";
	}
	return file;
}

GameAnimation3D* GameAtlasMgr::getHum3DAnimationByIdAndState(int id, ActMotion state)
{
	GameAnimation3D* anim = nullptr;
	auto it = _action3DInfo.find(id);
	if (it != _action3DInfo.end())
	{
		string file = hum3d_dir + it->second.file + "_anim.c3b";
		Action3DInfo info = it->second.getAction3DInfo(state);
		anim = GameAnimation3D::create(file, info.beginframe, info.endframe);
	}
	return anim;
}


