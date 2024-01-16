#include "Game.h"
#include "Constants.h"

#include <SFML/Graphics.hpp>
#include <climits>
#include <iostream>
#include <cstdlib>


int countAdjacentFlaggedSquares(const Game& game, const int x, const int y, std::vector<Square*>& adjacentSquares);
void revealEmptySquaresRecursive(Game& game, int x, int y);

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
						if (sq->hasMine()) {
							game.showAllMines();
							std::cout << "YOU LOSE!" << std::endl;
						}
						if (sq->getValue() == 0) {
							revealEmptySquaresRecursive(game, xCoord / SPRITE_LENGTH, yCoord / SPRITE_LENGTH);
						}
						sq->openSquare();
						continue;
						//TODO: make a system that ends the game correctly
					}
					if (sq->isOpened()) {
						std::vector<Square*> adjacentSquares;
						int adjacentFlaggedSquares = countAdjacentFlaggedSquares(game, xCoord / SPRITE_LENGTH, yCoord / SPRITE_LENGTH, adjacentSquares);
						if (adjacentFlaggedSquares == sq->getValue()) {
							for (Square* adjSquare : adjacentSquares) {
								if (!adjSquare->isFlagged()) {
									if (adjSquare->hasMine()) {
										game.showAllMines();
										std::cout << "YOU LOSE!" << std::endl;
									} 
									else {
										if (adjSquare->getValue() == 0) {
											revealEmptySquaresRecursive(game, adjSquare->getX(), adjSquare->getY());
										}
										adjSquare->openSquare();
										game.incrementSquaresOpened();
									}
								}
							}
						}
					}
				} 
				else if (event.mouseButton.button == sf::Mouse::Right) {
					if (sq->isOpenable()) {
						sq->flag();
					} else if (sq->isFlagged()) {
						sq->removeFlag();
					}
				}
			}

			if (game.getSquaresOpened() == game.openedSquaresToWin()) {
				window.close();
				std::cout << "YOU WIN!" << std::endl;
				return 0;
			}
		}
		
		window.clear(sf::Color(0,0,0,255));

		for (size_t i = 0; i < game.getM(); i++) {
			for (size_t j = 0; j < game.getN(); j++) {
				window.draw(game.getGrid()[i][j]->getSprite());
			}
		}
		std::cout << "needed number of squares for a win: " << game.openedSquaresToWin() << std::endl;
		std::cout << "current number of squares opened: " << game.getSquaresOpened() << std::endl;

		window.display();
	}

	return 0;
}

int countAdjacentFlaggedSquares(const Game& game, const int x, const int y, std::vector<Square*>& adjacentSquares) {
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
					adjacentSquares.push_back(adjacentSquare);
				}
				if (adjacentSquare->isFlagged()) {
					result++;
				}
			}
		}
	}
	return result;
}

void revealEmptySquaresRecursive(Game& game, int x, int y) {
	if (x < 0 || x >= game.getM() || y < 0 || y >= game.getN()) {
		return;
	}

	Square* currentSquare = game.getGrid().at(x).at(y);
	if (currentSquare->isOpened()) {
		return;
	}

	currentSquare->openSquare();
	game.incrementSquaresOpened();

	if (currentSquare->getValue() != 0) {
		return;
	}

	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {
			revealEmptySquaresRecursive(game, x + i, y + j);
		}
	}
}