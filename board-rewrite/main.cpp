#include"Board.h"
#include<array>
#include<string>
#include<iostream>

int main() {
    std::array<char, 64> pieces{'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R', 
                                'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P',
                                ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                                ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                                'R', ' ', ' ', 'k', ' ', ' ', ' ', ' ',
                                ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                                'p', 'p', 'p', 'p', ' ', 'p', 'p', 'p',
                                'r', 'n', 'b', 'q', ' ', 'b', 'n', 'r'};
    
    std::array<bool, 6> movedPieces {false, false, false, false, false, false};
    std::string lastMove = "----";
    Board board(pieces, movedPieces, lastMove);

    std::array<std::vector<int>, 64> possibleMoves = board.getPossibleMoves(true);
    int y = 4;
    int x = 3;
    int piece = board.getTileNumber(x, y);
    for (int i = 0; i < possibleMoves[piece].size(); i++) {
        std::cout << board.getYCoord(possibleMoves[piece][i]) << board.getXCoord(possibleMoves[piece][i]) << std::endl;
    }
    board.printBoard();
    //board.movePiece(0, 1, 0);
}