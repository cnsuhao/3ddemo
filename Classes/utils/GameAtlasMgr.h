#ifndef _GAMEATLASMGR_H_
#define _GAMEATLASMGR_H_

#include "CocosHead.h"
#include "Global.h"
#include "GameAction3D.h"
enum class EffectType
{
	nil		= 0,
	start	= 1,
	fly		= 2,
	hit		= 3,
};
// 动作信息
struct ActionInfo
{
	ActMotion type;
	int beginframe;
	int framecount;
	int dir;
	int delay;
	EffectType effecttype;
};

// 3D动作信息
struct Action3DInfo
{
	ActMotion type = ActMotion::nil;
	int beginframe = 0;
	int endframe = 0;
};

// 3D动作集合
struct Action3DConfig
{
	int		  id;
	string	  file;
	vector<Action3DInfo> info;
	Action3DInfo getAction3DInfo(ActMotion type)
	{
		for (auto it : info)
		{
			if (it.type == type)
			{
				return it;
			}
		}
		return Action3DInfo();
	}
};


// 动作集合
struct AtlasConfig
{
	int		  id;
	string	  file;
	vector<ActionInfo> info;
	ActionInfo getActionInfo(ActMotion type)
	{
		for (auto it:info)
		{
			if (it.type == type)
			{
				return it;
			}
		}
		return ActionInfo();
	}
};
// 图块信息
struct AtlasDesc
{
	unsigned short id;
	unsigned short x;
	unsigned short y;
	unsigned short w;
	unsigned short h;
	short cx;
	short cy;
	bool isValid = false;
};

struct AtlasInfo
{
	string path;
	map<int, AtlasDesc> desc;
};

enum class SkillType
{
	hit		= 1,
	magic	= 2,
};



struct EffectAnim
{
	EffectType	effect;
	Animation*	anim;
	EffectAnim(EffectType t,Animation* a)
	{
		effect	= t;
		anim	= a;
	}
};
//
struct SkillInfo
{
	int distance = 0;
	int skillId = 0;
	int effectId = 0;
	bool isValid = false;
	SkillType skilltype = SkillType::hit; //1:hit 2:magic
};
// 管理
class GameAtlasMgr:public Ref
{
public:
	// 配置
	const string skill_config	= "config/skill.txt";
	const string hum_config		= "config/hum.txt";
	const string effect_config	= "config/effect.txt";
	const string weapon_config	= "config/weapon.txt";
	const string hair_config = "config/hair.txt";
	const string hum3d_config = "config/hum3d.txt";
	// 路径
	const string hum3d_dir = "hum3d/";
public:
	GameAtlasMgr();
	~GameAtlasMgr();
	static GameAtlasMgr* getInstance();
	static void destroyInstance();
	void loadHumAtlasConfig();
	void loadEffectAtlasConfig();
	void loadWeaponAtlasConfig();
	void loadSkillInfoConfig();
	void loadHairAtlasConfig();
	void loadHumAction3DInfoConfig();
	void loadAltasDesc(const string& key,const string& filename);
	
	string getHum3DFileName(int id);
	GameAnimation3D* getHum3DAnimationByIdAndState(int id, ActMotion state);
	Animation* getHumAnimationByIdAndStateAndDir(int id, ActMotion motion, ActDir dir);
	Animation* getWeaponAnimationByIdAndStateAndDir(int id, ActMotion motion, ActDir dir);
	Animation* getHairAnimationByIdAndStateAndDir(int id, ActMotion motion, ActDir dir);
	vector<EffectAnim> getEffectAnimationByIdAndStateAndDir(int id, ActDir dir = ActDir::DIR_UP,int dir16 = 0);
	SkillInfo getSkillInfoById(int id);

	void removeUnUseTextures(float dt);
private:
	AtlasDesc getAtlasDescById(const string& key,const int& id);

	void init();
private:
	// 动作配置
	map<int, AtlasConfig> _humAtlasConfig;
	// 武器配置
	map<int, AtlasConfig> _weaponAtlasConfig;
	// 特效配置
	map<int, AtlasConfig> _effectAtlasConfig;
	// 头发配置
	map<int, AtlasConfig> _hairAtlasConfig;

	// 图片偏移信息
	map<string, AtlasInfo> _atlasInfo;
	// 技能信息
	map<int, SkillInfo>	   _skillInfo;
	// 3D动作配置
	map<int, Action3DConfig> _action3DInfo;
	static GameAtlasMgr* _GameAtlasMgr;
};




#endif