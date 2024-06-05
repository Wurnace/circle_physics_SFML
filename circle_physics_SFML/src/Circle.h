#pragma once
#include "Vector.h"

#include <array>

const int MAX_CIRCLES = 10000;
const int WORLD_SIZE_X = 90000;
const int WORLD_SIZE_Y = 90000;

class Circle
{
public:
    Circle() {}
    Circle(Vector position, int radius)
        : Position(position), PositionOld(position), Radius(radius) {}
    Circle(Vector position, Vector velocity, int radius)
        : Position(position), PositionOld(position + velocity), Radius(radius) {}

    void Collision(Circle* allCircles, int numCircles, float dt);
    void Collision(Circle* other, float dt);
    void Update(Circle* allCircles, int numCircles, float dt);

public:
	Vector Position { 0, 0 };
	Vector PositionOld { 0, 0 };
	Vector Acceleration { 0, 0 };
    int Radius { 25 };
};

void CollisionNoSelf(Circle* allCircles, int numCircles, float dt, Vector source, int radius);
