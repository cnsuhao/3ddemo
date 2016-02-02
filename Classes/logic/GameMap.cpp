#include "GameMap.h"
#include "ObjectDataMgr.h"
#include "GamePlayer.h"
#include "GameObjectMgr.h"
#include "Global.h"
#include "UIManager.h"
#include "ObjectData.h"
#include "ObjectDataMgr.h"
#include "UIEffectMgr.h"
#include "GameObject3DMgr.h"
#include "ObjectData3DMgr.h"
#pragma execution_character_set("utf-8")

GameMap* GameMap::_sGameMap = nullptr;

GameMap::GameMap():
_alphaLayer(nullptr),
_blockLayer(nullptr),
_unitGroup(nullptr),
_gridNode(nullptr),
_effectNode(nullptr),
_moveArrow(nullptr),
_chuansongpt("")
{

}

GameMap::~GameMap()
{

}

GameMap* GameMap::getInstance()
{
	if (!_sGameMap)
	{
		_sGameMap = new GameMap;
		_sGameMap->init();
		_sGameMap->setAnchorPoint(Point::ZERO);
	}
	return _sGameMap;
}

void GameMap::destroyInstance()
{
	if (_sGameMap)
	{
		_sGameMap->removeFromParent();
		CC_SAFE_RELEASE_NULL(_sGameMap);
	}
}

void GameMap::setTileMap()
{
	do 
	{
		auto maindata = ObjectData3DMgr::getInstance()->getMainObjectData();
		CC_BREAK_IF(maindata == nullptr);
		_tileMap = experimental::TMXTiledMap::create(StringUtils::format("map/%s.tmx", maindata->m_mapId.c_str()));
		CC_BREAK_IF(_tileMap == nullptr);
		this->addChild(_tileMap,(int)Zorder::order_map);
		//_tileMap->setVisible(false);
		_gridNode = DrawGridNode::create(_tileMap);
		_gridNode->setGrideSize(Size(map_grid_width, map_grid_height));
		this->addChild(_gridNode, (int)Zorder::order_grid);
		_gridNode->setVisible(false);

		_triggerNode = Node::create();
		this->addChild(_triggerNode, (int)Zorder::order_effect);

		_effectNode = Node::create();
		this->addChild(_effectNode, (int)Zorder::order_effect);
		_mapSize = _tileMap->getMapSize();
		_alphaLayer = _tileMap->getLayer("alpha");
		if (_alphaLayer)
		{
			_alphaLayer->setVisible(false);
		}
		_blockLayer = _tileMap->getLayer("block");
		if (_blockLayer)
		{
			_blockLayer->setVisible(false);
		}
		_triggerGroup = _tileMap->getObjectGroup("trigger");
		if (_triggerGroup)
		{
			auto vec = _triggerGroup->getObjects();
			for (int i = 0; i < vec.size(); ++i)
			{
				ValueMap prop = vec[i].asValueMap();
				int x = prop["x"].asInt();
				int y = prop["y"].asInt();
				int w = prop["width"].asInt();
				int h = prop["height"].asInt();

				UIEffectMgr::getInstance()->playEffect("chuansongmen", _triggerNode, Point(x + w / 2, y + h / 2), true);
			}

		}
		_unitGroup = _tileMap->getObjectGroup("unit");
		if (_unitGroup)
		{
			auto vec = _unitGroup->getObjects();
			for (int i = 0; i < vec.size(); ++i)
			{
				ValueMap prop = vec[i].asValueMap();

				int x_f = prop["x"].asInt();
				int y_f = prop["y"].asInt();
				int w_f = prop["width"].asInt();
				int h_f = prop["height"].asInt();

				int x = x_f / map_grid_width;
				int y = _mapSize.height - y_f / map_grid_height;
				int w = ceil(w_f / map_grid_width);
				int h = ceil(h_f / map_grid_height);

				string name = prop["name"].asString();
				ObjectData* objdata = ObjectData::create();
				int dressId = RandomHelper::random_int(1, 4);
				int job = dressId > 3 ? 1 : dressId;
				int hp = 1000, mp = 1000;
				if (job == 1)
				{
					hp = 30000;
					mp = 10000;
				}
				else
				{
					hp = 15000;
					mp = 20000;
				}
				objdata->init(i + 2, dressId, ActDir(i % 8), ActMotion::stand, Point(x, y), maindata->m_mapId, hp, mp, job);
				objdata->setName(StringUtils::format("李%d",i));
				objdata->setRect(Rect(x,y,w,h));
				if (objdata->m_dressId != 4)
				{
					objdata->setWeaponId(1);
				}
				ObjectDataMgr::getInstance()->addPlayerData(objdata);
				// 3d
				ObjectData3D* objdata3d = ObjectData3D::create();
				objdata3d->init(i + 1000, dressId % 2 + 1, 0.0f, ActMotion::stand, Point((1 - i + 10) * 48, (1 - i + 10) * 48), maindata->m_mapId, hp, mp);
				objdata3d->setRect(Rect(x_f, y_f, w_f, h_f));
				ObjectData3DMgr::getInstance()->addPlayerData(objdata3d);
			}

			_wayPTGroup = _tileMap->getObjectGroup("waypoint");
			// 传送点
			if (_chuansongpt != "" && _wayPTGroup)
			{
				if (_wayPTGroup)
				{
					auto vecs = _wayPTGroup->getObjects();
					for (int i = 0; i < vecs.size(); ++i)
					{
						auto prop = vecs[i].asValueMap();
						string name = prop["name"].asString();
						if (name == _chuansongpt)
						{
							int x = prop["x"].asInt() / map_grid_width;
							int y = _mapSize.height - prop["y"].asInt() / map_grid_height;

							auto maindata = ObjectDataMgr::getInstance()->getMainObjectData();
							if (maindata)
							{
								maindata->m_pos = Point(x, y);
							}
							break;
						}
					}
				}
			}
		}

	} while (0);

}

void GameMap::loadObjects()
{
	// 箭头
	_moveArrow = Sprite::create("ui/common/movearrow.png", Rect(0, 0, 120, 128));
	this->addChild(_moveArrow, (int)Zorder::order_grid);
	_moveArrow->setVisible(false);

	//auto mgr = GameObjectMgr::getInstance();
	//if (mgr)
	//{
	//	this->addChild(mgr, (int)Zorder::order_obj);
	//	mgr->loadObjects();
	//}
	auto mgr3d = GameObject3DMgr::getInstance();
	if (mgr3d)
	{
		this->addChild(mgr3d, (int)Zorder::order_obj);
		mgr3d->loadObjects(); 
	}
}

Point GameMap::convertTilePosToNodePos(Point tile)
{
	// tmx  Y从上到下是正方向
	float x = map_grid_width * tile.x;
	float y = map_grid_height * (_mapSize.height - tile.y - 1);

	return Point(x, y) + Point(map_grid_width / 2, 0);
}

void GameMap::adjustPosition()
{
	auto player = GameObject3DMgr::getInstance()->getMainGamePlayer();
	if (player)
	{
		Point my_pos = player->getTilePos();
		Point map_pos = Point::ZERO;
		float minX = designSize.width - map_grid_width * _mapSize.width;
		float maxX = 0.0f;
		float minY = designSize.height - map_grid_height * _mapSize.height;
		float maxY = 0.0f;
		map_pos.x = designSize.width / 2 - my_pos.x;
		map_pos.y = designSize.height / 2 - my_pos.y;
		// 校准位置
		if (map_pos.x < minX)
		{
			map_pos.x = minX;
		}
		if (map_pos.y < minY)
		{
			map_pos.y = minY;
		}
		if (map_pos.x > maxX)
		{
			map_pos.x = maxX;
		}
		if (map_pos.y > maxY)
		{
			map_pos.y = maxY;
		}
		this->setPosition(map_pos);
	}
}

bool GameMap::canMove(int x, int y)
{
	// 在地图范围内
	if (!_blockLayer ||( x >= 2 && x < _mapSize.width - 1 && y >= 2 && y < _mapSize.height - 1 && _blockLayer->getTileAt(Point(x, y)) == nullptr))
	{
		return true;
	}
	return false;
}


bool GameMap::canMovePixel(float x, float y)
{
	Point pt = convertPixelPosToTilePos(Point(x, y));
	return canMove(pt.x, pt.y);
}

Point GameMap::convertWorldPosToTilePos(Point pos)
{
	Point nodePos = _tileMap->convertToNodeSpace(pos);

	int tile_x = nodePos.x / map_grid_width;
	int tile_y = nodePos.y / map_grid_height;

	tile_y = _mapSize.height - tile_y - 1;

	return Point(tile_x, tile_y);
}


Point GameMap::convertPixelPosToTilePos(Point pos)
{
	int tile_x = pos.x / map_grid_width;
	int tile_y = pos.y / map_grid_height;

	tile_y = _mapSize.height - tile_y - 1;

	return Point(tile_x, tile_y);
}

Size GameMap::getMapSize()
{
	return _mapSize;
}

void GameMap::onGridChangeShow(Ref* pSender, GameEvent* gEvent)
{
	if (_gridNode)
	{
		bool isVisible = _gridNode->isVisible();
		_gridNode->setVisible(!isVisible);
	}
}

bool GameMap::init()
{
	UIManager::getInstance()->getDispatcher()->addGameEventListener((int)GameEventId::grid_changeshow, CC_CALLBACK_2(GameMap::onGridChangeShow, this), this);
	return true;
}


void GameMap::runMoveArrowAnim(Point pt)
{
	auto pos = this->convertToNodeSpace(pt);
	Animation* animation = Animation::create();
	for (int i = 0; i < 7; ++i)
	{
		SpriteFrame* frame = SpriteFrame::create("ui/common/movearrow.png", Rect(i * 120, 0, 120, 128));
		if (frame)
		{
			animation->addSpriteFrame(frame);
		}
	}
	animation->setDelayPerUnit(0.1f);
	Animate* animate = Animate::create(animation);
	CallFunc* callFunc = CallFunc::create(
		[=](){_moveArrow->setVisible(false); }
	);
	_moveArrow->stopAllActions();
	_moveArrow->setVisible(true);
	_moveArrow->setPosition(pos);
	_moveArrow->runAction(Sequence::create(animate, callFunc, nullptr));
}

bool GameMap::checkIsChuanSongPoint(Point pt)
{
	if (_triggerGroup)
	{
		pt = convertTilePosToNodePos(pt);
		auto vec = _triggerGroup->getObjects();
		for (int i = 0; i < vec.size(); ++i)
		{
			ValueMap prop = vec[i].asValueMap();
			float x = prop["x"].asFloat();
			float y = prop["y"].asFloat();
			float w = prop["width"].asFloat();
			float h = prop["height"].asFloat();
			if (Rect(x, y, w, h).containsPoint(pt))
			{
				_chuansongpt = prop["WayPointName"].asString();
				GameEvent* gEvent = GameEvent::create(GameEventId::change_map);
				gEvent->setParamStr(prop["MapName"].asString());
				GameDispatcher::getInstance()->dispatcherGameEvent(gEvent, this);
				return true;
			}
		}
	}

	return false;
}

vector<string> GameMap::getMapImages()
{
	vector<string> images;
	auto mainData = ObjectData3DMgr::getInstance()->getMainObjectData();
	if (mainData)
	{
		TMXMapInfo *mapInfo = TMXMapInfo::create(StringUtils::format("map/%s.tmx", mainData->m_mapId.c_str()));
		if (mapInfo)
		{
			auto tilesets = mapInfo->getTilesets();
			for (auto item : tilesets)
			{
				images.push_back(item->_sourceImage);
			}

			map_grid_width = mapInfo->getTileSize().width;
			map_grid_height = mapInfo->getTileSize().height;
		}
	}

	return images;
}

cocos2d::Point GameMap::getFarestChuanSongPoint()
{
	Point chuansong = Point::ZERO;
	auto mainData = ObjectDataMgr::getInstance()->getMainObjectData();
	if (mainData && _triggerGroup)
	{
		float distance = -1;
		Point myPos = mainData->m_pos;
		auto vec = _triggerGroup->getObjects();
		for (int i = 0; i < vec.size(); ++i)
		{
			ValueMap prop = vec[i].asValueMap();
			int x = prop["x"].asInt() / map_grid_width;
			int y = _mapSize.height - prop["y"].asInt() / map_grid_height - 1;
			int w = prop["width"].asInt() / map_grid_width;
			int h = prop["height"].asInt() / map_grid_height;

			string mapName = prop["MapName"].asString();
			Point pt = Point(x + w / 2, y - h / 2);
			float d = pt.distance(myPos);
			if (d > distance && mapName[0] == 'm')
			{
				distance = d;
				chuansong = pt;
			}
		}
	}

	return chuansong;
}

bool GameMap::isAlphaPoint(Point pt)
{
	if (_alphaLayer && _alphaLayer->getTileAt(pt))
	{
		return true;
	}
	return false;
}

bool GameMap::isAlphaPixelPoint(Point pt)
{
	pt = convertPixelPosToTilePos(pt);
	return isAlphaPoint(pt);
}

void GameMap::clearResources()
{
	this->removeAllChildren();
	GameObjectMgr::getInstance()->clearGameOjects();
	ObjectDataMgr::getInstance()->clearObjectDatas();
	TextureCache::getInstance()->removeUnusedTextures();
}


cocos2d::Vec3 GameMap::converPointToVec3(Point point)
{
	auto objCamera = GameObject3DMgr::getInstance()->getObject3DCamera();
	Point location = this->convertToWorldSpace(point);
	Vec3 nearP(location.x, location.y, -1.0f), farP(location.x, location.y, 1.0f);
	auto size = Director::getInstance()->getWinSize();
	nearP = objCamera->unprojectGL(nearP);
	farP = objCamera->unprojectGL(farP);
	Vec3 dir(farP - nearP);
	float dist = 0.0f;
	float ndd = Vec3::dot(Vec3(0, 1, 0), dir);
	if (ndd == 0)
		dist = 0.0f;
	float ndo = Vec3::dot(Vec3(0, 1, 0), nearP);
	dist = (0 - ndo) / ndd;
	Vec3 p = nearP + dist *  dir;
	return p;
}


