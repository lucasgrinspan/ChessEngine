#include<iostream>
#include<string>
#include"Board.h"
#include"Piece.h"
#include"Pieces/Pawn.h"
int main() {
    Board board;
    board.printBoard();
    Pawn pawn("a1", true);
    std::cout << pawn.getPosition();
}