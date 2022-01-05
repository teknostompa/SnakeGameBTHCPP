#pragma once
#include "GameState.h"
#include "Food.h"
#include <string>
#include <map>

using std::vector; using std::string;
class SinglePlayerState : public GameState {
public:
    SinglePlayerState(std::string settings, sf::Font font) : setting(settings) {
        this->font = font;
        vector<vector<string>>setting = getSettingsFromString(settings);
        for (int i = 0; i < setting.size(); i++) {
            if (setting.at(i).at(0) == "Snake") {
                snakeCol = intfromhex(setting.at(i).at(1));
            }
            if (setting.at(i).at(0) == "Food") {
                foodCol = intfromhex(setting.at(i).at(1));
            }
            if (setting.at(i).at(0) == "Text") {
                textCol = intfromhex(setting.at(i).at(1));
            }
            if (setting.at(i).at(0) == "Background") {
                backgroundCol = intfromhex(setting.at(i).at(1));
            }
            
            if (setting.at(i).at(0) == "Steering") {
                steering = (setting.at(i).at(1) == "Normal") ? 1 : 0;
            }
        }
        food = Food(20, foodCol, 5, 5);
        snake = Snake(snakeCol, 3, 20, steering);
        background.setSize(sf::Vector2f(20 * 20, 20 * 20));
        background.setFillColor(backgroundCol);
        //TODO set settings
    }

    void KeyEvent(sf::Keyboard::Key key) {
        snake.KeyEvent(key);
    }

    int tick() {
        gameOver = snake.tick();
        if (food.tick(snake.GetBody()) == 1) {
            score += 100;
            snake.addbody();
        }
        if (gameOver) {
            return score;
        }
        return 0;
    }

    void reset() {
        food = Food(20, foodCol, 5, 5);
        snake = Snake(snakeCol, 3, 20, steering);
        score = 0;
    }

    void Draw(sf::RenderWindow& window) {
        window.draw(background);
        food.Draw(window);
        snake.Draw(window);
        sf::Text text;
        std::string sco = "SCORE ";
        text.setString(sco += std::to_string(score));
        text.setCharacterSize(30);
        text.setFillColor(textCol);
        text.setFont(font);
        text.setOrigin(0, 0);
        text.setPosition(10, 10);
        window.draw(text);
    }
private:
    Snake snake;
    sf::Color snakeCol;
    Food food;
    sf::Color foodCol;
    int score;
    sf::Color textCol;
    sf::RectangleShape background;
    sf::Color backgroundCol;
    int steering;
    const string hex = "0123456789ABCDEF";
    string setting;
    sf::Font font;
    int gameOver;

    vector<string> getSettingFromSubString(string settings) {
        vector<string> setting;
        setting.push_back(settings.substr(0, settings.find(': ') - 1));
        setting.push_back(settings.substr(settings.find(': ') + 1, settings.length()));
        return setting;
    }

    vector<vector<string>> getSettingsFromString(string settings) {
        vector<vector<string>> settingsList;
        while (settings.find(',') != string::npos) {
            settingsList.push_back(getSettingFromSubString(settings.substr(0, settings.find(','))));
            settings = settings.substr(settings.find(',') + 2, settings.length() - 1);
        }
        settingsList.push_back(getSettingFromSubString(settings));
        return settingsList;
    }

    sf::Color intfromhex(string hexcode) {
        sf::Color col{
            (sf::Uint8)(hex.find(hexcode.substr(0, 1)) + 16 * hex.find(hexcode.substr(1, 1))),
            (sf::Uint8)(hex.find(hexcode.substr(2, 1)) + 16 * hex.find(hexcode.substr(3, 1))),
            (sf::Uint8)(hex.find(hexcode.substr(4, 1)) + 16 * hex.find(hexcode.substr(5, 1)))
        };/*
        colors[0] = hex.find(hexcode.substr(0, 1)) + 16 * hex.find(hexcode.substr(1, 1));
        colors[1] = hex.find(hexcode.substr(2, 1)) + 16 * hex.find(hexcode.substr(3, 1));
        colors[2] = hex.find(hexcode.substr(4, 1)) + 16 * hex.find(hexcode.substr(5, 1));*/
        return col;
    }
}; 
