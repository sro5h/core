#ifndef _COLLIDER_HPP
#define _COLLIDER_HPP

#include <memory>
#include <SFML/Graphics/RenderTarget.hpp>
#include "tinyc2.h"
#include "Tinyc2Debug.hpp"

class Body {
public:
        virtual void move(float x, float y) = 0;
        virtual void moveTo(float x, float y) = 0;
        virtual float getX() = 0;
        virtual float getY() = 0;
};

class CircleBody : public Body {
public:
        CircleBody(float r, float x, float y)
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

        void draw(sf::RenderTarget& target)
        {
                Tinyc2Debug debug(target);

                for (auto& ptr : circleBodies) {
                        debug.draw(ptr->body);
                }
        }

private:
        std::vector<std::shared_ptr<CircleBody>> circleBodies;
};

#endif // _COLLIDER_HPP
