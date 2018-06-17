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
        std::array<std::vector<int>, 64> getPossibleMoves();
    private:
        const int PIECE_ICON = 0;
        const int POSITION = 1;
        const int BOARD_LENGTH = 8;
        const int NUM_TILES = 64;
        const int KING_RANGE = 2;
        const int MAX_RANGE = 8;

        std::array<char, 64> m_board;
        std::array<bool, 6> m_movedPiecesList;
        std::string m_lastMove;

        int getYCoord(int tileNumber);
        int getXCoord(int tileNumber);
        int getTileNumber(int x, int y);
        bool isWhite(char piece);

        std::string getPiece(int tileNum);

        std::vector<int> getPawnMoves(int x, int y);
        std::vector<int> getStraightLineMoves(int tileNumber, bool color, int length);
        std::vector<int> getDiagonalMoves(int tileNumber, bool color, int length);
        std::vector<int> getKnightMoves(int x, int y);
        std::vector<int> getBishopMoves(int x, int y);
        std::vector<int> getQueenMoves(int x, int y);
        std::vector<int> getKingMoves(int x, int y);
};
#endif