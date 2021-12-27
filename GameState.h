#pragma once
#include <SFML/Graphics.hpp>

enum class States {
    MENU = 0,
    GAME = 1,
    SETTINGS = 2,
    HIGHSCORE = 3
};

class GameState {
public:

    GameState(void) {

    }

    void KeyEvent(sf::Keyboard::Key key);
    void tick();
    void Draw(sf::RenderWindow& window);

private:
    sf::Color color;
};