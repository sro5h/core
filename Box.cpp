#include "Box.hpp"

Box::Box(Collider& collider, float x, float y)
{
        body = std::make_shared<AabbBody>(64, 64, x, y);
        collider.registerBody(body);
}

void Box::update() {}

void Box::draw(sf::RenderTarget& target)
{
        DebugDraw debug(target);
        debug.drawRect(body->getWidth(), body->getHeight(),
                        body->getX(), body->getY(), sf::Color::Red);
}
