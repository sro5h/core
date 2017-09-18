#include <SFML/Graphics.hpp>
#define TINYC2_IMPL
#include "tinyc2.h"
#undef TINYC2_IMPL
#include "Tinyc2Debug.hpp"
#include "Collider.hpp"

#define MC_PER_TICK 15625
#define SPEED 1.5

void processInput(std::shared_ptr<Body> body);

int main(int argc, char* argv[])
{
        sf::ContextSettings settings;
        settings.antialiasingLevel = 8;

        sf::RenderWindow window(sf::VideoMode(500, 500), "App", sf::Style::Default, settings);

        Tinyc2Debug debug(window);
        Collider collider;

        auto staticBody = collider.createCircleBody(64, 100, 100);
        auto aabbBody = collider.createAabbBody(50, 50, -100, -100);
        auto movingBody = collider.createCircleBody(16, 0, 0);
        movingBody->dynamic = true;

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

                        collider.update();

                        lag -= MC_PER_TICK;
                }

                sf::View view = window.getDefaultView();
                view.setCenter(0, 0);
                window.setView(view);

                window.clear(sf::Color(30, 30, 30));
                debug.draw(staticBody->body);
                debug.draw(aabbBody->body);
                debug.draw(movingBody->body);
                window.display();
        }

        return 0;
}

void processInput(std::shared_ptr<Body> body)
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
                toMove = c2Mulvs(c2Norm(toMove), SPEED);
                body->move(toMove.x, toMove.y);
        }
}
