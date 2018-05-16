#include<iostream>
#include<string>
#include"Board.h"
#include"Piece.h"
#include"Pieces/Pawn.h"
#include"Pieces/Rook.h"
#include"Pieces/Knight.h"
#include"Pieces/Bishop.h"
#include"Pieces/Queen.h"
#include"Pieces/King.h"
#include"Pieces/Blank.h"
int main() {
    char initBoard[8][8] = {    {'R', ' ', ' ', ' ', 'K', ' ', 'N', 'R'}, 
                                {'P', 'P', 'P', 'P', ' ', 'P', 'P', 'P'},
                                {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
                                {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'} };
    //White king, black king, a1, a8, h1, h8
    bool movedPieces[6] = {false, false, false, false, false, false};
    Board board(initBoard, movedPieces);
    board.printBoard();
    board.movePiece("10", "21");
    board.printBoard();
    //TODO: change variables when king/rook moves
    //TODO: check if king is in check after every move
    //TODO: delete piece when eaten
    //TODO: en passant
    //std::cout << board.inCheck("03", false) << std::endl;
}