#include"EvaluatorTree.h"
#include"Board.h"
#include<iostream>
#include<vector>
#include<string>

EvaluatorTree::EvaluatorTree(Board& root) {
    std::vector<std::string> possibleMoves = root.getPossibleMoves(false);
    
}
EvaluatorTree::~EvaluatorTree() {}
Board& EvaluatorTree::applyNewMove(Board& parent, std::string move) {

}
int EvaluatorTree::evaluateState(Board& board) {
    int evaluation = 0;
    std::vector<Piece*> currentPieces = board.getCurrentPieces();
    for (Piece* piece : currentPieces) {
        //  Substract if black piece and add if white piece
        int modifier = piece->getColor() ? -1 : 1;
        evaluation += (piece->getValue() * modifier);
    }
    return evaluation;
}