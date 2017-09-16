#include "Collider.hpp"

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


std::shared_ptr<CircleBody> Collider::createCircleBody(float r, float x,
                float y)
{
        auto body = std::make_shared<CircleBody>(r, x, y);

        bodies.push_back(body);
        return body;
}

std::shared_ptr<AabbBody> Collider::createAabbBody(float w, float h, float x,
                float y)
{
        auto body = std::make_shared<AabbBody>(w, h, x, y);

        bodies.push_back(body);
        return body;
}

void Collider::update()
{
        manifolds.clear();

        for (int i = 0; i < bodies.size(); ++i) {
                for (int j = i + 1; j < bodies.size(); ++j) {
                        auto a = bodies[i];
                        auto b = bodies[j];

                        c2Manifold manifold;
                        c2Collide(a->get(), nullptr, a->type,
                                        b->get(), nullptr, b->type,
                                        &manifold);

                        if (manifold.count > 0) {
                                manifolds.push_back(manifold);
                                solveCollision(a, b, manifold);
                        }
                }
        }
}

void Collider::solveCollision(std::shared_ptr<Body> a, std::shared_ptr<Body> b,
                const c2Manifold& manifold)
{
        c2v toMove = c2Mulvs(manifold.normal, manifold.depths[0]);

        if (a->dynamic && !b->dynamic) {
                a->move(-toMove.x, -toMove.y);
        } else if (!a->dynamic && b->dynamic) {
                b->move(toMove.x, toMove.y);
        }
}
