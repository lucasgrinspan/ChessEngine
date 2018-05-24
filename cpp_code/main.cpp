#include<iostream>
#include<string>
#include"Board.h"
#include"Piece.h"
#include"Evaluator.h"
#include"Pieces/Pawn.h"
#include"Pieces/Rook.h"
#include"Pieces/Knight.h"
#include"Pieces/Bishop.h"
#include"Pieces/Queen.h"
#include"Pieces/King.h"
#include"Pieces/Blank.h"
int main() {
    char initBoard[8][8] = {    {'R', ' ', ' ', ' ', 'K', ' ', ' ', 'R'}, 
                                {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
                                {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
                                {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'} };

    std::vector<std::string> moves {"----", "1111"};
    Board board(initBoard, moves); 
    std::vector<std::string> possibleMoves = board.getPossibleMoves(false);
    Evaluator evaluator(possibleMoves);
    
    /* DOCUMENTATION
    Board coordinates are given by a string where the first character is the y coord,
    and the second character is the x coord. The top left square represents "00", while
    the bottom left square represents "77".

    movePiece() takes two parameters, the current tile of the piece and the desired tile of 
    the piece
    It returns the result of the action as a bool.
    */
}