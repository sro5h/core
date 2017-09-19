#ifndef _BOX_HPP
#define _BOX_HPP

#include "Entity.hpp"
#include "Collider.hpp"
#include "DebugDraw.hpp"

class Box : public Entity {
public:
        Box(Collider& collider, float x, float y);

        void update();
        void draw(sf::RenderTarget& target);

private:
        std::shared_ptr<AabbBody> body;
};

#endif // _BOX_HPP
