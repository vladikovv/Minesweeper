#include "Game.h"

#include <SFML/Graphics.hpp>
#include <climits>
#include <iostream>
#include <cstdlib>

constexpr int SPRITE_LENGTH = 54;
constexpr int LENGTH = 16;
constexpr int WIDTH = 16;
constexpr int NUMBER_OF_MINES = 40;


int countAdjacentFlaggedSquares(Game& game, int x, int y, std::vector<Square*>& arr);

int main() {
	sf::RenderWindow window(sf::VideoMode(SPRITE_LENGTH * LENGTH, SPRITE_LENGTH * WIDTH), "Minesweeper", sf::Style::Titlebar | sf::Style::Close);
	Game game(LENGTH, WIDTH, NUMBER_OF_MINES);

	while (game.isGameOver() != true && window.isOpen()) {
		sf::Event event;
		
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed || game.isGameOver()) {
				window.close();	
			}
			if (event.type == sf::Event::MouseButtonReleased) {
				int xCoord = event.mouseButton.x;
				int yCoord = event.mouseButton.y;
				Square* sq = game.getGrid().at(xCoord / SPRITE_LENGTH).at(yCoord / SPRITE_LENGTH);
				if (event.mouseButton.button == sf::Mouse::Left) {
					if (sq->isOpenable()) {
						sq->openSquare();
					}
					if (sq->isOpened()) {
						if (sq->hasMine()) {
							window.close();
							return 0;
						} else {
							std::vector<Square*> adjacentSquares;
							int adjacentFlaggedSquares = countAdjacentFlaggedSquares(game, xCoord / SPRITE_LENGTH, yCoord / SPRITE_LENGTH, adjacentSquares);
							if (adjacentFlaggedSquares == sq->getValue()) {
								for (Square* adjSquare : adjacentSquares) {
									if (adjSquare->hasMine()) {
										window.close();
										return 0;
									}
									adjSquare->openSquare();
								}
							}
						}
					}
				} else if (event.mouseButton.button == sf::Mouse::Right) {
					if (sq->isOpenable()) {
						sq->flag();
					} else if (sq->isFlagged()) {
						sq->removeFlag();
					}
				}
			}
		}
		

		window.clear(sf::Color(0,0,0,255));

		for (size_t i = 0; i < game.getM(); i++) {
			for (size_t j = 0; j < game.getN(); j++) {
				window.draw(game.getGrid()[i][j]->getSprite());
			}
		}
		window.display();
	}


	return 0;
}

int countAdjacentFlaggedSquares(Game& game, int x, int y, std::vector<Square*>& arr) {
	int result = 0;
	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {
			if (i == 0 && j == 0) {
				continue;
			}

			int newX = x + i;
			int newY = y + j;

			if (newX >= 0 && newX < game.getM() && newY >= 0 && newY < game.getN()) {
				Square* adjacentSquare = game.getGrid().at(newX).at(newY);
				if (!adjacentSquare->isOpened()) {
					arr.push_back(adjacentSquare);
				}
				if (adjacentSquare->isFlagged()) {
					result++;
				}
			}
		}
	}
	return result;
}