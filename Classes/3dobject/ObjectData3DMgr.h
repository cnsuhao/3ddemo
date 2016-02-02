#ifndef OBJECTDATA3DMGR_H
#define OBJECTDATA3DMGR_H

#include "ObjectData3D.h"

class ObjectData3DMgr
{
public:

	ObjectData3DMgr();

	virtual ~ObjectData3DMgr();

	static ObjectData3DMgr* getInstance();

	static void destroyInstance();

	void initData();

	void setMainData(int job);

	ObjectData3D* getMainObjectData();

	void addPlayerData(ObjectData3D* data);

	vector<ObjectData3D*> getPlayList();

	void clearObjectDatas();
private:

	// 主玩家
	ObjectData3D*			m_mainData;
	// 玩家列表
	vector<ObjectData3D*> m_playerDataList;

	static ObjectData3DMgr* s_dataMgr;
};


#endif