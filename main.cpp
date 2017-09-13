#include <SFML/Graphics.hpp>
#define TINYC2_IMPL
#include "tinyc2.h"

#define MC_PER_TICK 15625

class Player : public sf::Drawable {
        const float speed = 1;

        sf::CircleShape shape;

public:
        Player()
        {
                shape = sf::CircleShape(16);
                shape.setOrigin(16, 16);
                body.p.x = 0;
                body.p.y = 0;
                body.r = 16;
        }

        void update()
        {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                        body.p.x -= speed;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                        body.p.x += speed;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                        body.p.y -= speed;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                        body.p.y += speed;
                }
        }

        virtual void draw(sf::RenderTarget& target,
                        sf::RenderStates states) const
        {
                sf::Transform translation;
                translation.translate(body.p.x, body.p.y);
                states.transform = translation;

                target.draw(shape, states);
        }

        c2Circle body;
};

class Obstacle : public sf::Drawable {
        sf::RectangleShape shape;

public:
        Obstacle(int width, int height, float x, float y)
        {
                shape = sf::RectangleShape(sf::Vector2f(width, height));
                body.min.x = x;
                body.min.y = y;
                body.max.x = x + width;
                body.max.y = y + height;
        }

        virtual void draw(sf::RenderTarget& target,
                        sf::RenderStates states) const
        {
                sf::Transform translation;
                translation.translate(body.min.x, body.min.y);
                states.transform = translation;

                target.draw(shape, states);
        }

        c2AABB body;
};

int main(int argc, char* argv[])
{
        sf::ContextSettings settings;
        settings.antialiasingLevel = 8;

        sf::RenderWindow window(sf::VideoMode(500, 500), "App", sf::Style::Default, settings);

        Player player;
        Obstacle obstacle(100, 30, 0, 200);

        // Timing stuff
        sf::Clock clock;
        int previous = 0;
        int lag = 0;

        while (window.isOpen()) {
                int current = clock.getElapsedTime().asMicroseconds();
                int elapsed = current - previous;
                previous = current;
                lag += elapsed;

                sf::Event event;

                while (window.pollEvent(event)) {
                        if (event.type == sf::Event::Closed) {
                                window.close();
                        }
                }

                while (lag >= MC_PER_TICK) {
                        player.update();

                        // Check for collision
                        c2Manifold manifold;
                        c2CircletoAABBManifold(player.body, obstacle.body,
                                        &manifold);

                        if (manifold.count > 0) {
                                player.body.p.x -= manifold.normal.x * manifold.depths[0];
                                player.body.p.y -= manifold.normal.y * manifold.depths[0];
                        }

                        lag -= MC_PER_TICK;
                }

                sf::View view = window.getDefaultView();
                view.setCenter(0, 0);
                window.setView(view);

                window.clear(sf::Color(30, 30, 30));
                window.draw(player);
                window.draw(obstacle);
                window.display();
        }

        return 0;
}
