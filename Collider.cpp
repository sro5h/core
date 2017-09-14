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


std::shared_ptr<CircleBody> Collider::createCircleBody(float r, float x,
                float y)
{
        auto body = std::make_shared<CircleBody>(r, x, y);

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
        if (a->dynamic && !b->dynamic) {
                a->move(-manifold.normal.x * manifold.depths[0],
                                -manifold.normal.y * manifold.depths[0]);
        } else if (!a->dynamic && b->dynamic) {
                b->move(+manifold.normal.x * manifold.depths[0],
                                +manifold.normal.y * manifold.depths[0]);
        }
}
