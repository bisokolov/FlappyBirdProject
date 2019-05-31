#include "pch.h"
#include "flappy.h"

void Point2d::Move(const Point2d & deltaPos)
{
	x += deltaPos.x;
	y += deltaPos.y;
}

float LevelDescription::Pylon::GetLeftWall() const
{
	return center.x - width / 2;
}

float LevelDescription::Pylon::GetRigthWall() const
{
	return center.x + width / 2;
}

float LevelDescription::Pylon::GetBottomWall() const
{
	return center.y - gapHeight / 2;
}

float LevelDescription::Pylon::GetTopWall() const
{
	return center.y + gapHeight / 2;
}
