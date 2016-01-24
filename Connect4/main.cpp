#include <iostream>
#include <chrono>
#include <stack>
#include <thread>
#include "board.h"
#include "tree.h"
#include "minimax.h"

typedef std::chrono::high_resolution_clock Clock;

void threadusInterruptus(double *duration) {
    auto s = Clock::now();
    auto e = Clock::now();
    double difference = std::chrono::nanoseconds(e - s).count();
    if (difference >= *duration) {
        std::cout << "time\n";
        return;
    }
}
int getPlayerValue(bool &redFirst,std::string val) {
    if (val.compare("red")==0) {redFirst = true;return 79;}
    else {redFirst = false;return 88;}
}
void printDefault() {
    std::cout << "X is black O is red\n";
    std::cout << "Press 1 to print to play vs computah\n";
    std::cout << "Press 2 to play human vs human\n";
    std::cout << "Press q  to Exit \n";
}

int main() {
    int black = 88;     //X
    int red = 79;       //O
    Tree *tree = new Tree();
    int *bestMiniMaxMove = new int();
    //std::thread minmaxThread(fillTree, tree, board, black, red);
    std::string input;
    printDefault();
    bool running = true;
    while (running == true) {
        std::getline(std::cin, input);
        if (input == "1") {
            int inputWidth = 7;
            int inputHeight = 6;
            int inputInARow = 4;
            double timeRequirement;
            bool blackFirst = false;
            std::cout << "Enter board Width: ";
            std::cin >> inputWidth;
            std::cout << "Enter board Height: ";
            std::cin >> inputHeight;
            std::cout << "Enter win requirement: ";
            std::cin >> inputInARow;
            std::cout << "Enter time requirement in ms: ";
            std::cin >> timeRequirement; 
           
            Board *board = new Board(inputWidth, inputHeight, inputInARow);
            MiniMax *minimax = new MiniMax(board, bestMiniMaxMove);
            
            while ((!board->hasAWin()) && !board->hasATie()) {
                //human player turn
                if (blackFirst) {
                    int columnInput = 0;
                    std::cout << "Enter column to set value: ";
                    std::cin >> columnInput;
                    board->setValue(columnInput, black);    
                }
                //AI player turn
                else {
                    minimax->play();
                    board->setValue(bestMiniMaxMove[0], red);
                    std::cout << "My minimax move on column " << bestMiniMaxMove[0] << '\n';
                }
                board->printBoard();
                std::cout << "----------------------------\n";
                blackFirst = !blackFirst;
            }
            if (board->hasWon(88)) {
			std::cout << "Player X Won";
			}
			else if (board->hasATie()) {
				std::cout << "A tie";
			}
			else {
				std::cout << "AI O Won";
			}
            printDefault();
        }
        if (input == "2") {
            int inputWidth;
            int inputHeight;
            int inputInARow;
            double timeRequirement;
            std::string player;
            int humanPlayer;
            bool redFirst = true;
            std::cout << "Enter board Width: ";
            std::cin >> inputWidth;
            std::cout << "Enter board Height: ";
            std::cin >> inputHeight;
            std::cout << "Enter win requirement: ";
            std::cin >> inputInARow;
            std::cout << "Enter color you play black|red: ";
            std::cin.ignore();
            std::getline(std::cin, player);
            humanPlayer = getPlayerValue(redFirst,player);
            Board *board = new Board(inputWidth, inputHeight, inputInARow);
            while (!board->hasAWin() && !board->hasATie()) {
                if (redFirst) {
                    int columnInput = 0;
                    std::cout << "Red Enter column to set value: ";
                    std::cin >> columnInput;
                    board->setValue(columnInput, red);
                    board->printBoard();
                    std::cout << "Your input " << columnInput << '\n';
                }
                else {
                    int columnInput = 0;
                    std::cout << "Black Enter column to set value: ";
                    std::cin >> columnInput;
                    board->setValue(columnInput, black);
                    board->printBoard();
                    std::cout << "Your input " << columnInput<< '\n';
                }
                redFirst = !redFirst;
            }
            if (board->hasWon(88)) {
				std::cout << "X Won";
			}
			else if (board->hasATie()) {
				std::cout << "A tie";
			}
			else {
				std::cout << "O Won";
			}
            printDefault();
        }
        if (input == "q") {
            running = false;
            return 0;
        }
    }
}


/*    

    Board *testb = new Board(4,4,3);
    std::cout << testb->hasAWin() << '\n';
    testb->setValue(1, red);
    testb->setValue(1, black);
    testb->setValue(0, black);
    testb->setValue(2, red);
    testb->setValue(2, red);
    testb->setValue(2, black);
    testb->printBoard();
    std::cout << testb->hasAWin() << '\n';

    auto s = Clock::now();
    
    auto e = Clock::now();
    double difference = std::chrono::nanoseconds(e - s).count();
    
        board->setValue(0, red);
    board->setValue(0, black);
    board->setValue(0, red);
    board->setValue(1, black);
    board->setValue(1, black);
    board->setValue(1, black);
    board->setValue(1, red);
    board->setValue(2, black);
    board->setValue(2, red);

    board->setValue(4, red);
    board->setValue(4, black);
    board->setValue(4, black);
    board->setValue(4, black);
    board->setValue(4, red);
  

    */


/*
Board *generateNewState(Board *board, int player, int columnValue) {
    Board *cloneBoard = board->clone();
    cloneBoard->setValue(columnValue, player);
    return cloneBoard;
}
std::vector<Board*> *vectorOfPossibleStates(Board *board, int player) {
    std::vector<Board*> *possibleStates = new std::vector<Board*>();
    for (auto &i : *board->getColumnsNotFull()) {
        possibleStates->push_back(generateNewState(board, player, i));
    }
    return possibleStates;
}

int getPlayer(int i, int playerMe, int playerOpponent) {
    return (i % 2 == 1) ? playerMe : playerOpponent;
}

//generates every possible move between two players
void fillTree(Tree *t, Board *b, int playerMe, int playerOpponent) {
    std::vector<Tree::point*> *leafVector = new std::vector<Tree::point*>;
    std::stack<Tree::point*> *processStack = new std::stack<Tree::point*>;
    Tree::point *tempPoint = t->getRoot();
    leafVector->push_back(tempPoint);
    int depthCounter = 0;
    int player = playerOpponent;
    do {
        for (auto &i : *leafVector) {
            std::vector<Board*> *inidividualBoardMove = vectorOfPossibleStates(i->board, player);
            for (auto &x : *inidividualBoardMove) {
                tempPoint = t->addPoint(i, x);
                processStack->push(tempPoint);
            }
        }
        leafVector->clear();
        while (!processStack->empty()) {
            leafVector->push_back(processStack->top());
            processStack->pop();
        }
        std::cout << leafVector->size() << '\n';
        depthCounter++;
        player = getPlayer(depthCounter, playerMe, playerOpponent);
    } while (!leafVector->at(leafVector->size() - 1)->board->isBoardFull());
}
*/