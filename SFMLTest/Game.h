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
	void showAllMines() const;
	void incrementSquaresOpened();
	int openedSquares() const;
	int getOpenedSquaresToWin() const;
	void makeAllSquaresUnopenable();
	void setMinesLeft(int minesLeft);
	int getMinesLeft();
	~Game();

private:
	int m_;
	int n_;
	int minesCount_;
	int minesLeft_;
	std::vector<std::vector<Square*>> grid_;
	bool isGameOver_ = false;
	int openedSquares_;
	int openedSquaresToWin_;


	void addSquares();
	void addMines();
	void simplePrint() const;
	void setNonMineSquareValues();

	
};

#endif