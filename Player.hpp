#ifndef _PLAYER_HPP
#define _PLAYER_HPP

#include "Entity.hpp"
#include "Collider.hpp"
#include "DebugDraw.hpp"

class Player : public Entity {
public:
        Player(Collider& collider)
                : speed(1.3)
        {
                body = collider.createCircleBody(16, 0, 0);
                body->dynamic = true;
        }

        void update()
        {
                handleInput();
        }

        void draw(sf::RenderTarget& target)
        {
                DebugDraw debug(target);
                debug.drawCircle(body->getRadius(),
                                body->getX(), body->getY(), sf::Color::Blue);
        }

private:
        void handleInput()
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

        std::shared_ptr<CircleBody> body;
        const float speed;
};

#endif // _PLAYER_HPP
