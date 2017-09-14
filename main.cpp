#include <SFML/Graphics.hpp>
#define TINYC2_IMPL
#include "tinyc2.h"
#undef TINYC2_IMPL
#include "Collider.hpp"

#define MC_PER_TICK 15625

void processInput(std::shared_ptr<Body> body);

int main(int argc, char* argv[])
{
        sf::ContextSettings settings;
        settings.antialiasingLevel = 8;

        sf::RenderWindow window(sf::VideoMode(500, 500), "App", sf::Style::Default, settings);

        Collider collider;

        std::shared_ptr<Body> staticBody = collider.createCircleBody(64, 100, 100);
        std::shared_ptr<Body> movingBody = collider.createCircleBody(16, 0, 0);

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
                        processInput(movingBody);

                        lag -= MC_PER_TICK;
                }

                sf::View view = window.getDefaultView();
                view.setCenter(0, 0);
                window.setView(view);

                window.clear(sf::Color(30, 30, 30));
                collider.draw(window);
                window.display();
        }

        return 0;
}

void processInput(std::shared_ptr<Body> body)
{
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                body->move(-2, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                body->move(2, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                body->move(0, -2);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                body->move(0, 2);
        }
}
