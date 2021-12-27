#pragma once
#include "Shape.h";


class Block : public Shape {
public:
    Block(int x, int y, int w, sf::Color c) : x(x), y(y), width(w), color(c) {
        sf::RectangleShape temp(sf::Vector2f(w, w));
        shape = temp;
        shape.setFillColor(c);
        shape.setPosition(x, y);
    };

    void SetPosition(sf::Vector2f pos) {
        if ((int)pos.x % width != this->x || pos.y / width != this->y) {
            this->x = pos.x;
            this->y = pos.y;
        }
    }

    sf::Vector2f GetPosition() {
        return sf::Vector2f(x,y);
    }

    void SetColor(const sf::Color& c) {
        if (this->color != c) {
            this->color = c;
            shape.setFillColor(c);
        }
    }

    void Draw(sf::RenderWindow& window) {
        shape.setFillColor(color);
        shape.setPosition(x * 20, y * 20);
        window.draw(shape);
    }

private:
    sf::RectangleShape shape;
    sf::Color color;
    int x,y;
    int width;
};