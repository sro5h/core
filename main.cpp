#include <SFML/Graphics.hpp>
#define TINYC2_IMPL
#include "tinyc2.h"

#define MC_PER_TICK 15625

class Player : public sf::Drawable {
        const float speed = 1;

        sf::CircleShape shape;
        float x = 0;
        float y = 0;

public:
        Player()
        {
                shape = sf::CircleShape(16);
                shape.setOrigin(16, 16);
        }

        void update()
        {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                        x -= speed;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                        x += speed;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                        y -= speed;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                        y += speed;
                }
        }

        virtual void draw(sf::RenderTarget& target,
                        sf::RenderStates states) const
        {
                sf::Transform translation;
                translation.translate(x, y);
                states.transform = translation;

                target.draw(shape, states);
        }
};

int main(int argc, char* argv[])
{
        sf::ContextSettings settings;
        settings.antialiasingLevel = 8;

        sf::RenderWindow window(sf::VideoMode(500, 500), "App", sf::Style::Default, settings);

        Player player;

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

                        lag -= MC_PER_TICK;
                }

                sf::View view = window.getDefaultView();
                view.setCenter(0, 0);
                window.setView(view);

                window.clear(sf::Color(30, 30, 30));
                window.draw(player);
                window.display();
        }

        return 0;
}
