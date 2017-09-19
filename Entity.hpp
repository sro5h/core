#ifndef _ENTITY_HPP
#define _ENTITY_HPP

#include <SFML/Graphics/RenderTarget.hpp>

class Entity {
public:
        virtual ~Entity() {}

        virtual void update() = 0;
        virtual void draw(sf::RenderTarget& target) = 0;
};

#endif // _ENTITY_HPP
