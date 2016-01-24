#pragma once
#include <algorithm>
#include <climits>
#include <vector>
#include "board.h"

class MiniMax
{
public:
    MiniMax(Board *b, int *bestMiniMaxMove);
    void play();
    double moveValue(int column);
    double MinMaxAlphaBeta(Board board, double max, double min, int treeDepth, bool isMaxPlayer);
    double determineWorth(int treeDepth, bool hasAWin);
    ~MiniMax();
private:
    Board *board;
	int *bestMiniMaxMove;
    int black = 88;     //X
    int red = 79;       //O
};

