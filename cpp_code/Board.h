#ifndef BOARD_H
#define BOARD_H
#include<string>
#include<vector>
#include"Piece.h"
#include"Pieces/King.h"
class Board {
    public:
        Board(char board[8][8], std::vector<std::string> moves);
        std::vector<Piece*> getCurrentPieces();
        bool movePiece(std::string from, std::string to);
        std::vector<std::string> getPossibleMoves(bool color);

        //Debugging
        void printBoard();
        void printMoves();
    private: 
        bool validateMove(Piece* piece, std::string to);
        std::vector<Piece*> currentPieces;
        //Returns true if square is in check by color
        bool inCheck(std::string square, bool color);
        //True if the piece moved
        bool movedPiecesState[6];
        char boardState[8][8];
        std::vector<int> stringCoordtoInt(std::string square);
        std::vector<std::string> moveList;
};
#endif