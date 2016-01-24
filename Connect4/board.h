#pragma once
#include <vector>
#include <iostream>
#include <algorithm>

class Board
{
public:
	Board(int x, int y, int inARow);
	void printBoard();
    bool hasWon(int player);
    bool hasAWin();
    bool hasATie();
	void accumulateWorth();
	bool hasVerticalWon(int square, int player, int numberInARow);
    bool hasHorizontalWon(int square, int player, int numberInARow);
    bool hasDiagonalForwardWin(int square, int player, int numberInARow);
    bool hasDiagonalBackWin(int square, int player, int numberInARow);
    void removePreviousSetValue();
    void removePreviousSetValueBasedOnColumn(int column, int player);
    void setValue(int columnValue, int val);
	bool isColFilled(int columnNum);
	bool isColumnFilled(int columnValue);
    int getWidthLeft();
    std::vector<int> *getColumnsNotFull();
    std::vector<int> *getBoard() { //faster passing pointer around
        return &m_board;
    }
    int getFillCounter() {
        return m_fillCounter;
    }
    bool isBoardFull() {
        return (m_boardSize - m_fillCounter == 0)?true : false;
    }
    int getWidth() {
        return m_x;
    }
    int getHeight() {
        return m_y;
    }
	int getInRow() {
		return m_inARow;
	}
    Board *clone() const {
        return new Board(*this);
    }
	int largetstInWorth() {
		std::vector<int> m_worth;
		m_worth.push_back(constVertical);
		m_worth.push_back(constHorizontal);
		m_worth.push_back(constDiagonalR);
		m_worth.push_back(constDiagonalL);
		int temp = -1;
		for (auto i : m_worth) {
			if (i > temp) {
				temp = i;
			}
		}
		return temp;
	}

	double getWorth(int treeDepth,int maxDepth) {
		double largestWorth = largetstInWorth();
		return (largestWorth/((double)m_inARow))*(1.0-((double)treeDepth)/((double)maxDepth))*0.01;
	}
	int constVertical;
	int constHorizontal;
	int constDiagonalL;
	int constDiagonalR;
	~Board();
private:
	int VERTICAL = 0, HORIZONTAL = 1, DIAGONALr = 2, DIAGONALl = 3;
	//count horizontal,vertical, diagonal right, diagonal left
	std::vector<int> m_board;
    std::vector<int> finVector;
	std::vector<int> colVector;
    int m_unfilled;
	int m_boardSize;
	int m_x;
	int m_y;
    int m_fillCounter;
    int m_inARow;
    int m_previousSetValueLoc;
	int colNum;
};

