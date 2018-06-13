#ifndef BOARD_H
#define BOARD_H
#include<vector>
#include<string>
class Board {
    public:
        Board(std::vector<std::string> pieces, std::vector<bool> movedPieces);
        void printBoard();
    private:
        const int PIECE_ICON = 0;
        const int Y_COORD = 1;
        const int X_COORD = 2;
        const int BOARD_LENGTH = 8;

        std::vector<std::string> m_piecesList;
        std::vector<bool> m_movedPiecesList;

        int getYCoord(std::string piece);
        int getXCoord(std::string piece);
        char getIcon(std::string piece);

};
#endif