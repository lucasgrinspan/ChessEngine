#ifndef BOARD_H
#define BOARD_H
#include<array>
#include<string>
#include<vector>
class Board {
    public:
        Board(std::array<char, 64> pieces, std::array<bool, 6> movedPieces, std::string lastMove, int repCounter);
        void printBoard();
        void printBitBoard(std::array<bool, 64> board);
        void undo();
        
        bool movePiece(int tileNum0, int tileNum1);
        std::array<std::vector<int>, 64> getPossibleMoves(bool color);
        
        int getYCoord(int tileNumber);
        int getXCoord(int tileNumber);
        int getTileNumber(int x, int y);
        char pieceAt(int tileNumber);
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

        //  Consts used for accessing the moved pieces array
        const int WHITE_KING = 0;
        const int BLACK_KING = 1;
        const int A1_ROOK = 2;
        const int H1_ROOK = 3;
        const int A8_ROOK = 4;
        const int H8_ROOK = 5;

        //  Consts used for starting piece positions
        //  Must be known at compile time
        #define A1_ROOK_POS 56
        #define H1_ROOK_POS 63
        #define A8_ROOK_POS 0
        #define H8_ROOK_POS 7

        int kingPositionWhite = 60;
        int kingPositionBlack = 4;

        std::array<char, 64> m_board;
        std::array<char, 64> m_prevBoard;
        std::array<bool, 64> m_attackedSquares;
        std::array<bool, 64> m_captureMask;
        std::array<bool, 64> m_blockMask;
        std::array<bool, 64> m_pinnedMask;
        std::array<bool, 6> m_movedPiecesList;
        std::array<bool, 6> m_prevMovedPiecesList;
        int m_lastMove0;
        int m_lastMove1;
        int m_prevLastMove0;
        int m_prevLastMove1;
        int m_3FoldRepCounter = 1;
        int m_50RepCounter = 1;

        bool isWhite(char piece);
        bool isOpponentPiece(char piece, bool color);
        bool withinBounds(int x, int y);
        void generateAttackedSquares(bool color);
        void generateBlockMask(bool color, int checkLocation);
        int calculatePin(bool color, int limit, int increment, int initialPos, char validPinner);

        void updateKingPositions();
        void hideKing(bool color);
        void resetKing(bool color);

        bool checkMask(int tileNumber);
        bool isInCheck(int tileNumber);

        std::vector<int> getStraightLineMoves(int tileNumber, bool color, int length, bool influence);
        std::vector<int> getDiagonalMoves(int tileNumber, bool color, int length, bool influence);
        std::vector<int> getKnightMoves(int tileNumber, bool color, bool influence);
        std::vector<int> getPawnMoves(int tileNumber, bool color, bool influence);
        std::vector<int> getKingMoves(int tileNumber, bool color, bool influence);

        std::array<int, 2> getCheckLocations(bool color);
        std::array<std::vector<int>, 64> generatePinnedMask(bool color);

};
#endif