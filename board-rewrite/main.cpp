#include"Board.h"
#include<array>
#include<string>
#include<iostream>
#include<stdlib.h>
#include<fstream>

int main() {
    bool perft = true;
    bool randGen = false;
    bool moveGen = false;
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

    //  Test by using perft testing
    if (perft) {
        //  Start with FEN string
        std::string FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w QqKk - 0 1";
        std::array<char, 64> genPieces;
        genPieces.fill(' ');
        int boardCounter = 0;
        int fenCounter;
        for (unsigned int i = 0; i < FEN.size(); i++) {
            //  FEN notation uses uppercase for white, lower for black
            if (FEN.at(i) == '/') {

            } else if (std::isdigit(FEN.at(i))) {
                boardCounter += FEN.at(i) - '0';
            } else if (FEN.at(i) == ' ') {
                fenCounter = ++i;
                break;
            } else if (std::islower(FEN.at(i))) {
                genPieces[boardCounter] = std::toupper(FEN.at(i));
                boardCounter++;
            } else {
                genPieces[boardCounter] = std::tolower(FEN.at(i));
                boardCounter++;
            }
        }
        //  Print board to check
        for (int i = 0; i < 64; i++) {
            if (i % 8 == 0) {
                std::cout << std::endl;
            }
            std::cout << genPieces[i] << " ";
        }
        std::cout << std::endl;

        bool fenActiveColor = FEN.at(fenCounter) == 'w' ? true : false;
        std::cout << fenActiveColor << std::endl;

        //  Generate the moved pieces list
        std::array<bool, 6> fenMovedPieces;
        fenMovedPieces.fill(true);
        fenCounter += 2;
        while (FEN.at(fenCounter) != ' ') {
            if (FEN.at(fenCounter) == '-') {
                //  No castling possible, everything is true
                fenCounter += 2;
                break;
            }
            if (FEN.at(fenCounter) == 'K') {
                fenMovedPieces[0] = false;
                fenMovedPieces[3] = false;
            } else if (FEN.at(fenCounter) == 'Q') {
                fenMovedPieces[0] = false;
                fenMovedPieces[2] = false;
            } else if (FEN.at(fenCounter) == 'k') {
                fenMovedPieces[1] = false;
                fenMovedPieces[5] = false;
            } else if (FEN.at(fenCounter) == 'q') {
                fenMovedPieces[1] = false;
                fenMovedPieces[4] = false;
            }
            fenCounter++;
        }
        //  Print moved pieces list
        for (bool result : fenMovedPieces) {
            std::cout << result;
        }
        std::cout << std::endl;

        //  Get the en passant target (last move)
        std::string fenLastMove;
        if (FEN.at(++fenCounter) == '-') {
            fenCounter += 2;
            fenLastMove = "0000";
        } else {
            //  Convert algebraic notation to tile number notation
            int column = FEN.at(fenCounter++) - '1';
            int row = FEN.at(fenCounter++) - 'a';
            fenCounter++;
            //  The rows are in reverse order
            row = (7 - row);
            
            //  The actual last move is the tile behind the tile number
            int modifier = fenActiveColor ? 1 : -1;
            row = row + modifier;

            int row0 = row + (2 * modifier);

            int tileNum0 = row0 * 8 + column;
            int tileNum1 = row * 8 + column;

            fenLastMove = std::to_string(tileNum0) + std::to_string(tileNum1);
        }
        std::cout << fenLastMove << std::endl;

        //  Get the halfmove counter 
        std::string fenHalfMoveCounter;
        fenHalfMoveCounter.push_back(FEN.at(fenCounter++));
        if (FEN.at(fenCounter) != ' ') {
            fenHalfMoveCounter.push_back(FEN.at(fenCounter));
        }
        std::cout << fenHalfMoveCounter << std::endl;
    }
    //  Test by using randomly generated moves
    if (randGen) {    
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
    }
    //  Test by printing move of piece at x, y
    if (moveGen) {
        std::array<std::vector<int>, 64> possibleMoves = board.getPossibleMoves(true);
        int y = 2;
        int x = 1;
        int piece = board.getTileNumber(x, y);
        std::cout << std::endl;
        for (unsigned int i = 0; i < possibleMoves[piece].size(); i++) {
            std::cout << board.getYCoord(possibleMoves[piece][i]) << board.getXCoord(possibleMoves[piece][i]) << std::endl;
            //std::cout << possibleMoves[piece][i] << std::endl;
        }
        board.printBoard();
    }
}