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
    char initBoard[8][8] = {    {'R', ' ', ' ', ' ', 'K', ' ', ' ', 'R'}, 
                                {'P', 'P', 'P', 'P', 'P', 'P', ' ', 'P'},
                                {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                {'p', 'p', 'p', 'p', 'p', 'p', 'P', 'p'},
                                {'r', 'n', 'b', 'q', 'k', 'b', ' ', 'r'} };
    //White king, black king, a1, a8, h1, h8
    std::vector<std::string> moves {"----", "6747"};
    bool movedPieces[6] = {false, false, false, false, false, false};
    Board board(initBoard, movedPieces, moves);
    //board.printMoves();
    //board.movePiece("26", "36");
    board.printBoard();
    board.movePiece("04", "02");

    board.printMoves();

    /* DOCUMENTATION
    Board coordinates are given by a string where the first character is the y coord,
    and the second character is the x coord. The top left square represents "00", while
    the bottom left square represents "77".

    movePiece() takes three parameters, the current tile of the piece, the desired tile of 
    the piece, and an integer in case that a pawn promotion occurs.
    It returns the result of the action as a bool.
    */

    //TODO: change variables when king/rook moves
    //TODO: check if king is in check after every move
}