#ifndef GAMEDATA3D_H
#define GAMEDATA3D_H

#include "GameAtlasMgr.h"

class ObjectData3D:public Ref
{
public:

	ObjectData3D();
	virtual ~ObjectData3D();

	static ObjectData3D* create();

	// 初始化
	void init(int id, int dressId, float dir, ActMotion aniState, Point pos, string mapId, int hp, int mp);
	// 获取信息
	Point getTileMapPos(){ return m_pos; }
	string	getName(){ return m_name; }
	int		getHP(){ return m_hp; }
	int		getHPMax(){ return m_hpMax; }
	int		getMP(){ return m_mp; }
	int		getMPMax(){ return m_mpMax; }
	void setName(string name){ m_name = name; }
	void setRect(Rect rect){ m_rect = rect; }
public:
	// 衣服
	int			m_dressId;
	// 朝向
	float		m_dir;
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
	// id
	int			m_id;
	// 名字
	string		m_name;
	// 活动范围
	Rect		m_rect;
	// 是否活着
	bool		m_isLive;
};


#endif