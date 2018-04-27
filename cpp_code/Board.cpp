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
            if (board[i][j] == 'r' || board[i][j] == 'R') {
                //Create position
                std::string position = std::to_string(i) + std::to_string(j);
                //True if uppercase
                Piece* rook = new Rook(position, board[i][j] == 'R');
                currentPieces.push_back(rook);
            } else if (board[i][j] == 'b' || board[i][j] == 'B') {
                std::string position = std::to_string(i) + std::to_string(j);
                Piece* bishop = new Bishop(position, board[i][j] == 'B');
                currentPieces.push_back(bishop);
            } else if (board[i][j] == 'n' || board[i][j] == 'N') {
                std::string position = std::to_string(i) + std::to_string(j);
                Piece* knight = new Knight(position, board[i][j] == 'N');
                currentPieces.push_back(knight);
            } else if (board[i][j] == 'q' || board[i][j] == 'Q') {
                std::string position = std::to_string(i) + std::to_string(j);
                Piece* queen = new Queen(position, board[i][j] == 'Q');
                currentPieces.push_back(queen);
            } else if (board[i][j] == 'k' || board[i][j] == 'K') {
                std::string position = std::to_string(i) + std::to_string(j);
                Piece* king = new King(position, board[i][j] == 'K');
                currentPieces.push_back(king);
            } else if (board[i][j] == 'p' || board[i][j] == 'P') {
                std::string position = std::to_string(i) + std::to_string(j);
                Piece* pawn = new Pawn(position, board[i][j] == 'P');
                currentPieces.push_back(pawn);
            }
        }
    }
}
std::vector<Piece*> Board::getCurrentPieces() {
    return currentPieces;
}

void Board::printBoard() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            std::cout << boardState[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << currentPieces[6]->getPosition();
}

bool Board::movePiece(std::string from, std::string to) {
    Piece* selectedPiece;
    //Iterate through the pieces and find the one being moved
    for (Piece* piece : currentPieces) {
        if (piece->getPosition().compare(from) == 0) {
            selectedPiece = piece;
        }
    }
    return selectedPiece->movePiece(to); 
}