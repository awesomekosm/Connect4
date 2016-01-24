#include "minimax.h"



MiniMax::MiniMax(Board *b, int *bestMiniMaxMove){
	this->board = b;
	this->bestMiniMaxMove = bestMiniMaxMove;
}
bool hasFullColumn(std::vector<int> &val, int compare) {
    return !(val.empty() && std::find(val.begin(), val.end(), compare) == val.end());
}
void MiniMax::play(){  
    double max = -100.0f;
    for (int i = 0; i < board->getWidth(); i++) {
        if (!board->isColFilled(i)) {
            double moveWorth = moveValue(i);
			//even if just a little better then the worst possible move
            if (moveWorth > max) {
                max = moveWorth;
                *bestMiniMaxMove = i;
                if (moveWorth == 1.0f) {
                    break;
                }
            }
        }
    }
}

double MiniMax::moveValue(int column) {
    board->setValue(column, black);
    double testWorth = MinMaxAlphaBeta(*this->board, -100.0f, 100.0f, 4,false);
	board->removePreviousSetValue();
    return testWorth;
}

double MiniMax::determineWorth(int treeDepth, bool hasAWin) {
    double moveWorth = 0.0f;
    if (hasAWin) {
        if (board->hasWon(red)) { 
			moveWorth = -1.0f;
        } else {
			moveWorth = 1.0f;
        }
    } else {
		moveWorth = 1.0/board->getWorth(treeDepth, 10);
    }
    return moveWorth / (10 -treeDepth);
}
//max player is AI
double MiniMax::MinMaxAlphaBeta(Board board, double max, double min, int treeDepth, bool isMaxPlayer) {
    if (treeDepth == 0 || board.hasAWin()) {
        return determineWorth(treeDepth, true);
    }
    if (isMaxPlayer) {
        for (int i = 0; i < board.getWidth(); i++) {
            if (!board.isColFilled(i)) {
                board.setValue(i, black);
				max = std::max(max, MinMaxAlphaBeta(board, max, min, treeDepth - 1, false));
                board.removePreviousSetValue();
                if (min <= max) {
                    break;
                }
            }
        }
        return max;
    } 
	if(!isMaxPlayer){
        for (int i = 0; i < board.getWidth();i++) {
            if (!board.isColFilled(i)) {
                board.setValue(i, red);
				min = std::min(min, MinMaxAlphaBeta(board,max, min, treeDepth - 1, true));
                board.removePreviousSetValue();
                if (min <= max) {
                    break;
                }
            }
        }
        return min;
    }

}


MiniMax::~MiniMax()
{
}



