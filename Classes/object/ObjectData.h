#ifndef GAMEDATA_H
#define GAMEDATA_H

#include "GameAtlasMgr.h"

class ObjectData:public Ref
{

public:

	ObjectData();

	virtual ~ObjectData();

	static ObjectData* create();

	void init(int id, int dressId, ActDir dir, ActMotion aniState, Point pos, string mapId, int hp, int mp, int job = 1);

	Point getTileMapPos(){ return m_pos; }
	string	getName(){ return m_name; }
	int		getHP(){ return m_hp; }
	int		getHPMax(){ return m_hpMax; }
	int		getMP(){ return m_mp; }
	int		getMPMax(){ return m_mpMax; }
	void setWeaponId(int id){ m_weaponId = id; }
	void setName(string name){ m_name = name; }
	void setRect(Rect rect){ m_rect = rect; }
public:
	// 衣服
	int			m_dressId;
	// 武器
	int			m_weaponId;
	// 头发
	int			m_hairId;
	// 方向
	ActDir		m_dir;
	// 状态
	ActMotion	m_aniState;
	// 位置
	Point		m_pos;
	// 地图
	string		m_mapId;
	// hp
	int			m_hp;
	int			m_hpMax;
	// mp
	int			m_mp;
	int			m_mpMax;
	//
	int			m_id;
	//
	int			m_job;

	string		m_name;

	Rect		m_rect;

	bool		m_isLive;
};


#endif