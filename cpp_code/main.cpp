#include<iostream>
#include"Board.h"
#include"Piece.h"
#include"Pieces/Pawn.h"
int main() {
    Board board;
    board.printBoard();
    Piece* pawn = new Pawn("a1", true);
}