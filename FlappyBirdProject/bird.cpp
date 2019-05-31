#include "pch.h"
#include "bird.h"
#include <iostream>

Bird::Bird(const Point2d & startingPosition)
{
	m_position = startingPosition;
}

bool Bird::IsAlive(const LevelDescription & level)
{
	if (!IsInsideTheLevel(level)) {
		return false;
	}
	if (HasHitAPylon(level)) {
		return false;
	}
	return true;
}

void Bird::NextPosition(bool Jumped)
{
	if (Jumped) {
		m_position.Move({ HORIZONTAL_VELOCITY,JUMP_ACCELERATION });
	}
	else {
		m_position.Move({ HORIZONTAL_VELOCITY,-VERTICAL_ACCELERATION });
	}
}

bool Bird::IsInsideTheLevel(const LevelDescription & level)
{
	return (m_position.x > level.length || m_position.y <= 0 || m_position.y >= level.height) ? false : true;
}

bool Bird::HasHitAPylon(const LevelDescription & level)
{
	for (int i = 0;i < level.pylons.size();++i) {
		if (m_position.x >= level.pylons[i].GetLeftWall() && m_position.x <= level.pylons[i].GetRigthWall()) {
			if (m_position.y <= level.pylons[i].GetBottomWall() || m_position.y >= level.pylons[i].GetTopWall()) {
				/*
				std::cout << "\n";
				std::cout << "The x position is: " << m_position.x << " The y position is: " << m_position.y << "\n";
				std::cout << "The left wall is: " << level.pylons[i].GetLeftWall() << " The right wall is: " << level.pylons[i].GetRigthWall() << " \n";
				std::cout << "The bottom wall is: " << level.pylons[i].GetBottomWall() << " The top wall is: " << level.pylons[i].GetTopWall() << "\n";
				*/
				return true;
			}
		}
	}
	return false;
}

void Bird::PrintPosition() const
{
	std::cout << " \n Position is: (" << m_position.x << " , " << m_position.y << ") \n";
}
