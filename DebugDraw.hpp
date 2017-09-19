#ifndef _DRAW_UTIL_HPP
#define _DRAW_UTIL_HPP

#include <SFML/Graphics.hpp>

class DebugDraw {
public:
        DebugDraw(sf::RenderTarget& target)
                : target(target) {}

        void drawPoint(float x, float y, sf::Color color)
        {
                sf::CircleShape shape(1);
                shape.setOrigin(1, 1);
                shape.setPosition(x, y);
                shape.setFillColor(color);

                target.draw(shape);
        }

        void drawLine(float x1, float y1, float x2, float y2, sf::Color color)
        {
                sf::Vertex shape[] = {
                        sf::Vertex(sf::Vector2f(x1, y1), color),
                        sf::Vertex(sf::Vector2f(x2, y2), color)
                };

                target.draw(shape, 2, sf::Lines);
        }

        void drawRect(float w, float h, float x, float y, sf::Color color)
        {
                sf::RectangleShape shape(sf::Vector2f(w, h));
                shape.setPosition(x, y);
                shape.setFillColor(sf::Color::Transparent);
                shape.setOutlineColor(color);
                shape.setOutlineThickness(1.0f);

                target.draw(shape);
        }

        void drawCircle(float r, float x, float y, sf::Color color)
        {
                sf::CircleShape shape(r);
                shape.setOrigin(r, r);
                shape.setPosition(x, y);
                shape.setFillColor(sf::Color::Transparent);
                shape.setOutlineColor(color);
                shape.setOutlineThickness(1.0f);

                target.draw(shape);
        }

private:
        sf::RenderTarget& target;
};

#endif // _DRAW_UTIL_HPP
