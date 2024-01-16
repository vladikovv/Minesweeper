#include "Game.h"

#include <iostream>
#include <random>

Game::Game(int m, int n, int minesCount) {
	m_ = m;
	n_ = n;
	minesCount_ = minesCount;
	squaresToWin_ = m_ * n_ - minesCount;
	squaresOpened_ = 0;

	addSquares();
	addMines();
	setNonMineSquareValues();
	simplePrint();
	std::cout << std::endl;
}

int Game::getM() const {
	return m_;
}

int Game::getN() const {
	return n_;
}

int Game::getMinesCount() const {
	return minesCount_;
}

void Game::setM(int m) {
	m_ = m;
}

void Game::setN(int n) {
	n_ = n;
}

void Game::setMinesCount(int minesCount) {
	minesCount_ = minesCount;
}

void Game::addMines() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distributionX(0, m_ - 1);
	std::uniform_int_distribution<int> distributionY(0, n_ - 1);

	int addedMinesCount = 0;
	while (addedMinesCount < minesCount_) {
		int mineXCoord = distributionX(gen);
		int mineYCoord = distributionY(gen);

		if (!grid_.at(mineXCoord).at(mineYCoord)->hasMine()) {
			grid_.at(mineXCoord).at(mineYCoord)->setMine();
			addedMinesCount++;
		}
	}
}

void Game::simplePrint() const {
	for (size_t i = 0; i < m_; i++) {
		for (size_t j = 0; j < n_; j++) {
			if (grid_.at(j).at(i)->hasMine()) {
				std::cout << "M ";
			}
			else {
				std::cout << grid_.at(j).at(i)->getValue() << ' ';
			}
		}
		std::cout << std::endl;
	}
}

void Game::setNonMineSquareValues() {
	for (size_t i = 0; i < m_; i++) {
		for (size_t j = 0; j < n_; j++) {
			Square* current = grid_.at(i).at(j);
			if (current->hasMine()) {
				continue;
			}

			if (i == 0 && j == 0) {
				current->setValue(grid_.at(0).at(1)->hasMine()		//top left edge square
					+ grid_.at(1).at(0)->hasMine()
					+ grid_.at(1).at(1)->hasMine());
			}

			else if (i == 0 && j == n_ - 1) {
				current->setValue(grid_.at(0).at(n_ - 2)->hasMine()		//top right edge square
					+ grid_.at(1).at(n_ - 1)->hasMine()
					+ grid_.at(1).at(n_ - 2)->hasMine());
			}

			else if (i == m_ - 1 && j == 0) {
				current->setValue(grid_.at(m_ - 2).at(0)->hasMine()		//bottom left edge square
					+ grid_.at(m_ - 2).at(1)->hasMine()
					+ grid_.at(m_ - 1).at(1)->hasMine());
			}

			else if (i == m_ - 1 && j == n_ - 1) {
				current->setValue(grid_.at(m_ - 2).at(n_ - 1)->hasMine()		//bottom left edge square
					+ grid_.at(m_ - 1).at(n_ - 2)->hasMine()
					+ grid_.at(m_ - 2).at(n_ - 2)->hasMine());
			}

			else if (i == 0 && j > 0 && j < n_ - 1) {										//top row without the edges
				current->setValue(grid_.at(i).at(j - 1)->hasMine()
					+ grid_.at(i + 1).at(j - 1)->hasMine()
					+ grid_.at(i + 1).at(j)->hasMine()
					+ grid_.at(i + 1).at(j + 1)->hasMine()
					+ grid_.at(i).at(j + 1)->hasMine());
			}

			else if (i > 0 && i < m_ - 1 && j == n_ - 1) {										//right column without the edges
				current->setValue(grid_.at(i - 1).at(j)->hasMine()
					+ grid_.at(i - 1).at(j - 1)->hasMine()
					+ grid_.at(i).at(j - 1)->hasMine()
					+ grid_.at(i + 1).at(j - 1)->hasMine()
					+ grid_.at(i + 1).at(j)->hasMine());
			}

			else if (i == m_ - 1 && j > 0 && j < n_ - 1) {										//bottom row without the edges
				current->setValue(grid_.at(i).at(j - 1)->hasMine()
					+ grid_.at(i - 1).at(j - 1)->hasMine()
					+ grid_.at(i - 1).at(j)->hasMine()
					+ grid_.at(i - 1).at(j + 1)->hasMine()
					+ grid_.at(i).at(j + 1)->hasMine());
			}

			else if (i > 0 && i < m_ - 1 && j == 0) {										//right column without the edges
				current->setValue(grid_.at(i - 1).at(j)->hasMine()
					+ grid_.at(i - 1).at(j + 1)->hasMine()
					+ grid_.at(i).at(j + 1)->hasMine()
					+ grid_.at(i + 1).at(j + 1)->hasMine()
					+ grid_.at(i + 1).at(j)->hasMine());
			}
			
			else {
				current->setValue(grid_.at(i - 1).at(j - 1)->hasMine()					//rest of the squares
					+ grid_.at(i - 1).at(j)->hasMine()
					+ grid_.at(i - 1).at(j + 1)->hasMine()
					+ grid_.at(i).at(j + 1)->hasMine()
					+ grid_.at(i + 1).at(j + 1)->hasMine()
					+ grid_.at(i + 1).at(j)->hasMine()
					+ grid_.at(i + 1).at(j - 1)->hasMine()
					+ grid_.at(i).at(j - 1)->hasMine());
			}
		}

	}
}

std::vector<std::vector<Square*>> Game::getGrid() const {
	return grid_;
}

void Game::addSquares() {
	for (size_t i = 0; i < m_; i++) {
		std::vector<Square*> row;
		for (size_t j = 0; j < n_; j++) {
			Square* square = new Square(i, j);
			row.push_back(square);
		}
		grid_.push_back(row);
	}
}

void Game::endGame() {
	isGameOver_ = true;
 }

bool Game::isGameOver() const {
	return isGameOver_;
}

void Game::incrementSquaresOpened() {
	squaresOpened_++;
}

int Game::getSquaresOpened() const {
	return squaresOpened_;
}

int Game::openedSquaresToWin() const {
	return squaresToWin_;
}

void Game::showAllMines() const {
	for (size_t i = 0; i < m_; i++) {
		std::vector<Square*> row = grid_.at(i);
		for (size_t j = 0; j < n_; j++) {
			Square* current = row.at(j);
			if (current->hasMine() && !current->isFlagged()) {
				sf::Texture texture;
				if (!texture.loadFromFile("textures/MINESWEEPER_M.png")) {
					std::cout << "Error loading texture!" << std::endl;
				}
				current->changeSprite(texture);
			}
		}
	}
}

Game::~Game() {
	for (size_t i = 0; i < m_; i++) {
		std::vector<Square*> row = grid_.at(i);
		for (size_t j = 0; j < n_; j++) {
			delete row.at(j);
		}
	}
}