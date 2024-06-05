#include "Circle.h"
#include <iostream>

// This Macro is for whether Circle::Collision applies a force to the other circle colliding
#define CollisionStep2 true

// CIRCLE CODE
void Circle::Collision(Circle* allCircles, int numCircles, float dt)
{
    for (int i = 0; i < numCircles; i++)
    {
        if (&allCircles[i] == this)
            continue;

        Vector axis = this->Position - allCircles[i].Position;
        float distSq = axis.magSq();
        int minDistSq = (this->Radius + allCircles[i].Radius);
        minDistSq *= minDistSq;
        if (distSq <= minDistSq && distSq > 0)
        {
            Vector n = axis / distSq;
            const float delta = 0.05f * (minDistSq - distSq);
            this->Position += n * delta;

#if CollisionStep2
            allCircles[i].Position -= n * delta;
#endif
        }
    }
}
void Circle::Collision(Circle* other, float dt)
{
    if (other == this)
        return;

    Vector axis = this->Position - other->Position;
    float distSq = axis.magSq();
    int minDistSq = (this->Radius + other->Radius);
    minDistSq *= minDistSq;
    if (distSq <= minDistSq && distSq > 0)
    {
        Vector n = axis / distSq;
        const float delta = 0.05f * (minDistSq - distSq);
        this->Position += n * delta;
        other->Position -= n * delta;
    }
}

void Circle::Update(Circle* allCircles, int numCircles, float dt)
{
    Acceleration.y += 0.005f;

    Vector vel = Position - PositionOld;
    PositionOld = Position;
    Position += vel + Acceleration * dt * dt;
    Acceleration.set(0, 0);

    //for (int i = 0; i < 10; i++)
    //    Collision(allCircles, numCircles, dt);

    if (Position.x > WORLD_SIZE_X - Radius * 2.0f)
    {
        Position.x = WORLD_SIZE_X - Radius * 2.0f;
        //Acceleration.x = -0.05f;
    }
    else if (Position.x < Radius / 4.0f)
    {
        Position.x = Radius / 4.0f;
        //Acceleration.x = 0.05f;
    }

    if (Position.y > WORLD_SIZE_Y - Radius * 2.0f)
    {
        Position.y = WORLD_SIZE_Y - Radius * 2.0f;
        //Acceleration.y = -0.05f;
    }
    else if (Position.y < Radius / 2.0f)
    {
        Position.y = Radius / 2.0f;
        //Acceleration.y = 0.05f;
    }
}

void CollisionNoSelf(Circle* allCircles, int numCircles, float dt, Vector source, int radius)
{
    for (int i = 0; i < numCircles; i++)
    {
        Vector axis = source - allCircles[i].Position;
        float distSq = axis.magSq();
        int minDist = radius + allCircles[i].Radius;
        minDist *= minDist;
        if (distSq <= minDist && distSq > 0)
            allCircles[i].Position -= (axis / distSq) * (0.03f * (minDist - distSq));
    }
}
