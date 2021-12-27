#pragma once
#include <SFML/Graphics.hpp>

class Shape {
public:

    Shape(void) {

    }

    void SetPosition(int x, int y);
    void SetColor(const sf::Color& color);

    void Draw(sf::RenderWindow& window);

private:
    sf::Color color;
};