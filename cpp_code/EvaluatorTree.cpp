#include"EvaluatorTree.h"
#include"Board.h"
#include<iostream>
#include<vector>
#include<string>

EvaluatorTree::EvaluatorTree(Board& root) {
    std::vector<std::string> possibleMoves = root.getPossibleMoves(true);
    int minEval = 1000;
    std::string move;
    for (int i = 0; i < possibleMoves.size(); i++) {
        Board* newBoard = applyNewMove(root.boardState, root.getMoveList(), possibleMoves[i]);
        int evaluation = evaluateState(*newBoard);
        if (evaluation < minEval) {
            minEval = evaluation;
            selectedMove = possibleMoves[i];
        }
    }
}
EvaluatorTree::~EvaluatorTree() {}
std::string EvaluatorTree::returnMove() {
    return selectedMove;
}
Board* EvaluatorTree::applyNewMove(char parentBoardState[8][8], std::vector<std::string> moveList, std::string move) {
    Board* child = new Board(parentBoardState, moveList);
    std::string from = move.substr(0, 2);
    std::string to = move.substr(2);
    child->movePiece(from, to, true, false);
    return child;
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