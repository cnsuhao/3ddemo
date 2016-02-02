#include "ObjectData3D.h"


ObjectData3D::ObjectData3D()
{

}

ObjectData3D::~ObjectData3D()
{

}


ObjectData3D* ObjectData3D::create()
{
	ObjectData3D* data = new ObjectData3D;
	data->autorelease();
	return data;
}

void ObjectData3D::init(int id, int dressId, float dir, ActMotion aniState, Point pos, string mapId, int hp, int mp)
{
	m_dir = 0.0f;
	m_id = id;
	m_dressId = dressId;
	m_aniState = aniState;
	m_pos = pos;
	m_mapId = mapId;
	m_hp = hp;
	m_mp = mp;
	m_hpMax = hp;
	m_mpMax = mp;
	m_isLive = true;
}
