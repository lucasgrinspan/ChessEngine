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

        //  Debugging
        void printBoard();
        void printMoves();
    private: 
        bool validateMove(Piece* piece, std::string to);
        bool inCheck(std::string square, bool color);
        int getKingStatus(bool color);
        std::vector<int> stringCoordtoInt(std::string square);
        std::vector<std::square> getPiecesAttackingKing(color);
        
        Piece* whiteKing;
        Piece* blackKing;
        std::vector<Piece*> currentPieces;
        bool movedPiecesState[6];
        char boardState[8][8];
        std::vector<std::string> moveList;
};
#endif