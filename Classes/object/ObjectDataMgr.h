#ifndef OBJECTDATAMGR_H
#define OBJECTDATAMGR_H

#include "ObjectData.h"

class ObjectDataMgr
{
public:

	ObjectDataMgr();

	virtual ~ObjectDataMgr();

	static ObjectDataMgr* getInstance();

	static void destroyInstance();

	void initData();

	void setMainData(int job);

	ObjectData* getMainObjectData();

	void addPlayerData(ObjectData* data);

	vector<ObjectData*> getPlayList();

	int	getMainPlayerJob();

	void clearObjectDatas();
private:

	// 主玩家
	ObjectData*			m_mainData;
	// 玩家列表
	vector<ObjectData*> m_playerDataList;
	// NPC列表
	vector<ObjectData*> m_npcDataList;
	// 怪物列表
	vector<ObjectData*> m_monsterDataList;

	static ObjectDataMgr* s_dataMgr;
};


#endif