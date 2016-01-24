#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <queue>
#include "board.h"

class Tree {
public:
    struct point {
        Board *board;
        std::vector<point> *pointChildren = new std::vector<point>;
    };

    //appends a new point to the old point and sets values
    point *addPoint(point *p, Board *board) {
        point *newPoint = new point();
        newPoint->board = board;
        (*p).pointChildren->push_back(*newPoint);
        return newPoint;
    }

    //recursivly itterate through the tree and print values; visual representation of a tree
    void itterateNTree(point *tree, std::vector<Board> &pointVector, int depth) {
        if (tree != NULL) {
            pointVector.push_back(*tree->board);
            for (int d = 0; d < depth; d++) {
                std::cout << '\t';
            }
            tree->board->printBoard();
            std::cout <<'\n';
            for (auto &i : *tree->pointChildren) {
                itterateNTree(&i, pointVector,depth+1);
            }
        }
    }
    void printTree(point *tree) {
        std::vector<Board> pointVector;
        itterateNTree(tree, pointVector,0);
    }

    //get all points with search value are found
    void dfsALL(point *tree, Board *searchValue,std::vector<point*> *ptr) {
        if (tree != NULL) {
            if (tree->board == searchValue) {
                ptr->push_back(tree);
            }
            for (auto &i : *tree->pointChildren) {
                dfsALL(&i, searchValue,ptr);
            }
        }
    }

    std::vector<point*> *depthFirstSearchAll (Board *searchTerm) {
        std::vector<point*> *ptr = new std::vector<point*>();       
        dfsALL(getRoot(), searchTerm,ptr);
        return ptr;
    }

    inline point *getRoot() {
        return root;
    }
private:
    point *root = new point();
};