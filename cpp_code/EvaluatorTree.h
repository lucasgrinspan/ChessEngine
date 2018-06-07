#ifndef EVALUATORTREE_H
#define EVALUATORTREE_H
#include<string>
#include<vector>
#include"Board.h"

//  This class analyses the board and returns a numerical values from -100 to 100
//  0 means neutral, 100 means white advantage, -100 means black advantage
class EvaluatorTree {
    public:
        EvaluatorTree(Board& root);
        ~EvaluatorTree();
        std::string returnMove();
    private:
        int computeMinimax(int depth, Board& board, bool minimaxToggle);
        int evaluateState(Board& board);
        Board* applyNewMove(char parentBoardState[8][8], std::vector<std::string> moveList, std::string move);
        
        std::string selectedMove;
        const int SEARCH_DEPTH = 3;

};
#endif