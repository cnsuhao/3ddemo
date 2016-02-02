#include "ObjectData3DMgr.h"

#pragma execution_character_set("utf-8")

ObjectData3DMgr* ObjectData3DMgr::s_dataMgr = nullptr;



ObjectData3DMgr::ObjectData3DMgr()
{

}

ObjectData3DMgr::~ObjectData3DMgr()
{

}

ObjectData3DMgr* ObjectData3DMgr::getInstance()
{
	if (!s_dataMgr)
	{
		s_dataMgr = new ObjectData3DMgr;
		s_dataMgr->initData();
	}
	return s_dataMgr;
}

void ObjectData3DMgr::destroyInstance()
{
	if (s_dataMgr)
	{
		CC_SAFE_DELETE(s_dataMgr);
	}
}

void ObjectData3DMgr::initData()
{

}

ObjectData3D* ObjectData3DMgr::getMainObjectData()
{
	return m_mainData;
}

void ObjectData3DMgr::addPlayerData(ObjectData3D* data)
{
	if (data)
	{
		data->retain();
		m_playerDataList.push_back(data);
	}
}

vector<ObjectData3D*> ObjectData3DMgr::getPlayList()
{
	return m_playerDataList;
}

void ObjectData3DMgr::setMainData(int job)
{
	// 主角 
	m_mainData = ObjectData3D::create();
	m_mainData->retain();
	m_mainData->init(1, 2, 0.0f, ActMotion::stand, Point(48 * 10, 48 * 10), "m1", 50000, 10000);
	m_mainData->setName("张三");
}

void ObjectData3DMgr::clearObjectDatas()
{
	for (auto data : m_playerDataList)
	{
		data->release();
	}
	m_playerDataList.clear();

	m_mainData->m_aniState = ActMotion::stand;
}
