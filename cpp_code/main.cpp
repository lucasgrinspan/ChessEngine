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
    char initBoard[8][8] = {    {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}, 
                                {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
                                {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
                                {'r', ' ', ' ', ' ', 'k', 'b', 'n', 'r'} };
    //White king, black king, a1, a8, h1, h8
    bool movedPieces[6] = {false, false, false, false, false, false};
    Board board(initBoard, movedPieces);
    board.printBoard();
    board.movePiece("74", "72");
    board.printBoard();
}