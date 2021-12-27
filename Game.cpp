#include <SFML/Graphics.hpp>
#include <vector>
#include "Snake.h"
#include "SinglePlayerState.h"
#include "MenuState.h"
#include "GameState.h";

int main()
{
    States state = States::GAME;
    sf::RenderWindow window(sf::VideoMode(400, 400), "Snake!");
    SinglePlayerState game = SinglePlayerState("Steering: Normal, Food: FF00FF, Snake: FFFFFF, Text: CC0000, Background: 000000");
    const sf::Time TARGET_DELTA = sf::milliseconds(500);
    sf::Clock timer;
    sf::Time delta;
    delta = TARGET_DELTA;
    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close(); 
            
            if (event.type == sf::Event::KeyReleased) {
                if (state == States::GAME)game.KeyEvent(event.key.code);
            }
        }
        delta += timer.getElapsedTime();
        timer.restart();
        if (delta >= TARGET_DELTA) {
            delta -= TARGET_DELTA;
            if(state == States::GAME)game.tick();
            window.clear();
            if (state == States::GAME)game.Draw(window);
            window.display();
        }
        
    }

    return 0;
}