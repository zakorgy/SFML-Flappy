#include <SFML/Graphics.hpp>

#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "Bird.h"
#include "Pipe.h"
#include "Constants.h"

using namespace std;

static sf::Font font;
static sf::Text message;

void insertNewPipes(vector<Pipe>& pipes, int& random, float xPos);
bool updateGame(sf::RenderWindow* window, sf::Time delta, Bird& bird, vector<Pipe>& pipes, int& random);
void reRollToNearRandom(int& random); 
void createPipes(vector<Pipe>& pipes, int& random);
void setupMessage();

int main()
{
	srand(time(NULL));

	if (!font.loadFromFile("resources/sansation.ttf"))
		return EXIT_FAILURE;
	setupMessage();

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Sfml-Flappy");
	bool replay = false;
	do {
		sf::Clock clock;
		Bird& bird = Bird((float)WINDOW_WIDTH, (float)WINDOW_HEIGHT);
		int random = 20;
		vector<Pipe> pipes;
		createPipes(pipes, random);
		replay = updateGame(&window, clock.restart(), bird, pipes, random);
	} while (replay);
	return 0;
}

void setupMessage() {
	message.setFont(font);
	message.setCharacterSize(40);
	message.setPosition(120.f, 150.f);
	message.setFillColor(sf::Color::Red);
	message.setString("Welcome to Sfml-Flappy!\nPress space to start the game");
}

bool updateGame(sf::RenderWindow* window, sf::Time delta, Bird& bird, vector<Pipe>& pipes, int& random) {
	bool isPlaying = false;
	bool isAlive = true;
	while (window->isOpen())
	{
		// Handle events
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Space)
				{
					if (isAlive && isPlaying) {
						bird.moveUp();
					} else if (isAlive && !isPlaying) {
						isPlaying = true;
					} else {
						return true;
					}
				}
			}
		}

		if (isPlaying) {
			if (isAlive) {

				// Update game objects
				bird.update(delta);

				if (bird.getYPos() > (WINDOW_HEIGHT - BIRD_RADIUS)) {
					isAlive = false;
					message.setString("You died!\nPress space to restart the game");
					continue;
				}

				for (int i = 0; i < pipes.size(); ++i) {
					if (pipes[i].shouldUpdate()) {
						pipes.erase(pipes.begin() + i);

						// Check if we have removed an upper and a lower pipe already and add two new pipes
						if (pipes.size() & 1) {
							float nextXPos = pipes[pipes.size()].getXPos() + PIPE_WIDTH + VERTICAL_GAP;
							insertNewPipes(pipes, random, nextXPos);
						}
					}
					else if (pipes[i].collidesWithBird(bird)) {
						isAlive = false;
						message.setString("You died!\nPress space to restart the game");
						continue;
					} else {
						pipes[i].update(delta);
					}
				}
			}
			// Clear background
			window->clear(sf::Color(0, 153, 204));

			// Draw game objects
			for (auto const& pipe : pipes) {
				window->draw(pipe);
			}
			window->draw(bird);
			if (!isAlive) {
				window->draw(message);
			}
		} else {
			// Clear background
			window->clear(sf::Color(0, 153, 204));
			window->draw(message);
		}

		// Present
		window->display();
	}
	return false;
}

void reRollToNearRandom(int& random) {
	int oldRand = random;
	do {
		random = rand() % 20 + 20;
	} while (abs(oldRand - random) > 10);
}

void insertNewPipes(vector<Pipe>& pipes, int& random, float xPos) {
	reRollToNearRandom(random);
	Pipe& pipe_up = Pipe(PIPE_WIDTH, random * 10.f, xPos, true);
	pipes.push_back(pipe_up);
	Pipe& pipe_down = Pipe(PIPE_WIDTH, WINDOW_HEIGHT - random * 10.f - HORIZONTAL_GAP, xPos, false);
	pipes.push_back(pipe_down);
}

void createPipes(vector<Pipe>& pipes, int& random) {
	for (int i = 0; i < (int)(WINDOW_WIDTH / PIPE_WIDTH); ++i) {
		insertNewPipes(pipes, random, WINDOW_WIDTH + i * (PIPE_WIDTH + VERTICAL_GAP));
	}
}
