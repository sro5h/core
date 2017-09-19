#include <SFML/Graphics.hpp>
#define TINYC2_IMPL
#include "tinyc2.h"
#undef TINYC2_IMPL
#include "Collider.hpp"
#include "Player.hpp"
#include "Box.hpp"

#define MC_PER_TICK 15625
#define SPEED 1.5

int main(int argc, char* argv[])
{
        sf::ContextSettings settings;
        settings.antialiasingLevel = 8;

        sf::RenderWindow window(sf::VideoMode(500, 500), "App", sf::Style::Default, settings);

        Collider collider;

        Player player = Player(collider);

        Box box = Box(collider, 50, 50);

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

                        collider.update();

                        lag -= MC_PER_TICK;
                }

                sf::View view = window.getDefaultView();
                view.setCenter(0, 0);
                window.setView(view);

                window.clear(sf::Color(30, 30, 30));
                box.draw(window);
                player.draw(window);
                window.display();
        }

        return 0;
}
