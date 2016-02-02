#ifndef __GAMEGLOBAL_H__
#define __GAMEGLOBAL_H__

#include "CocosHead.h"


typedef std::function<void(Ref*)> GameEventCallback1;

static Size designSize = Size(800, 480);

extern float map_grid_width;

extern float map_grid_height;

extern float g_frameRate;

// zorder
enum class Zorder
{
	order_map = 1,
	order_grid = 10,
	order_effect = 20,
	order_obj = 100,
	order_ui = 500,
};


// 8方向
enum class ActDir
{
	DIR_UP = 0,
	DIR_UPRIGHT = 1,
	DIR_RIGHT = 2,
	DIR_DOWNRIGHT = 3,
	DIR_DOWN = 4,
	DIR_LEFTDOWN = 5,
	DIR_LEFT = 6,
	DIR_LEFTUP = 7
};

static bool IsWeaponFirst[8] =
{
	true,
	true,
	true,
	true,
	false,
	false,
	false,
	false
};


static float MOVETIME[8] =
{
	1.0f,
	1.414f,
	1.0f,
	1.414f,
	1.0f,
	1.414f,
	1.0f,
	1.414f
};


// 动作定义 
enum class ActMotion
{
	stand = 0,
	walk = 1,
	hit = 2,
	bighit = 3,
	magic = 4,
	die = 5,
	nil = 6,
};

enum class ObjectType
{
	nil			= 0,
	mainplayer	= 1,
	otherplayer = 2,
	monster		= 3,
	npc			= 4,
};

enum class Job
{
	zhanshi = 1,
	fashi	= 2,
	daoshi	= 3,
};

// 获取下个地点
static Point getNextPostion(Point pos, ActDir dir, int distance = 1)
{
	Point next = pos;
	switch (dir)
	{
	case ActDir::DIR_UP:
		next = pos + Point(0, -distance);
		break;
	case ActDir::DIR_UPRIGHT:
		next = pos + Point(distance, -distance);
		break;
	case ActDir::DIR_RIGHT:
		next = pos + Point(distance, 0);
		break;
	case ActDir::DIR_DOWNRIGHT:
		next = pos + Point(distance, distance);
		break;
	case ActDir::DIR_DOWN:
		next = pos + Point(0, distance);
		break;
	case ActDir::DIR_LEFTDOWN:
		next = pos + Point(-distance, distance);
		break;
	case ActDir::DIR_LEFT:
		next = pos + Point(-distance, 0);
		break;
	case ActDir::DIR_LEFTUP:
		next = pos + Point(-distance, -distance);
		break;
	default:
		break;
	}
	return next;
}

static ActDir getDirByAngle(float angle)
{
	ActDir dir = ActDir::DIR_DOWN;
	if (angle >= 0.0 && angle <= 22.5 || angle > 337.5 && angle <= 360.0 )
	{
		dir = ActDir::DIR_RIGHT;
	} 
	else if (angle > 22.5 && angle <= 67.5)
	{
		dir = ActDir::DIR_UPRIGHT;
	}
	else if (angle > 67.5 && angle <= 112.5)
	{
		dir = ActDir::DIR_UP;
	}
	else if (angle > 112.5 && angle <= 157.5)
	{
		dir = ActDir::DIR_LEFTUP;
	}
	else if (angle > 157.5 && angle <= 202.5)
	{
		dir = ActDir::DIR_LEFT;
	}
	else if (angle > 202.5 && angle <= 247.5)
	{
		dir = ActDir::DIR_LEFTDOWN;
	}
	else if (angle > 247.5 && angle <= 292.5)
	{
		dir = ActDir::DIR_DOWN;
	}
	else if (angle > 292.5 && angle <= 337.5)
	{
		dir = ActDir::DIR_DOWNRIGHT;
	}
	return dir;
}



static ActDir getDirByPoint(Point src,Point next)
{
	Point d_pos = next - src;
	float rotation = d_pos.getAngle();

	rotation = rotation * 180.0f / 3.14f;
	rotation = (rotation < 0 ? rotation + 360 : rotation);
	return getDirByAngle(rotation);
}


static float getDir3DYByPoint(Point src, Point next)
{
	Point d_pos = next - src;
	float rotation = d_pos.getAngle();
	rotation = rotation * 180.0f / 3.14f + 90.f;
	rotation = (rotation < 0 ? rotation + 360 : rotation);
	return rotation;
}


static int get16DirByAngle(float angle)
{
	int dir = 0;
	for (int i = 1; i < 16; ++i)
	{
		if (angle > 11.25 + (i - 1) * 22.5 && angle <= 11.25 + i * 22.5)
		{
			dir = i;
			break;
		}
	}
	return dir;
}


static Point getRandomPointInRect(Rect rect)
{
	int x = RandomHelper::random_int((int)rect.getMinX(),(int) rect.getMaxX());
	int y = RandomHelper::random_int((int)rect.getMinY(), (int)rect.getMaxY());

	return Point(x, y);
}


static Point converVec3ToPoint(Vec3 vec3)
{
	return Point(vec3.x, -vec3.z);
}


static Vec3 converPointToVec3(Point point)
{
	return Vec3(point.x, 0.0f, -point.y);
}

#endif