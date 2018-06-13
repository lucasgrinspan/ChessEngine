#include"Board.h"
#include<string>
#include<vector>
#include<iostream>
Board::Board(std::vector<std::string> pieces, std::vector<bool> movedPieces) {
    m_piecesList = pieces;
    m_movedPiecesList = movedPieces;
}
int Board::getXCoord(std::string piece) {
    return piece.at(X_COORD) - '0';
}
int Board::getYCoord(std::string piece) {
    return piece.at(Y_COORD) - '0';
}
char Board::getIcon(std::string piece) {
    return piece.at(PIECE_ICON);
}
void Board::printBoard() {
    for (int i = 0; i < BOARD_LENGTH; i++) {
        for (int j = 0; j < BOARD_LENGTH; j++) {
            for (int k = 0; k < m_piecesList.size(); k++) {
                if ((i == getYCoord(m_piecesList[k])) &&
                   (j == getXCoord(m_piecesList[k]))) {
                    std::cout << getIcon(m_piecesList[k]) << " ";
                    break;
                }
                if (k == m_piecesList.size() - 1) {
                    std::cout << "  ";
                }
            }
        }
        std::cout << std::endl;
    }
}