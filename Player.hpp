#ifndef _PLAYER_HPP
#define _PLAYER_HPP

#include "Entity.hpp"
#include "Collider.hpp"
#include "DebugDraw.hpp"

class Player : public Entity {
public:
        Player(Collider& collider);

        void update();
        void draw(sf::RenderTarget& target);

private:
        void handleInput();

        std::shared_ptr<CircleBody> body;
        const float speed;
};

#endif // _PLAYER_HPP
