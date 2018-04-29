#ifndef BOARD_H
#define BOARD_H
#include<string>
#include<vector>
#include"Piece.h"
class Board {
    public:
        Board(char board[8][8]);
        std::vector<Piece*> getCurrentPieces();
        bool movePiece(std::string from, std::string to);
        //For debugging
        void printBoard();
    private: 
        //TODO: method for validating if space is occupied or blocked
        std::vector<Piece*> currentPieces;
        char boardState[8][8];
        std::vector<int> stringCoordtoInt(std::string square);
};
#endif