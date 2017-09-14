#include "Collider.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include "Tinyc2Debug.hpp"

CircleBody::CircleBody(float r, float x, float y, bool dynamic)
        : Body(dynamic)
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


std::shared_ptr<CircleBody> Collider::createCircleBody(float r, float x,
                float y)
{
        auto body = std::make_shared<CircleBody>(r, x, y);

        circleBodies.push_back(body);
        return body;
}

void Collider::update()
{
        manifolds.clear();

        for (int i = 0; i < circleBodies.size(); ++i) {
                for (int j = i + 1; j < circleBodies.size(); ++j) {
                        auto a = circleBodies[i];
                        auto b = circleBodies[j];

                        c2Manifold manifold;
                        c2CircletoCircleManifold(a->body, b->body,
                                        &manifold);

                        if (manifold.count > 0) {
                                manifolds.push_back(manifold);
                                solveCollision(a, b, manifold);
                        }
                }
        }
}

void Collider::draw(sf::RenderTarget& target)
{
        Tinyc2Debug debug(target);

        for (auto& ptr : circleBodies) {
                debug.draw(ptr->body);
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
