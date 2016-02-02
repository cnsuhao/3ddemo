#include "UIWorldMap.h"
#include "GameScene.h"
#include "UIManager.h"
#include "GameMap.h"
#include "GameAI.h"
#include "GamePlayer.h"
#include "ObjectDataMgr.h"
#include "UIEffectMgr.h"
#pragma execution_character_set("utf-8")

UIWorldMap::UIWorldMap() :UIBaseNode()
, _mapScrollView(nullptr)
, _mapNameText(nullptr)
, _tileMap(nullptr)
, _selfIcon(nullptr)
, _desIcon(nullptr)
, _drawNode(nullptr)
, _touchPanel(nullptr)
{

}

UIWorldMap::~UIWorldMap()
{

}

bool UIWorldMap::init()
{
	this->setInitCsbFunc(CC_CALLBACK_0(UIWorldMap::loadCsbFunc, this));
	_csbPlist.push_back("ui/worldmap/worldmap0.plist");
	// 刷新主角位置事件
	GameDispatcher::getInstance()->addGameEventListener(int(GameEventId::began_changemypos), CC_CALLBACK_2(UIWorldMap::onUpdateMyPosEvent, this), this);
	return true;
}

void UIWorldMap::onClickCloseBtnEvent(Ref* pSender)
{
	this->hide();
}



void UIWorldMap::loadCsbFunc()
{
	auto csbRoot = dynamic_cast<Layout*>(GUIReader::getInstance()->widgetFromBinaryFile("ui/worldmap/worldmap.csb"));
	if (!csbRoot)
	{
		return ;
	}
	this->setCsbRoot(csbRoot);
	_csbFrame = dynamic_cast<Widget*>(Helper::seekWidgetByName(_csbRoot, "frame"));
	_mapScrollView = dynamic_cast<ui::ScrollView*>(Helper::seekWidgetByName(_csbRoot, "scrollview_map"));
	_mapNameText = dynamic_cast<Text*>(Helper::seekWidgetByName(_csbRoot, "text_mapname"));
	_touchPanel = dynamic_cast<Layout*>(_mapScrollView->getChildByName("touchpanel"));
	_mapScrollView->setClippingEnabled(true);
	_touchPanel->addTouchEventListener(CC_CALLBACK_2(UIWorldMap::onClickMapBtnEvent, this));
	Button* btnClose = dynamic_cast<Button*>(Helper::seekWidgetByName(_csbRoot, "btn_close"));
	if (btnClose)
	{
		btnClose->addClickEventListener(CC_CALLBACK_1(UIWorldMap::onClickCloseBtnEvent, this));
	}
	this->addChild(_csbRoot);
	this->setLocalZOrder((int)UIZorder::order_mainfront);
}

void UIWorldMap::show()
{
	UIBaseNode::show();
	// 加载地图
	initMapContent();
	// 校准位置
	adjustSelfIconPosition();
}

void UIWorldMap::hide()
{
	UIBaseNode::hide();
	// 清理地图
	clearMapContent();
}

void UIWorldMap::initMapContent()
{
	do
	{
		ObjectData* maindata = ObjectDataMgr::getInstance()->getMainObjectData();
		CC_BREAK_IF(maindata == nullptr);
		_tileMap = experimental::TMXTiledMap::create(StringUtils::format("map/%s.tmx", maindata->m_mapId.c_str()));
		CC_BREAK_IF(_tileMap == nullptr);
		_mapScrollView->addChild(_tileMap);
		_tileMap->setScale(_mapScale);
		_tileMap->setPosition(Point::ZERO);
		auto innerContainer = _mapScrollView->getInnerContainer();
		if (innerContainer)
		{
			innerContainer->setContentSize(_tileMap->getContentSize() * _mapScale);
			_touchPanel->setPosition(Point::ZERO);
			_touchPanel->setContentSize(_tileMap->getContentSize() * _mapScale);
		}
		if (_mapScrollView)
		{
			Point pt = _mapScrollView->convertToWorldSpace(Point::ZERO);
			Size scrollSize = _mapScrollView->getContentSize();
			_tileMap->setShowRect(Rect(pt.x, pt.y, scrollSize.width, scrollSize.height));
		}
		// 主角图标位置
		_drawNode = DrawNode::create();
		_touchPanel->addChild(_drawNode);
		_desIcon = ImageView::create("icon/des.png");
		_desIcon->setAnchorPoint(Point::ZERO);
		_desIcon->setVisible(false);
		_touchPanel->addChild(_desIcon);
		_selfIcon = ImageView::create("icon/role_1.png");
		_selfIcon->ignoreContentAdaptWithSize(false);
		_selfIcon->setContentSize(Size(30,30));
		_touchPanel->addChild(_selfIcon);
		_touchPanel->setLocalZOrder(10);
		auto _alphaLayer = _tileMap->getLayer("alpha");
		if (_alphaLayer)
		{
			_alphaLayer->setVisible(false);
		}
		auto _blockLayer = _tileMap->getLayer("block");
		if (_blockLayer)
		{
			_blockLayer->setVisible(false);
		}
		// 传送门
		auto triggerGroup = _tileMap->getObjectGroup("trigger");
		if (triggerGroup)
		{
			auto vec = triggerGroup->getObjects();
			for (int i = 0; i < vec.size(); ++i)
			{
				ValueMap prop = vec[i].asValueMap();
				int x = prop["x"].asInt();
				int y = prop["y"].asInt();
				int w = prop["width"].asInt();
				int h = prop["height"].asInt();

				UIEffectMgr::getInstance()->playEffect("chuansongmen", _touchPanel, Point(x + w / 2 , y + h / 2) * _mapScale, true, _mapScale);
			}

		}

	} while (0);
}


void UIWorldMap::clearMapContent()
{
	if (_tileMap && _selfIcon)
	{
		_touchPanel->removeAllChildrenWithCleanup(true);
		_tileMap->removeFromParentAndCleanup(true);
		_tileMap = nullptr;
		_selfIcon = nullptr;
		_drawNode = nullptr;
		_points.clear();
	}
}

void UIWorldMap::adjustSelfIconPosition()
{
	if (_selfIcon)
	{
		ObjectData* maindata = ObjectDataMgr::getInstance()->getMainObjectData();
		if (maindata)
		{
			Point selfPos = convertTilePosToNodePos(maindata->getTileMapPos());
			_selfIcon->setPosition(selfPos);
			// 校准位置
			Size scrollSize = _mapScrollView->getContentSize();
			Point centerPos = Point(scrollSize.width / 2, scrollSize.height / 2);
			Layout* innerContainer = _mapScrollView->getInnerContainer();
			Size innerSize = innerContainer->getContentSize();
			Point adjustPos = centerPos -  selfPos;
			if (adjustPos.x > 0)
			{
				adjustPos.x = 0;
			}
			if (adjustPos.x < scrollSize.width - innerSize.width)
			{
				adjustPos.x = scrollSize.width - innerSize.width;
			}
			if (adjustPos.y > 0)
			{
				adjustPos.y = 0;
			}
			if (adjustPos.y < scrollSize.height - innerSize.height)
			{
				adjustPos.y = scrollSize.height - innerSize.height;
			}
			innerContainer->setPosition(adjustPos);
		}

	}
}

void UIWorldMap::onClickMapBtnEvent(Ref* pSender, Widget::TouchEventType touchType)
{
	if (touchType == Widget::TouchEventType::ENDED)
	{
		Point touchPos = _touchPanel->getTouchEndPosition();
		Point nodePos = _touchPanel->convertToNodeSpace(touchPos);
		Point tilePos = convertNodePosToTilePos(nodePos);
		GamePlayer* mainPlayer = GameObjectMgr::getInstance()->getMainGamePlayer();
		if (GameMap::getInstance()->canMove(tilePos.x, tilePos.y))
		{
			mainPlayer->getDoSkill()->setIsAutoFight(false);
			mainPlayer->moveTo(tilePos);
		}
	}
}

void UIWorldMap::onUpdateMyPosEvent(Ref* pSender, GameEvent* gEvent)
{
	if (isVisible())
	{
		// 绘制
		drawPath();
	}
}

void UIWorldMap::setPathNode(ptr_PathNode node)
{
	// 清理路径
	_points.clear();
	// 跳过第一个点
	node = node->next;
	while (node)
	{
		_points.push_back(convertTilePosToNodePos(Point(node->m_x, node->m_y)));
		if (node->next == nullptr)
		{
			_desIcon->setVisible(true);
			_desIcon->setPosition(convertTilePosToNodePos(Point(node->m_x, node->m_y)));
		}
		node = node->next;
	}
}

void UIWorldMap::drawPath()
{
	ObjectData* maindata = ObjectDataMgr::getInstance()->getMainObjectData();
	GamePlayer* mainPlayer = GameObjectMgr::getInstance()->getMainGamePlayer();
	if (_selfIcon && maindata && mainPlayer)
	{
		Point endPos = convertTilePosToNodePos(mainPlayer->getTilePos());
		float moveTime = MOVETIME[(int)mainPlayer->getDir()] * 0.48f;

		MoveTo* moveTo = MoveTo::create(moveTime, endPos);
		CallFuncN* callEnd = CallFuncN::create(
			[=](Node*){

			if (_points.empty() == false)
			{
				_points.erase(_points.begin());
			}

			if (_points.empty())
			{
				_desIcon->setVisible(false);
			}
			else
			{
				_drawNode->clear();
				_drawNode->drawPoly(&_points[0], _points.size(), false, Color4F::RED);
			}
		}
		);
		_selfIcon->runAction(Sequence::create(moveTo, callEnd, nullptr));
	}
	if (_drawNode && _points.empty() == false)
	{
		_drawNode->clear();
		_drawNode->drawPoly(&_points[0], _points.size(), false, Color4F::RED);
	}
}

cocos2d::Point UIWorldMap::convertTilePosToNodePos(Point pt)
{
	Size mapSize = GameMap::getInstance()->getMapSize();
	float x = map_grid_width * _mapScale * (pt.x + 0.5f);
	float y = map_grid_height* _mapScale * (mapSize.height - pt.y - 0.5f);

	return Point(x, y);
}

cocos2d::Point UIWorldMap::convertNodePosToTilePos(Point pt)
{
	Size mapSize = GameMap::getInstance()->getMapSize();
	float x = pt.x / (map_grid_width * _mapScale);
	float y = mapSize.height - ceil(pt.y / (map_grid_height * _mapScale));

	return Point(x, y);
}

