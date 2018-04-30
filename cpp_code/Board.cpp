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
#include"Pieces/Blank.h"

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
            } else if (board[i][j] == ' ') {
                std::string position = std::to_string(i) + std::to_string(j);
                Piece* blank = new Blank(position, true);
            }
        }
    }
}
std::vector<int> Board::stringCoordtoInt(std::string square) {
    std::vector<int> intChords;
    intChords.push_back(square.at(1) - '0');
    intChords.push_back(square.at(0) - '0');
    return intChords;
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
}
bool Board::validateMove(Piece* piece, std::string to) {
    bool color = piece->getColor();

}
bool Board::movePiece(std::string from, std::string to) {
    Piece* selectedPiece;
    //Iterate through the pieces and find the one being moved
    for (Piece* piece : currentPieces) {
        if (piece->getPosition().compare(from) == 0) {
            selectedPiece = piece;
        }
    }
    //TODO: find way to check if piece is blocked
    bool result = selectedPiece->movePiece(to); 
    if (result) {
        selectedPiece->setPosition(to);
        int x = stringCoordtoInt(from)[0];
        int y = stringCoordtoInt(from)[1];

        char pieceLetter = boardState[y][x];
        boardState[y][x] = ' ';
        int x1 = stringCoordtoInt(to)[0];
        int y1 = stringCoordtoInt(to)[1];
        boardState[y1][x1] = pieceLetter;
    }
    return result;
}