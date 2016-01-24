#include "board.h"

Board::Board(int x, int y, int inARow){
	m_x = x;
	m_y = y;
    m_inARow = inARow;
	m_boardSize = x*y;
    m_unfilled = 46; //period - default value of a square
    m_fillCounter = 0;
    m_board.resize(m_boardSize,m_unfilled);   
	colVector.resize(m_x);
}

void Board::printBoard(){
    int itter = m_boardSize;
    while (itter > 0) {
        for (int i = itter - m_x; i < itter ;i++) {
            std::cout << (char)m_board.at(i) << ' ';
        }
        std::cout << '\n';
        itter -= m_x;
    }
}

bool Board::hasWon(int player) {
    for (int i = 0; i < m_boardSize; i++) {
        if (m_board.at(i) == player) {
            if (hasDiagonalForwardWin(i, player, m_inARow) || hasDiagonalBackWin(i,player, m_inARow)) {
                return true;
            }
            if (hasVerticalWon(i, player, m_inARow) || hasHorizontalWon(i, player, m_inARow)) {
                return true;
            }
        }            
    }
    return false;
}

bool Board::hasAWin() {
    if (hasWon(88) || hasWon(79)) {
        return true;
    }
    return false;
}
bool Board::hasATie() {
    if ((hasWon(88) && hasWon(79)) || isBoardFull()) {
        return true;
    }
    return false;
}

void Board::accumulateWorth() {

}
bool Board::hasVerticalWon(int square, int player, int numberInARow) {
    int count = 0;
    for (int i = square; i < m_boardSize;) {

        if (m_board.at(i) == player) {
            count++;
            i += m_x;
        }
        else {
			if (constVertical < count) {
				constVertical = count;
			}
            return false;
        }
        if (numberInARow == count) {
            return true;
		}
    }
    return false;
}

bool Board::hasHorizontalWon(int square, int player, int numberInARow) {
    int count = 0;
    for (int i = square; i < m_boardSize; i++) {
        if (m_board.at(i) == player) {
            count++;
        }
        else {
			if (constHorizontal < count) {
				constHorizontal = count;
			}
            return false;
        }
        if (numberInARow == count) {
            return true;
        }
    }
    return false;
}

/* diagonal forward slash */
bool Board::hasDiagonalForwardWin(int square, int player, int numberInARow) {
    int count = 0;
    for (int i = square; i < m_boardSize;) {
        if (m_board.at(i) == player) {
            count++;
            i += m_x+1;
        }
        else {
			if (constDiagonalR < count) {
				constDiagonalR = count;
			}
            return false;
        }
        if (numberInARow == count) {
            return true;
        }
    }
    return false;
}

/* diagonal back slash */
bool Board::hasDiagonalBackWin(int square, int player, int numberInARow) {
    int count = 0;
    for (int i = square; i < m_boardSize;) {
        if (m_board.at(i) == player) {
            count++;
            i += m_x - 1;
        }
        else {
			if (constDiagonalL < count) {
				constDiagonalL = count;
			}
            return false;
        }
        if (numberInARow == count) {
            return true;
        }
    }
    return false;
}
void Board::removePreviousSetValue() {
    m_board.at(m_previousSetValueLoc) = m_unfilled;
	colVector.at(colNum) -= 1;
    m_fillCounter--;
}
void Board::removePreviousSetValueBasedOnColumn(int column, int player) {
    bool shouldRemove = false;
    int buffer;
	int colNum = column;
    for (int i = 0; i < m_boardSize;) {
        if (m_board.at(column) == player) {
            buffer = column;
            shouldRemove = true;
        }
        column += m_x;
        i += m_x;
    }
    if (shouldRemove) {
        m_board.at(buffer) = m_unfilled;
		colVector.at(colNum) -=1;
    }
}
void Board::setValue(int columnValue, int val){
	colNum = columnValue;
    if (!isColFilled(columnValue)) {
        for (int i = 0; i < m_boardSize;) {
            if (m_board.at(columnValue) == m_unfilled) {
                m_board.at(columnValue) = val;
                m_previousSetValueLoc = columnValue;
				colVector.at(colNum) += 1;
                return;
            }
            columnValue += m_x;
            i += m_x;
        }
    }
}

bool Board::isColFilled(int columnNum) {
	if (colVector.at(columnNum) == m_y) {
		return true;
	} else {
		return false;
	}
}
bool Board::isColumnFilled(int columnValue) {
    if (columnValue <= m_x) {
        for (int i = 0; i < m_boardSize;) {
            if (m_board.at(columnValue) == m_unfilled) {
                return false;
            }
            columnValue += m_x;
            i += m_x;
        }
    }
    return true;
}

int Board::getWidthLeft() {
    int counter=0;
    for (int i = 0; i < m_x; i++) {
        if (isColumnFilled(i)) {
            counter++;
        }
    }
    return m_x - counter;
}
std::vector<int> *Board::getColumnsNotFull() {
    finVector.clear();
    for (int i = 0; i < m_x; i++) {
        if (!isColumnFilled(i)) {
            finVector.push_back(i);
        }
    }
    return &finVector;
}

Board::~Board()
{
}
