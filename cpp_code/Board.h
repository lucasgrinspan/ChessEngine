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
        bool movePiece(std::string from, std::string to, bool = true, bool = true);
        std::vector<std::string> getPossibleMoves(bool color);
        //std::vector<std::string> getPossibleMovesOfPiece(std::string tile);
        //  Debugging
        void printBoard();
        void printMoves();
    private: 
        bool validateMove(Piece* piece, std::string to);
        bool inCheck(std::string square, bool color);
        bool getMoveInCheck(int checkCount, bool color, Piece* selectedPiece, std::string from, std::string to);
        int getKingStatus(bool color);
        std::vector<int> stringCoordtoInt(std::string square);
        
        Piece* whiteKing;
        Piece* blackKing;
        std::vector<Piece*> currentPieces;
        bool movedPiecesState[6];
        char boardState[8][8];
        std::vector<std::string> moveList;
};
#endif