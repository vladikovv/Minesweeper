#ifndef GAME_H
#define GAME_H

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
	void endGame();
	bool isGameOver();
	~Game();

private:
	int m_;
	int n_;
	int minesCount_;
	std::vector<std::vector<Square*>> grid_;
	bool isGameOver_ = false;
	int squaresToWin_;

	void addSquares();
	void addMines();
	void simplePrint();
	void setNonMineSquareValues();

	
};

#endif