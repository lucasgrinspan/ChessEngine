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
        int evaluateState(Board& board);
        Board* applyNewMove(char parentBoardState[8][8], std::vector<std::string> moveList, std::string move);
        std::string selectedMove;
        const int SEARCH_DEPTH = 1;

        const int PAWN_WORTH   = 10;
        const int ROOK_WORTH   = 50;
        const int KNIGHT_WORTH = 30;
        const int BISHOP_WORTH = 30;
        const int QUEEN_WORTH  = 90;
        const int KING_WORTH   = 1000;

};
#endif