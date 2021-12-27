/*
	demo.cpp
	Author: Marcus Holmberg

	Permission is granted to all students to use and alter the code in this file.
	Feel free to play around with the code to see what it does. :)



	This example is using the library SFML
	The license is also included as a separate file.
	---------------------------------------------------------------------------
	SFML (Simple and Fast Multimedia Library) - Copyright (c) Laurent Gomila

	This software is provided 'as-is', without any express or implied warranty.
	In no event will the authors be held liable for any damages arising from
	the use of this software.

	Permission is granted to anyone to use this software for any purpose,
	including commercial applications, and to alter it and redistribute it
	freely, subject to the following restrictions:

	1. The origin of this software must not be misrepresented; you must not claim
	that you wrote the original software. If you use this software in a product,
	an acknowledgment in the product documentation would be appreciated but is
	not required.

	2. Altered source versions must be plainly marked as such, and must not be
	misrepresented as being the original software.

	3. This notice may not be removed or altered from any source distribution.
	---------------------------------------------------------------------------

#include <SFML/Graphics.hpp>
#include <string>

// Used for generating random numbers
#include <stdlib.h> // srand, rand

// NOTE: Because this is a demo, all example classes and funtions
// are defined in the same file.
// In your assignment, all classes are expected to have their own
// header file and source file.
class Block {
public:

	Block(float size);
	~Block();

	void SetPosition(int x, int y);
	void SetColor(const sf::Color& color);

	void Draw(sf::RenderWindow& window);

private:

	sf::RectangleShape m_shape;
	int m_positionX;
	int m_positionY;
	float m_size;
};

Block::Block(float size) {
	m_shape.setSize(sf::Vector2f(size, size));
	m_shape.setFillColor(sf::Color::Red);
	m_positionX = 0;
	m_positionY = 0;
	m_size = size;
}

Block::~Block() {
	// :)
}

void Block::SetPosition(int x, int y) {
	m_positionX = x;
	m_positionY = y;
}

void Block::SetColor(const sf::Color& color) {
	m_shape.setFillColor(color);
}

void Block::Draw(sf::RenderWindow& window) {
	m_shape.setPosition(m_positionX * m_size, m_positionY * m_size);
	window.draw(m_shape);
}


int main()
{
	const int WINDOW_WIDTH = 1000;
	const int WINDOW_HEIGHT = 800;
	const int TILE_SIZE = 10;

	const int TILE_ROWS = WINDOW_HEIGHT / TILE_SIZE;
	const int TILE_COLS = WINDOW_WIDTH / TILE_SIZE;

	const sf::Color CLEAR_COLOR = sf::Color::Black; // sf::Color(200, 200, 200) <- RGB 

	// Set seed for random numbers based on the current time.
	// A seed is needed in order to generate different numbers
	// everytime the application is executed.
	srand(time(NULL));

	// Create a window for rendering
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML demo!");

	// SFML has a bug which COULD make a wierd noice if this is not specified,
	// This is not always the case.
	// window.setFramerateLimit(60);

	sf::Font font;
	if (!font.loadFromFile("fonts/arial.ttf"))
	{
		// error... :(
	}

	sf::Text text;
	text.setString("Press space to start!");
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Red);
	text.setStyle(sf::Text::Bold);
	text.setFont(font);

	// The text object's position is originaly in it's top-left
	// corner. This will set it's position to it's center point.
	sf::FloatRect bounds = text.getLocalBounds();
	text.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
	text.setPosition(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));

	// Pulling a bug where the window won't show up for some computers
	// before an event i pulled.
	sf::Event event;
	window.pollEvent(event);

	// Render the welcome text
	window.clear(CLEAR_COLOR);
	window.draw(text);
	window.display();

	// Halt until the user has pressed the spacebar.
	// Remember to make the window focused.
	while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space));

	// Create a timer to make the frame time fixed
	const sf::Time TARGET_DELTA = sf::milliseconds(500); // New frame every half second

	sf::Clock timer; // Used to measure elapsed
	sf::Time delta; // Used to store elapsed time between frames

	// Set to target delta to render first frame directly
	delta = TARGET_DELTA;

	// Create an object to render.
	// It's position is set in the game loop below.
	Block blockyTheBlock(TILE_SIZE);
	// TIP: try creating a second block and render both! :)

	// This is the 'game loop', which should
	// 1. Handle any event
	// 2. Update the game logic (if needed)
	// 3. Render new frames (if needed)
	while (window.isOpen())
	{
		// This loop should handle any event (like key presses)
		// before rendering
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::Q) {
					window.close();
				}

				// Easter egg
				if (event.key.code == sf::Keyboard::C) {
					blockyTheBlock.SetColor(sf::Color::Green);
				}
			}
		}

		// Add up the time between iterations.
		// We don't want to render in every iteration.
		delta += timer.getElapsedTime();
		timer.restart();

		// 'delta' contain the elapsed time since the last frame
		// was rendered. We wan't to render a new frame when
		// 'delta' is greater than our targeted frame time.  
		if (delta >= TARGET_DELTA) {
			delta -= TARGET_DELTA;

			// Update 'game' logic
			blockyTheBlock.SetPosition(5 + timer.getElapsedTime().asMicroseconds(), 5);

			// The screen needs to be cleared before anything new is
			// rendered to it.
			// This can be skipped if you want to continue drawing
			// on top of the last frame. :)
			window.clear(CLEAR_COLOR);

			// Render all scene objects
			blockyTheBlock.Draw(window);

			// Reveal the masterpiece for the user.
			window.display();
		}
	}

	return 0;
}
*/