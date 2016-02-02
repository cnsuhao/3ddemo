#include "ObjectDataMgr.h"

#pragma execution_character_set("utf-8")

ObjectDataMgr* ObjectDataMgr::s_dataMgr = nullptr;



ObjectDataMgr::ObjectDataMgr():
m_mainData(nullptr)
{
}

ObjectDataMgr::~ObjectDataMgr()
{

}

ObjectDataMgr* ObjectDataMgr::getInstance()
{
	if (!s_dataMgr)
	{
		s_dataMgr = new ObjectDataMgr;
		s_dataMgr->initData();
	}
	return s_dataMgr;
}

void ObjectDataMgr::destroyInstance()
{
	if (s_dataMgr)
	{
		CC_SAFE_DELETE(s_dataMgr);
	}
}

void ObjectDataMgr::initData()
{

}

ObjectData* ObjectDataMgr::getMainObjectData()
{
	return m_mainData;
}

void ObjectDataMgr::addPlayerData(ObjectData* data)
{
	if (data)
	{
		data->retain();
		m_playerDataList.push_back(data);
	}
}

vector<ObjectData*> ObjectDataMgr::getPlayList()
{
	return m_playerDataList;
}

void ObjectDataMgr::setMainData(int job)
{
	// 主角 
	m_mainData = ObjectData::create();
	m_mainData->retain();
	m_mainData->init(1, job == 1? 5 : job, ActDir::DIR_DOWN, ActMotion::stand, Point(75, 35), "m1", 50000, 10000, job);
	m_mainData->setName("张三");
	m_mainData->setWeaponId(1);
}

int ObjectDataMgr::getMainPlayerJob()
{
	if (m_mainData)
	{
		return m_mainData->m_job;
	}
	return 0;
}

void ObjectDataMgr::clearObjectDatas()
{
	for (auto data : m_playerDataList)
	{
		data->release();
	}
	m_playerDataList.clear();
	if (m_mainData)
	{
		m_mainData->m_aniState = ActMotion::stand;
	}

}
