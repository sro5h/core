#include "Player.hpp"

Player::Player(Collider& collider)
        : speed(1.5)
{
        body = std::make_shared<CircleBody>(16, 0, 0);
        body->dynamic = true;
        collider.registerBody(body);
}

void Player::update()
{
                handleInput();
}

void Player::draw(sf::RenderTarget& target)
{
        DebugDraw debug(target);
        debug.drawCircle(body->getRadius(),
                        body->getX(), body->getY(), sf::Color::Yellow);
}

void Player::handleInput()
{
        c2v toMove = c2V(0, 0);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                toMove.x = -1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                toMove.x = 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                toMove.y = -1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                toMove.y = 1;
        }

        if (toMove.x != 0 || toMove.y != 0) {
                toMove = c2Mulvs(c2Norm(toMove), speed);
                body->move(toMove.x, toMove.y);
        }
}
