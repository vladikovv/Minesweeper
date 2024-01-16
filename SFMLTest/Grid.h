#ifndef GRID_H
#define GRID_H

#include<vector>
#include "Square.h"

class Game {
public:
	Game(int m, int n, int minesCount);
	int getM();
	int getN();
	int getMinesCount();
	void setM(int m);
	void setN(int n);
	void setMinesCount(int minesCount);
	std::vector<std::vector<Square*>> getGrid();
	~Game();

private:
	int m_;
	int n_;
	int minesCount_;
	std::vector<std::vector<Square*>> grid_;
	bool gameOver_ = false;

	void addSquares();
	void addMines();
	void simplePrint();
	void setNonMineSquareValues();
	void gameOver();
	
};

#endif