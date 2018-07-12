#include"Board.h"
#include<array>
#include<string>
#include<iostream>

int main() {
    std::array<char, 64> pieces{' ', ' ', ' ', ' ', 'K', ' ', ' ', ' ', 
                                ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                                ' ', 'p', ' ', ' ', ' ', ' ', ' ', ' ',
                                ' ', ' ', ' ', ' ', ' ', ' ', 'k', ' ',
                                ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                                ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                                ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                                'r', ' ', ' ', ' ', ' ', ' ', ' ', 'r'};
    
    //White king, black king, a1 rook, h1 rook, a8 rook, h8 rook
    std::array<bool, 6> movedPieces {false, false, false, false, false, false};
    std::string lastMove = "1329";
    Board board(pieces, movedPieces, lastMove);

    std::array<std::vector<int>, 64> possibleMoves = board.getPossibleMoves(true);
    int y = 2;
    int x = 1;
    int piece = board.getTileNumber(x, y);
    std::cout << std::endl;
    for (int i = 0; i < possibleMoves[piece].size(); i++) {
        std::cout << board.getYCoord(possibleMoves[piece][i]) << board.getXCoord(possibleMoves[piece][i]) << std::endl;
        //std::cout << possibleMoves[piece][i] << std::endl;
    }
    board.printBoard();
}