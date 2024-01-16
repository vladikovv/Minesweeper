#ifndef GAME_H
#define GAME_H

#include<vector>
#include "Square.h"

class Game {
public:
	Game(int m, int n, int minesCount);
	int getM() const;
	int getN() const;
	int getMinesCount() const;
	void setM(int m);
	void setN(int n);
	void setMinesCount(int minesCount);
	std::vector<std::vector<Square*>> getGrid() const;
	void endGame();
	bool isGameOver() const;
	void incrementSquaresOpened();
	int getSquaresOpened() const;
	int openedSquaresToWin() const;
	void showAllMines() const;
	~Game();

private:
	int m_;
	int n_;
	int minesCount_;
	std::vector<std::vector<Square*>> grid_;
	bool isGameOver_ = false;
	int squaresToWin_;
	int squaresOpened_;

	void addSquares();
	void addMines();
	void simplePrint() const;
	void setNonMineSquareValues();

	
};

#endif