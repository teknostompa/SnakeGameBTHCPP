#pragma once
#pragma once
#include "Shape.h"
#include <stdlib.h>

class Food {
public:
    Food(int w = 10, sf::Color c = sf::Color::Red, int x = 5, int y = 5) : x(x), y(y), width(w), color(c) {
        sf::RectangleShape temp(sf::Vector2f(w, w));
        shape = temp;
        shape.setFillColor(c);
        shape.setPosition(x, y);
        srand(time(NULL));
    };

    void SetPosition(sf::Vector2f pos) {
        if ((int)pos.x % width != this->x || pos.y / width != this->y) {
            this->x = pos.x;
            this->y = pos.y;
        }
    }

    void SetColor(const sf::Color& c) {
        if (this->color != c) {
            this->color = c;
            shape.setFillColor(c);
        }
    }

    int tick(std::vector<Block> body) {
        if (x == body[0].GetPosition().x && y == body[0].GetPosition().y) {
            //TODO Gen new food
            while(true) {
                x = rand() % 20;
                y = rand() % 20;
                for (int i = 0; i < body.size(); i++) {
                    if (body[i].GetPosition().x == x && body[i].GetPosition().y == y) {
                        goto rand_not_successful;
                    }
                }
                break;
            rand_not_successful:
                continue;
            }
            return 1;
        }
        return 0;
    }

    void Draw(sf::RenderWindow& window) {
        shape.setFillColor(color);
        shape.setPosition(x * 20 + ((20-width)/2), y * 20 + ((20 - width) / 2));
        window.draw(shape);
    }

private:
    sf::RectangleShape shape;
    sf::Color color;
    int x, y;
    int width;
};