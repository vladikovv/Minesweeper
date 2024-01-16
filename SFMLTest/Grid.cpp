#include "Grid.h"

#include <iostream>
#include <random>

Grid::Grid(int m, int n, int minesCount) {
	m_ = m;
	n_ = n;
	minesCount_ = minesCount;

	setSquaresCoordinates();
	addMines();

	setNonMineSquareValues();
	simplePrint();
	std::cout << std::endl;
}

int Grid::getM() {
	return m_;
}

int Grid::getN() {
	return n_;
}

int Grid::getMinesCount() {
	return minesCount_;
}

void Grid::setM(int m) {
	m_ = m;
}

void Grid::setN(int n) {
	n_ = n;
}

void Grid::setMinesCount(int minesCount) {
	minesCount_ = minesCount;
}

void Grid::addMines() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distributionX(0, m_ - 1);
	std::uniform_int_distribution<int> distributionY(0, n_ - 1);

	int addedMinesCount = 0;
	while (addedMinesCount < minesCount_) {
		int mineXCoord = distributionX(gen);
		int mineYCoord = distributionY(gen);
		
		Square* currentSquare = &grid_.at(mineXCoord).at(mineYCoord);
		if (!currentSquare->hasMine()) {
			currentSquare->setMine();
			addedMinesCount++;
		}
	}
}

void Grid::simplePrint() {
	for (auto it1 = grid_.begin(); it1 != grid_.end(); ++it1) {
		for (auto it2 = (*it1).begin(); it2 != (*it1).end(); ++it2) {
			if ((*it2).hasMine()) {
				std::cout << "M" << ' ';
			} else {
				std::cout << (*it2).getValue() << ' ';
			}
		}
		std::cout << "\n";
	}
}

void Grid::setNonMineSquareValues() {
	for (size_t i = 0; i < m_; i++) {
		for (size_t j = 0; j < n_; j++) {
			Square* current = &grid_.at(i).at(j);
			if (current->hasMine()) {
				continue;
			}

			if (i == 0 && j == 0) {
				current->setValue(grid_.at(0).at(1).hasMine()		//top left edge square
					+ grid_.at(1).at(0).hasMine()
					+ grid_.at(1).at(1).hasMine());
			}

			else if (i == 0 && j == n_ - 1) {
				current->setValue(grid_.at(0).at(n_ - 2).hasMine()		//top right edge square
					+ grid_.at(1).at(n_ - 1).hasMine()
					+ grid_.at(1).at(n_ - 2).hasMine());
			}

			else if (i == m_ - 1 && j == 0) {
				current->setValue(grid_.at(m_ - 2).at(0).hasMine()		//bottom left edge square
					+ grid_.at(m_ - 2).at(1).hasMine()
					+ grid_.at(m_ - 1).at(1).hasMine());
			}

			else if (i == m_ - 1 && j == n_ - 1) {
				current->setValue(grid_.at(m_ - 2).at(n_ - 1).hasMine()		//bottom left edge square
					+ grid_.at(m_ - 1).at(n_ - 2).hasMine()
					+ grid_.at(m_ - 2).at(n_ - 2).hasMine());
			}

			else if (i == 0 && j > 0 && j < n_ - 1) {										//top row without the edges
				current->setValue(grid_.at(i).at(j - 1).hasMine()
					+ grid_.at(i + 1).at(j - 1).hasMine()
					+ grid_.at(i + 1).at(j).hasMine()
					+ grid_.at(i + 1).at(j + 1).hasMine()
					+ grid_.at(i).at(j + 1).hasMine());
			}

			else if (i > 0 && i < m_ - 1 && j == n_ - 1) {										//right column without the edges
				current->setValue(grid_.at(i - 1).at(j).hasMine()
					+ grid_.at(i - 1).at(j - 1).hasMine()
					+ grid_.at(i).at(j - 1).hasMine()
					+ grid_.at(i + 1).at(j - 1).hasMine()
					+ grid_.at(i + 1).at(j).hasMine());
			}

			else if (i == m_ - 1 && j > 0 && j < n_ - 1) {										//bottom row without the edges
				current->setValue(grid_.at(i).at(j - 1).hasMine()
					+ grid_.at(i - 1).at(j - 1).hasMine()
					+ grid_.at(i - 1).at(j).hasMine()
					+ grid_.at(i - 1).at(j + 1).hasMine()
					+ grid_.at(i).at(j + 1).hasMine());
			}

			else if (i > 0 && i < m_ - 1 && j == 0) {										//right column without the edges
				current->setValue(grid_.at(i - 1).at(j).hasMine()
					+ grid_.at(i - 1).at(j + 1).hasMine()
					+ grid_.at(i).at(j + 1).hasMine()
					+ grid_.at(i + 1).at(j + 1).hasMine()
					+ grid_.at(i + 1).at(j).hasMine());
			}
			
			else {
				current->setValue(grid_.at(i - 1).at(j - 1).hasMine()					//rest of the squares
					+ grid_.at(i - 1).at(j).hasMine()
					+ grid_.at(i - 1).at(j + 1).hasMine()
					+ grid_.at(i).at(j + 1).hasMine()
					+ grid_.at(i + 1).at(j + 1).hasMine()
					+ grid_.at(i + 1).at(j).hasMine()
					+ grid_.at(i + 1).at(j - 1).hasMine()
					+ grid_.at(i).at(j - 1).hasMine());
			}
		}
	}
}

std::vector<std::vector<Square>> Grid::getGrid() {
	return grid_;
}

void Grid::addSquares() {
	for (size_t i = 0; i < m_; i++) {
		std::vector<Square> row;
		for (size_t j = 0; j < n_; j++) {
			Square sq(i, j);
			row.push_back(sq);
		}
		grid_.push_back(row);
	}
}

