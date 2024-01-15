#include "Grid.h"

#include <iostream>
#include <random>

Grid::Grid(int m, int n, int minesCount) {
	m_ = m;
	n_ = n;
	minesCount_ = minesCount;

	grid_.resize(m);
	for (auto it = grid_.begin(); it != grid_.end(); ++it) {
		(*it).resize(n);
	}

	addMines();
	simplePrint();
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
				std::cout << "E" << ' ';
			}
		}
		std::cout << "\n";
	}
}

