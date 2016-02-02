#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	_mapCamera = nullptr;
	_terrain = nullptr;
	_cameraPos = Vec3::ZERO;
	_cameraRotate = Vec3::ZERO;
	initAdujstPanel();
	initTerrain();
	initSprite3D();
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


void HelloWorld::initTerrain()
{
	if (_mapCamera && _terrain)
	{
		_mapCamera->removeFromParent();
		_terrain->removeFromParent();
		_mapCamera = nullptr;
		_terrain = nullptr;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	_mapCamera = Camera::createPerspective(60.0f, visibleSize.width / visibleSize.height, 0.1f, 1000.0f);
	_mapCamera->setCameraFlag(CameraFlag::USER1);
	_mapCamera->setPosition3D(_cameraPos);
	_mapCamera->setRotation3D(_cameraRotate);
	this->addChild(_mapCamera);
	Terrain::DetailMap r = Terrain::DetailMap("TerrainTest/Tx_FloorGrass01.jpg");
	Terrain::DetailMap g = Terrain::DetailMap("TerrainTest/Tx_FloorGrass02.jpg");
	Terrain::DetailMap b = Terrain::DetailMap("TerrainTest/Tx_FloorSand.jpg");
	Terrain::DetailMap a = Terrain::DetailMap("TerrainTest/Tx_FloorStone01.jpg");

	Terrain::TerrainData data = Terrain::TerrainData("TerrainTest/heightmap_u3d.jpg", "TerrainTest/Tx_FloorGrass01.jpg", Size(32, 32), _height, 513.0f / 513.0f * _scale);
	_terrain = Terrain::create(data,Terrain::CrackFixedType::INCREASE_LOWER);
	_terrain->setPosition3D(Vec3::ZERO);
	_terrain->setDrawWire(false);
	this->addChild(_terrain);
	_terrain->setCameraMask(2);
	_terrain->setLODDistance(100000, 100, 500);
	_terrain->setMaxDetailMapAmount(1);

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	auto touchlistener = EventListenerTouchOneByOne::create();
	touchlistener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	touchlistener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchlistener, this);
	this->schedule(schedule_selector(HelloWorld::updateCamera), 0.1f);
}

void HelloWorld::updateCamera(float dt)
{
	Vec3 pos = _mapCamera->getPosition3D();

	Vec3 forward, up, left;
	_mapCamera->getNodeToWorldTransform().getForwardVector(&forward);
	_mapCamera->getNodeToWorldTransform().getUpVector(&up);
	_mapCamera->getNodeToWorldTransform().getLeftVector(&left);

	Vec3 d = (-_x * left + _y * up - _z * forward) * _scale * 10;

	pos.y += d.y;
	pos.z += d.z;
	//pos += (-_x * left + _y * up - _z * forward) * _scale * 10;
	_mapCamera->setPosition3D(pos);
	_cameraPos = pos;
}

void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* unused_event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_W)
	{
		_z = -_per;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_S)
	{
		_z = _per;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_A)
	{
		_x = -_per;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_D)
	{
		_x = _per;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
	{
		_y = _per;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{
		_y = -_per;
	}
}

void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* unused_event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_W)
	{
		_z = 0.0f;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_S)
	{
		_z = 0.0f;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_A)
	{
		_x = 0.0f;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_D)
	{
		_x = 0.0f;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
	{
		_y = 0.0f;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{
		_y = 0.0f;
	}
}

void HelloWorld::onTouchMoved(Touch* touch, Event* evt)
{
	Point pre = touch->getPreviousLocation();
	Point now = touch->getLocation();

	Point dir = now - pre;

	Vec3 rotate = _mapCamera->getRotation3D();
	rotate.x += dir.y;
	rotate.y += dir.x;
	_mapCamera->setRotation3D(rotate);
	_cameraRotate = rotate;
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* evt)
{
	return true;
}

void HelloWorld::initAdujstPanel()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point originPostion = Director::getInstance()->getVisibleOrigin();
	Button* addHeightBtn = Button::create("button.png");
	addHeightBtn->setTag(1);
	addHeightBtn->setTitleText("+Height");
	addHeightBtn->setTitleFontSize(20);
	addHeightBtn->setPosition(Point(visibleSize.width - 100, 100) + originPostion);
	addHeightBtn->addTouchEventListener(CC_CALLBACK_2(HelloWorld::adjustHeightButtonTouchEvent, this));
	this->addChild(addHeightBtn);
	Button* deleightBtn = Button::create("button.png");
	deleightBtn->setTag(2);
	deleightBtn->setTitleText("-Height");
	deleightBtn->setTitleFontSize(20);
	deleightBtn->setPosition(Point(visibleSize.width - 100, 30) + originPostion);
	deleightBtn->addTouchEventListener(CC_CALLBACK_2(HelloWorld::adjustHeightButtonTouchEvent, this));
	this->addChild(deleightBtn);
}

void HelloWorld::adjustHeightButtonTouchEvent(Ref* ref, Widget::TouchEventType eventType)
{
	if (eventType == Widget::TouchEventType::ENDED)
	{

		Node* node = dynamic_cast<Node*>(ref);
		if (node)
		{
			int tag = node->getTag();
			if (tag == 1)
			{
				_height += 1.0f;
			}
			else
			{
				_height -= 1.0f;
			}

			initTerrain();
		}

	}
}


void HelloWorld::initSprite3D()
{
	std::string fileName = "Sprite3DTest/Swordman_No_Animation.c3b";
	std::string AnimName = "Sprite3DTest/Swordman_Animation.c3b";
	_sprite = Sprite3D::create(fileName);
	_sprite->setScale(5);
	_sprite->setRotation3D(Vec3(0, 270, 0));
	addChild(_sprite);
	_sprite->setPosition(Point(400,240));

	auto animation = Animation3D::create(AnimName);
	if (animation)
	{
		auto animate = Animate3D::create(animation);
		_sprite->runAction(RepeatForever::create(animate));
	}


	std::string fileName2 = "Sprite3DTest/Swordman_No_Animation.c3b";
	std::string AnimName2 = "Sprite3DTest/Swordman_Animation.c3b";
	auto _sprite2 = Sprite3D::create(fileName2);
	_sprite2->setScale(1);
	_sprite2->setRotation3D(Vec3(0, 0, 0));
	addChild(_sprite2);
	_sprite2->setPosition3D(Vec3::ZERO);
	_sprite2->setCameraMask(2);
	auto animation2 = Animation3D::create(AnimName2);
	if (animation2)
	{
		auto animate = Animate3D::createWithFrames(animation2,200,224);
		_sprite2->runAction(RepeatForever::create(animate));
	}

	_mapCamera->setPosition3D(Vec3(0,100,100));
	_mapCamera->setRotation3D(Vec3(-45,0,0));
}
