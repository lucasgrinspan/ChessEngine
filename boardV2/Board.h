#ifndef BOARD_H
#define BOARD_H
#include<array>
#include<string>
#include<vector>
class Board {
    public:
        Board(std::array<char, 64> pieces, std::array<bool, 6> movedPieces, std::string lastMove);
        void printBoard();

        bool movePiece(int tileNum0, int tileNum1, int promotionCase);
        std::array<std::vector<int>, 64> getPossibleMoves(bool color);
        
        int getYCoord(int tileNumber);
        int getXCoord(int tileNumber);
        int getTileNumber(int x, int y);
    private:
        const int PIECE_ICON = 0;
        const int POSITION = 1;
        const int BOARD_LENGTH = 8;
        const int NUM_TILES = 64;
        const int KING_RANGE = 2;
        const int MAX_RANGE = 8;
        const int NUM_KNIGHT_MOVES = 8;
        const bool MOVEMENT = false;
        const bool INFLUENCE = true;

        std::array<char, 64> m_board;
        std::array<bool, 64> m_attackedSquares;
        std::array<bool, 6> m_movedPiecesList;
        std::string m_lastMove;

        bool isWhite(char piece);
        bool isOpponentPiece(char piece, bool color);
        bool withinBounds(int x, int y);
        void generateAttackedSquares(bool color);

        bool isInCheck(int tileNumber);
        std::string getPiece(int tileNum);

        //  TODO: remove range parameter from straight and diagonal 
        std::vector<int> getStraightLineMoves(int tileNumber, bool color, int length, bool influence);
        std::vector<int> getDiagonalMoves(int tileNumber, bool color, int length, bool influence);
        std::vector<int> getKnightMoves(int tileNumber, bool color, bool influence);
        std::vector<int> getPawnMoves(int tileNumber, bool color, bool influence);
        std::vector<int> getKingMoves(int tileNumber, bool color, bool influence);

};
#endif