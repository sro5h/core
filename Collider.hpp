#ifndef _COLLIDER_HPP
#define _COLLIDER_HPP

#include <memory>
#include <SFML/Graphics/RenderTarget.hpp>
#include "tinyc2.h"
#include "Tinyc2Debug.hpp"

class Body {
public:
        Body(bool dynamic) : dynamic(dynamic) {}
        virtual ~Body() {}

        virtual void move(float x, float y) = 0;
        virtual void moveTo(float x, float y) = 0;
        virtual float getX() = 0;
        virtual float getY() = 0;

        bool dynamic;
};

class CircleBody : public Body {
public:
        CircleBody(float r, float x, float y, bool dynamic = false)
                : Body(dynamic)
        {
                body.r = r;
                body.p.x = x;
                body.p.y = y;
        }

        void move(float x, float y)
        {
                body.p.x += x;
                body.p.y += y;
        }

        void moveTo(float x, float y)
        {
                body.p.x = x;
                body.p.y = y;
        }

        float getX()
        {
                return body.p.x;
        }

        float getY()
        {
                return body.p.y;
        }

        c2Circle body;
};


class Collider {
public:
        std::shared_ptr<CircleBody> createCircleBody(float r, float x, float y)
        {
                auto body = std::make_shared<CircleBody>(r, x, y);

                circleBodies.push_back(body);
                return body;
        }

        void update()
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

        void draw(sf::RenderTarget& target)
        {
                Tinyc2Debug debug(target);

                for (auto& ptr : circleBodies) {
                        debug.draw(ptr->body);
                }
        }

private:
        void solveCollision(std::shared_ptr<Body> a, std::shared_ptr<Body> b,
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

        std::vector<std::shared_ptr<CircleBody>> circleBodies;
        // For debug purposes
        std::vector<c2Manifold> manifolds;
};

#endif // _COLLIDER_HPP
