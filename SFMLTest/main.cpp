#include "Game.h"

#include <SFML/Graphics.hpp>
#include <climits>
#include <iostream>
#include <cstdlib>


int countAdjacentFlaggedSquares(Game& game, int x, int y, std::vector<Square*>& arr);

int main() {
	sf::RenderWindow window(sf::VideoMode(27 * 16, 27 * 16), "Minesweeper", sf::Style::Titlebar | sf::Style::Close);
	Game game(16, 16, 40);

	while (game.isGameOver() != true && window.isOpen()) {
		sf::Event event;
		
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed || game.isGameOver()) {
				window.close();	
			}
			
		}
		if (event.type == sf::Event::MouseButtonPressed) {
			int xCoord = event.mouseButton.x;
			int yCoord = event.mouseButton.y;
			Square* sq = game.getGrid().at(std::abs(xCoord / 27)).at(std::abs(yCoord / 27));
			if (event.mouseButton.button == sf::Mouse::Left) {
				if(sq->isOpenable()) {
					sq->openSquare();
				}
				if (sq->isOpened()) {
					if (sq->hasMine()) {
						window.close();
						return 0;
					} 
					else {
						std::vector<Square*> adjacentSquares;
						int adjacentFlaggedSquares = countAdjacentFlaggedSquares(game, std::abs(xCoord / 27), std::abs(yCoord/27), adjacentSquares);
						if (adjacentFlaggedSquares == sq->getValue()) {
							for (Square* square : adjacentSquares) {
								square->openSquare();
							}
						}
					}
				}
			}
			else if (event.mouseButton.button == sf::Mouse::Right) {
				if (sq->isOpenable()) {
					sq->flag();
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
				arr.push_back(adjacentSquare);
				if (adjacentSquare->isFlagged()) {
					result++;
				}
			}
		}
	}
	return result;
}