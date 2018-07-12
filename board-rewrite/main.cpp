#include"Board.h"
#include<array>
#include<string>
#include<iostream>
#include<stdlib.h>
#include<fstream>

int main() {
    std::array<char, 64> pieces{'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R', 
                                'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P',
                                ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                                ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                                ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                                ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
                                'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p',
                                'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'};
    
    //White king, black king, a1 rook, h1 rook, a8 rook, h8 rook
    std::array<bool, 6> movedPieces {false, false, false, false, false, false};
    std::string lastMove = "0000";
    Board board(pieces, movedPieces, lastMove);

    //  Test by using randomly generated moves
    std::ofstream logFile("move-log.txt");
    board.printBoard();
    while (true) {
        int move0, move1;
        std::string move0s, move1s;
        std::cin >> move0s;
        std::cin >> move1s;
        move0 = board.getTileNumber(move0s.at(1) - '0', move0s.at(0) - '0');
        move1 = board.getTileNumber(move1s.at(1) - '0', move1s.at(0) - '0');

        //  exit code
        if (move0 == 99) {
            break;
        }
        std::cout << move0 << ", " << move1 << std::endl;
        std::cout << board.movePiece(move0, move1) << std::endl;
        logFile << move0 << ", " << move1 << std::endl;
        board.printBoard();

        std::array<std::vector<int>, 64> possibleMoves = board.getPossibleMoves(false);
        //  Get number between 0 and 64 to decide the piece
        int randPiece = rand() % 64;
        while (possibleMoves[randPiece].size() == 0) {
            randPiece = rand() % 64;
        }
        move0 = randPiece;

        //  Get random number to decide the move
        int randMove = rand() % possibleMoves[randPiece].size();
        move1 = possibleMoves[randPiece][randMove];

        std::cout << "    " << move0 << ", " << move1 << std::endl; 
        std::cout << board.movePiece(move0, move1) << std::endl;
        logFile << "    " << move0 << ", " << move1 << std::endl;
        board.printBoard();
    }
    logFile.close();
    //  Print move of piece at x, y
    // std::array<std::vector<int>, 64> possibleMoves = board.getPossibleMoves(true);
    // int y = 2;
    // int x = 1;
    // int piece = board.getTileNumber(x, y);
    // std::cout << std::endl;
    // for (int i = 0; i < possibleMoves[piece].size(); i++) {
    //     std::cout << board.getYCoord(possibleMoves[piece][i]) << board.getXCoord(possibleMoves[piece][i]) << std::endl;
    //     //std::cout << possibleMoves[piece][i] << std::endl;
    // }
    // board.printBoard();
}