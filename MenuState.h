#pragma once

#include "GameState.h"
#include "Block.h"
using std::string; using std::vector;
class MenuState : public GameState {
public:
    MenuState(sf::Font font) : block(Block(1, 1.3, 10, sf::Color::White)) { // std::string settings
        //TODO set settings
        vector<string> itemNames;
        itemNames.push_back("Singleplayer");
        itemNames.push_back("Multiplayer");
        itemNames.push_back("HighScore");
        itemNames.push_back("Quit");
        this->font = font;
        this->itemNames = itemNames;
        for (int i = 0; i < itemNames.size(); i++) {
            menuItems.push_back(sf::Text());
            menuItems[i].setString(itemNames[i]);
            menuItems[i].setCharacterSize(30);
            menuItems[i].setFillColor(sf::Color::White);
            menuItems[i].setFont(font);
            menuItems[i].setOrigin(0, 0);
            menuItems[i].setPosition(10, 10);
        }

    }

    ~MenuState() {

    }

    int KeyEvent(sf::Keyboard::Key key) {
        if (key == sf::Keyboard::Down) {
            selectedItem  = (selectedItem + 1) % menuItems.size();
        }
        if (key == sf::Keyboard::Up) {
            if (selectedItem != 0) {
                selectedItem--;
            }
            else {
                selectedItem = menuItems.size() - 1;
            }
        }

        if (key == sf::Keyboard::Enter) {
            if (menuItems[selectedItem].getString() == "Singleplayer") {
                return 1;
            }
            if (menuItems[selectedItem].getString() == "HighScore") {
                return 3;
            }
            if (menuItems[selectedItem].getString() == "Quit") {
                return 5;
            }

        }
        block.SetPosition(sf::Vector2f(1, 1.3 + selectedItem * 1.5));
        return 0;
    }

    void tick() {
        
    }

    void Draw(sf::RenderWindow& window) {
        for (int i = 0; i < menuItems.size(); i++) {
            menuItems[i].setFont(font);
            menuItems[i].setPosition(40, 10 + i*30);
            window.draw(menuItems[i]);
        }
        block.Draw(window);
    }
private:
    vector<sf::Text> menuItems = {};
    sf::Font font;
    vector<string> itemNames;
    Block block;
    int selectedItem = 0;
};
