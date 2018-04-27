#include<iostream>
#include<string>
#include<vector>
#include"Board.h"
#include"Piece.h"
#include"Pieces/Pawn.h"
#include"Pieces/Rook.h"
#include"Pieces/Knight.h"
#include"Pieces/Bishop.h"
#include"Pieces/Queen.h"
#include"Pieces/King.h"
Board::Board(char board[8][8]) {
    //Read from parameter board
    for (int i = 0; i < 8; i++) {
         for (int j = 0; j < 8; j++) {
            //Copy to internal board object
            boardState[i][j] = board[i][j];

            //Initialize Piece objects
            if (board[i][j] == 'f') {
                Piece* rook = new Rook("11", true);
                currentPieces.push_back(rook);
            }
        }
    }
}

void Board::printBoard() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            std::cout << boardState[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << currentPieces[0]->getPosition() << std::endl;
    
}
bool Board::movePiece(std::string from, std::string to) {
    return true;
}