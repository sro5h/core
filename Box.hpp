#ifndef _BOX_HPP
#define _BOX_HPP

#include "Entity.hpp"
#include "Collider.hpp"
#include "DebugDraw.hpp"

class Box : public Entity {
public:
        Box(Collider& collider, float x, float y)
        {
                body = collider.createAabbBody(64, 64, x, y);
        }

        void update()
        {
        }

        void draw(sf::RenderTarget& target)
        {
                DebugDraw debug(target);
                debug.drawRect(body->getWidth(), body->getHeight(),
                                body->getX(), body->getY(), sf::Color::White);
        }

private:
        std::shared_ptr<AabbBody> body;
};

#endif // _BOX_HPP
