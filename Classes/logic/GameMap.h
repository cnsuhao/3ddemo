#ifndef __GAMEMAP_H__
#define __GAMEMAP_H__

#include "CocosHead.h"
#include "DrawHelper.h"
#include "GameEvent.h"
#include "2d/CCFastTMXTiledMap.h"
class GameMap:public Node
{
public:

	const int map_tag = 100;
	const int mgr_tag = 200;

	GameMap();

	virtual ~GameMap();

	static GameMap* getInstance();

	static void destroyInstance();

	virtual bool init();

	void setTileMap();

	void loadObjects();

	Point convertTilePosToNodePos(Point tile);

	Point convertWorldPosToTilePos(Point pos);

	Point convertPixelPosToTilePos(Point pos);

	void adjustPosition();

	bool canMove(int x,int y);

	bool canMovePixel(float x, float y);

	Size getMapSize();

	void onGridChangeShow(Ref* pSender, GameEvent* gEvent);

	Node* getEffectNode(){ return _effectNode; }

	void runMoveArrowAnim(Point pt);

	bool checkIsChuanSongPoint(Point pt);

	Point getFarestChuanSongPoint();

	vector<string> getMapImages();

	bool isAlphaPoint(Point pt);

	bool isAlphaPixelPoint(Point pt);

	void clearResources();

	cocos2d::Vec3 converPointToVec3(Point point);
private:
	Sprite*			_moveArrow;
	Node*			_effectNode;
	Node*			_triggerNode;
	DrawGridNode*	_gridNode;
	experimental::TMXTiledMap*	_tileMap;
	Size			_mapSize;
	experimental::TMXLayer*		_alphaLayer;
	experimental::TMXLayer*		_blockLayer;
	TMXObjectGroup* _unitGroup;
	TMXObjectGroup* _wayPTGroup;
	TMXObjectGroup* _triggerGroup;
	string			_chuansongpt;
	static GameMap* _sGameMap;
};






#endif