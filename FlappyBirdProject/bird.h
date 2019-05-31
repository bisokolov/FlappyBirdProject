#pragma once
#include "pch.h"
#include "flappy.h"


class Bird {
public:
	Bird(const Point2d & startingPosition);
	bool IsAlive(const LevelDescription& level);
	void NextPosition(bool Jumped);
	bool IsInsideTheLevel(const LevelDescription& level);
	bool HasHitAPylon(const LevelDescription& level);
	void PrintPosition() const;
private:
	Point2d m_position;
};