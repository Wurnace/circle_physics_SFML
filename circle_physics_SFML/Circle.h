#pragma once
#include "Vector.h"
#include <iostream>

int worldSizeX = 8000;
int worldSizeY = 8000;

class Circle
{
public:
	Vector pos { 0, 0 };
	Vector posold { 0, 0 };
	Vector acc { 0, 0 };
    int rad{ 25 };

    void Collision(Circle allCircles[], int numCircles, float dt)
    {
        for (int i = 0; i < numCircles; i++)
        {
            if (&allCircles[i] == this)
            {
                continue;
            }
            Vector axis = this->pos - allCircles[i].pos;
            float dist = axis.mag();
            float minDist = this->rad + allCircles[i].rad;
            if (dist <= minDist)
            {
                Vector n = axis / dist;
                const float delta = minDist - dist;
                this->pos += n * 0.5f * delta;
                allCircles[i].pos -= n * 0.5 * delta;
            }
        }
    }

    float clamp(float a, float mx, float mn)
    {
        if (a > mx)
        {
            return mx;
        }
        if (a < mn)
        {
            return mn;
        }
        return a;
    }

	void Update(Circle allCircles[], int numCircles, float dt)
	{
        acc += {0, 0.005};
		Vector vel = pos - posold;
        posold = pos;
		pos += vel + acc * dt * dt;
        acc = {0, 0};
        Collision(allCircles, numCircles, dt);
        Collision(allCircles, numCircles, dt);
        Collision(allCircles, numCircles, dt);
        Collision(allCircles, numCircles, dt);
        Collision(allCircles, numCircles, dt);
        Collision(allCircles, numCircles, dt);
        Collision(allCircles, numCircles, dt);
        Collision(allCircles, numCircles, dt);
        Collision(allCircles, numCircles, dt);
        Collision(allCircles, numCircles, dt);
        Collision(allCircles, numCircles, dt);
        Collision(allCircles, numCircles, dt);
        if (pos.x > worldSizeX - rad * 2.0f)
        {
            pos.x = worldSizeX - rad * 2.0f;
            acc.x = -0.05f;
        }
        else if (pos.x < rad / 4.0f)
        {
            pos.x = rad / 4.0f;
            acc.x = 0.05f;
        }

        if (pos.y > worldSizeY - rad * 2.0f)
        {
            pos.y = worldSizeY - rad * 2.0f;
            acc.y = -0.05f;
        }
        else if (pos.y < rad / 2.0f)
        {
            pos.y = rad / 2.0f;
            acc.y = 0.05f;
        }
	}
    Circle()
        : pos({ 0, 0 }), posold({ 0, 0 }), acc({ 0, 0 }), rad(25) {}
    Circle(Vector pos0, int rad)
        : pos(pos0), posold(pos0), acc({0, 0}), rad(rad) {}
    Circle(Vector pos0, Vector vel, int rad)
        : pos(pos0), posold(pos0 + vel), acc({ 0, 0 }), rad(rad) {}
};



void CollisionNoSelf(Circle allCircles[], int numCircles, float dt, Vector source, int rad)
{
    for (int i = 0; i < numCircles; i++)
    {
        Vector axis = source - allCircles[i].pos;
        float dist = axis.mag();
        float minDist = rad + allCircles[i].rad;
        if (dist <= minDist)
        {
            Vector n = axis / dist;
            const float delta = minDist - dist;
            source += n * 0.5f * delta;
            allCircles[i].pos -= n * 0.5 * delta;
        }
    }
}
