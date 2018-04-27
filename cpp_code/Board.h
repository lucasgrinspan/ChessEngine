#ifndef BOARD_H
#define BOARD_H
#include<string>
#include<vector>
#include"Piece.h"
class Board {
    public:
        Board(char board[8][8]);
        //For debugging
        void printBoard();
        bool movePiece(std::string from, std::string to);
    private: 
        std::vector<Piece*> currentPieces;
        char boardState[8][8];
        bool validateMove(std::string from, std::string to);
};
#endif