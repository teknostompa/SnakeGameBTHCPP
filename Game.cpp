#include <SFML/Graphics.hpp>
#include <vector>
#include "Snake.h"
#include "SinglePlayerState.h"
#include "MenuState.h"
#include "GameState.h";
#include "HighScoreState.h"

int main()
{
    States state = States::MENU;
    sf::RenderWindow window(sf::VideoMode(400, 400), "Snake!");
    int menuChoice;
    int gameOver;
    sf::Font font;
    if (!font.loadFromFile("fonts/ARCADECLASSIC.TTF")){}
    HighScoreState highScore = HighScoreState(font);
    SinglePlayerState game = SinglePlayerState("Steering: Normal, Food: FF00FF, Snake: FFFFFF, Text: CC0000, Background: 000000", font);
    MenuState menu = MenuState(font);
    sf::Time TARGET_DELTA = sf::milliseconds(30);
    sf::Clock timer;
    sf::Time delta;
    delta = TARGET_DELTA;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyReleased) {
                if (state == States::GAME)game.KeyEvent(event.key.code);
                else if (state == States::HIGHSCORE) {
                    menuChoice = highScore.KeyEvent(event.key.code);
                    if (menuChoice != 0) {
                        switch (menuChoice)
                        {
                        case 5:
                            state = States::MENU;
                            break;
                        default:
                            break;
                        }
                    }
                    menuChoice = 0;
                }
                else if (state == States::MENU) {
                    menuChoice = menu.KeyEvent(event.key.code);
                    if (menuChoice != 0) {
                        switch (menuChoice)
                        {
                        case 1:
                            state = States::GAME;
                            TARGET_DELTA = sf::milliseconds(500);
                            break;
                        case 3:
                            highScore = HighScoreState(font);
                            state = States::HIGHSCORE;
                            break;
                        case 5:
                            window.close();
                        default:
                            break;
                        }
                    }
                    menuChoice = 0;
                }
                
            }
        }
        delta += timer.getElapsedTime();
        timer.restart();
        if (delta >= TARGET_DELTA) {
            delta -= TARGET_DELTA;
            if (state == States::GAME) {
                gameOver = game.tick();
                if (gameOver != 0) {
                    highScore = HighScoreState(gameOver, font);
                    state = States::HIGHSCORE;
                }
            }
            if (state == States::MENU)menu.tick();
            if (state == States::HIGHSCORE)highScore.tick();
            window.clear();
            if (state == States::GAME)game.Draw(window);
            if (state == States::MENU)menu.Draw(window);
            if (state == States::HIGHSCORE)highScore.Draw(window);
            window.display();
        }
        
    }

    return 0;
}