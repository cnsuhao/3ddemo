#include "ObjectData.h"


ObjectData::ObjectData()
{
	m_weaponId = 0;
	m_hairId = 0;
}

ObjectData::~ObjectData()
{

}


ObjectData* ObjectData::create()
{
	ObjectData* data = new ObjectData;
	data->autorelease();
	return data;
}

void ObjectData::init(int id, int dressId, ActDir dir, ActMotion aniState, Point pos, string mapId, int hp, int mp, int job)
{
	m_id = id;
	m_dressId = dressId;
	m_dir = dir;
	m_aniState = aniState;
	m_pos = pos;
	m_mapId = mapId;
	m_hp = hp;
	m_mp = mp;
	m_job = job;
	m_hpMax = hp;
	m_mpMax = mp;
	m_isLive = true;

	if (m_dressId != 2 && m_dressId != 4)
	{
		m_hairId = 1;
	}
	else
	{
		m_hairId = 0;
	}
}
