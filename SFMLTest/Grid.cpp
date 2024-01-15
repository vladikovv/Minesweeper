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

}

