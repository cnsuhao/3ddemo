#ifndef UIWorldMap_h__
#define UIWorldMap_h__

#include "UIBaseNode.h"
#include "GameObjectMgr.h"
#include "FindPath.h"
class UIWorldMap :public UIBaseNode
{
public:

	UIWorldMap();

	~UIWorldMap();

	bool init();

	CREATE_FUNC(UIWorldMap);

	void onClickMapBtnEvent(Ref* pSender, Widget::TouchEventType touchType);

	void onClickCloseBtnEvent(Ref* pSender);

	void loadCsbFunc();

	virtual void show();

	virtual void hide();

	void initMapContent();

	void clearMapContent();

	void adjustSelfIconPosition();

	void onUpdateMyPosEvent(Ref* pSender, GameEvent* gEvent);

	void setPathNode(ptr_PathNode node);

	void drawPath();

	Point convertTilePosToNodePos(Point pt);

	Point convertNodePosToTilePos(Point pt);
private:
	const float _mapScale = 0.25f;
	const  int _tileMapTag = 100;
	ui::ScrollView* _mapScrollView;
	Layout*		_touchPanel;
	Text*		_mapNameText;
	ImageView*  _selfIcon;
	ImageView*  _desIcon;
	vector<Point> _points;
	DrawNode*	_drawNode;
	experimental::TMXTiledMap* _tileMap;
};
#endif // UIWorldMap_h__

