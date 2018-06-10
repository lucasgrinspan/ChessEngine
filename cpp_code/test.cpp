#include<iostream>
#include<string>
#include"Board.h"
#include"Piece.h"
#include"EvaluatorTree.h"
#include"Pieces/Pawn.h"
#include"Pieces/Rook.h"
#include"Pieces/Knight.h"
#include"Pieces/Bishop.h"
#include"Pieces/Queen.h"
#include"Pieces/King.h"
#include"Pieces/Blank.h"
int main() {
    char mainBoardArr[8][8] = {{'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}, 
                            {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
                            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
                            {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'} };

    std::vector<std::string> moves {"----"};
    Board mainBoard(mainBoardArr, moves);
    std::vector<std::string> presetMoves{"6444", "7655", "7152", "6757", "6343", "7236", "3645", "4435", "3524"};
    //std::vector<std::string> possibleMoves = board.getPossibleMoves(false);
    //Evaluator evaluator(possibleMoves);
    bool playing = true;
    bool usePresets = true;
    int moveCounter = 0;
    while (playing) {
        if (usePresets) {
            if (moveCounter < presetMoves.size()) {
                mainBoard.movePiece(presetMoves[moveCounter].substr(0, 2), presetMoves[moveCounter].substr(2), false, true);
            } else {
                playing = false;
            }
        } else {
            std::string move;
            std::cin >> move;
            mainBoard.movePiece(move.substr(0, 2), move.substr(2), false, true);
        }
        mainBoard.printBoard();
        EvaluatorTree eval(mainBoard);
        std::string opponentMove = eval.returnMove();
        std::cout << opponentMove << std::endl;
        mainBoard.movePiece(opponentMove.substr(0, 2), opponentMove.substr(2), false, true);
        mainBoard.printBoard();
        
        moveCounter++;
    }
    //TODO: add check validation for pieces being taken
    /* DOCUMENTATION
    Board coordinates are given by a string where the first character is the y coord,
    and the second character is the x coord. The top left square represents "00", while
    the bottom left square represents "77".

    movePiece() takes two parameters, the current tile of the piece and the desired tile of 
    the piece
    It returns the result of the action as a bool.
    */
}