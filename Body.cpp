#include "Body.hpp"

CircleBody::CircleBody(float r, float x, float y, bool dynamic)
        : Body(C2_CIRCLE, dynamic)
{
        body.r = r;
        body.p.x = x;
        body.p.y = y;
}

void CircleBody::move(float x, float y)
{
        body.p.x += x;
        body.p.y += y;
}

void CircleBody::moveTo(float x, float y)
{
        body.p.x = x;
        body.p.y = y;
}

float CircleBody::getX()
{
        return body.p.x;
}

float CircleBody::getY()
{
        return body.p.y;
}

const void* CircleBody::get()
{
        return &body;
}

float CircleBody::getRadius()
{
        return body.r;
}


AabbBody::AabbBody(float w, float h, float x, float y, bool dynamic)
        : Body(C2_AABB, dynamic)
{
        body.min = c2V(x, y);
        body.max = c2V(x + w, y + h);
}

void AabbBody::move(float x, float y)
{
        body.min.x += x;
        body.min.y += y;
        body.max.x += x;
        body.max.y += y;
}

void AabbBody::moveTo(float x, float y)
{
        float w = body.max.x - body.min.x;
        float h = body.max.y - body.min.y;
        body.min = c2V(x, y);
        body.max = c2V(x + w, y + h);
}

float AabbBody::getX()
{
        return body.min.x;
}

float AabbBody::getY()
{
        return body.min.y;
}

const void* AabbBody::get()
{
        return &body;
}

float AabbBody::getWidth()
{
        return body.max.x - body.min.x;
}

float AabbBody::getHeight()
{
        return body.max.y - body.min.y;
}
