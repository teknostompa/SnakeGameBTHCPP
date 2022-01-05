#pragma once
#include "GameState.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Block.h"

using std::vector; using std::string;
class HighScoreState : public GameState {
public:


	HighScoreState(int Score, sf::Font font) : block(Block(1, 1.3, 10, sf::Color::White)), font(font), newScore(Score){
		nameEntering = true;
		explanation = sf::Text();
		explanation.setOrigin(0, 0);
		explanation.setFillColor(sf::Color::White);
		explanation.setCharacterSize(30);
		explanation.setString("Type  your  name\nthen  press  Enter");
		nameDisplay = sf::Text();
		nameDisplay.setOrigin(0, 0);
		nameDisplay.setFillColor(sf::Color::White);
		nameDisplay.setCharacterSize(30);
		std::ifstream scores("scores.txt");
		if (scores.is_open()) {
			string line;
			vector<string> itemNames;
			while (getline(scores, line)) {
				itemNames.push_back(line);
			}scores.close();
			this->itemNames = itemNames;
		}
		else {

		}scores.close();

	}

	void GenerateHighScoreList() {
		itemNames = sortScores(itemNames);
		std::ofstream scores("scores.txt", std::ios::trunc);
		for (int i = 0; i < itemNames.size(); i++) {
			scores << itemNames[i] << "\n";
		}scores.close();
		itemNames.push_back("Quit");
		for (int i = 0; i < itemNames.size(); i++) {
			menuItems.push_back(sf::Text());
			menuItems[i].setString(itemNames[i]);
			menuItems[i].setCharacterSize(30);
			menuItems[i].setFillColor(sf::Color::White);
			menuItems[i].setFont(font);
			menuItems[i].setOrigin(0, 0);
		}
	}

	HighScoreState(sf::Font font) : block(Block(1, 1.3, 10, sf::Color::White)) {
		std::ifstream scores("scores.txt");
		if (scores.is_open()) {
			string line;
			vector<string> itemNames;
			while (getline(scores, line)) {
				itemNames.push_back(line);
			}scores.close();
			
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
		else {

		}
	}

	int KeyEvent(sf::Keyboard::Key key) {
		if (nameEntering) {
			if (key == sf::Keyboard::BackSpace) {
				Name = Name.substr(0, Name.size() - 2);
			}
			else if (key == sf::Keyboard::Space) {
				Name += " ";
			}
			else if (key == sf::Keyboard::Enter) {
				itemNames.push_back(Name + " " + std::to_string(newScore));
				GenerateHighScoreList();
				nameEntering = false;
			}
			else {
				Name += KeyToChar(key);
			}

		}
		else {
			if (key == sf::Keyboard::Down) {
				selectedItem = (selectedItem + 1) % menuItems.size();
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
				if (menuItems[selectedItem].getString() == "Quit") {
					return 5;
				}
			}

			block.SetPosition(sf::Vector2f(1, 1.3 + selectedItem * 1.5));
		}
		return 0;
	}
	void tick() {

	}
	void Draw(sf::RenderWindow& window) {

		if (nameEntering) {
			nameDisplay.setString(Name);
			nameDisplay.setFont(font);
			nameDisplay.setPosition(30, 90);
			explanation.setFont(font);
			explanation.setPosition(30, 30);
			window.draw(nameDisplay);
			window.draw(explanation);
		}
		else {
			for (int i = 0; i < menuItems.size(); i++) {
				menuItems[i].setFont(font);
				menuItems[i].setPosition(40, 10 + i * 30);
				window.draw(menuItems[i]);
			}
			block.Draw(window);
		}

	}
private:
	sf::Text nameDisplay;
	sf::Text explanation;
	vector<sf::Text> menuItems = {};
	sf::Font font;
	vector<string> itemNames;
	Block block;
	int selectedItem = 0;
	bool nameEntering = false;
	string Name = "";
	int newScore;

	int scoreFromLine(string line) {
		int splitPos = line.find(" ");
		return std::stoi(line.substr(splitPos, line.size() - 1));
	}

	vector<string> sortScores(vector<string> list) {
		int PosOfNewScore = list.size() - 1;
		while (PosOfNewScore != 0 && scoreFromLine(list[PosOfNewScore]) > scoreFromLine(list[PosOfNewScore - 1])) {
			string temp = list[PosOfNewScore];
			list[PosOfNewScore] = list[PosOfNewScore - 1];
			list[PosOfNewScore - 1] = temp;
			PosOfNewScore--;
		}
		
		

		return list;
	}

	char KeyToChar(const sf::Keyboard::Key& k) {
		char ret;
		switch (k) {
			case sf::Keyboard::A:
				ret = 'A';
				break;
			case sf::Keyboard::B:
				ret = 'B';
				break;
			case sf::Keyboard::C:
				ret = 'C';
				break;
			case sf::Keyboard::D:
				ret = 'D';
				break;
			case sf::Keyboard::E:
				ret = 'E';
				break;
			case sf::Keyboard::F:
				ret = 'F';
				break;
			case sf::Keyboard::G:
				ret = 'G';
				break;
			case sf::Keyboard::H:
				ret = 'H';
				break;
			case sf::Keyboard::I:
				ret = 'I';
				break;
			case sf::Keyboard::J:
				ret = 'J';
				break;
			case sf::Keyboard::K:
				ret = 'K';
				break;
			case sf::Keyboard::L:
				ret = 'L';
				break;
			case sf::Keyboard::M:
				ret = 'M';
				break;
			case sf::Keyboard::N:
				ret = 'N';
				break;
			case sf::Keyboard::O:
				ret = 'O';
				break;
			case sf::Keyboard::P:
				ret = 'P';
				break;
			case sf::Keyboard::Q:
				ret = 'Q';
				break;
			case sf::Keyboard::R:
				ret = 'R';
				break;
			case sf::Keyboard::S:
				ret = 'S';
				break;
			case sf::Keyboard::T:
				ret = 'T';
				break;
			case sf::Keyboard::U:
				ret = 'U';
				break;
			case sf::Keyboard::V:
				ret = 'V';
				break;
			case sf::Keyboard::W:
				ret = 'W';
				break;
			case sf::Keyboard::X:
				ret = 'X';
				break;
			case sf::Keyboard::Y:
				ret = 'Y';
				break;
			case sf::Keyboard::Z:
				ret = 'Z';
				break;
			default:
				ret = '?';
				break;
		}
		return ret;
	}
};