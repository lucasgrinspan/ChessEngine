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
#include"../node.h"
char initBoard[8][8] = {    {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}, 
                            {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
                            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                            {'b', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
                            {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'} };

std::vector<std::string> moveList {"----"};
Board board(initBoard, moveList);

void generatePossibleMoves(const v8::FunctionCallbackInfo<v8::Value>& args){
    v8::Isolate* isolate = args.GetIsolate();
    v8::String::Utf8Value str(args[0]->ToString());
    auto piece = (const char*)(*str);

    std::vector<std::string> moves = board.getPossibleMovesOfPiece(piece);
    std::string squaresList = "";
    for (std::string move : moves) {
        squaresList += move;
    }

    char *squaresListConvert = &squaresList[0u];
    auto squares = v8::String::NewFromUtf8(isolate, squaresListConvert);
    args.GetReturnValue().Set(squares);
}
int main() {
    char initBoard[8][8] = {    {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}, 
                                {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
                                {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                {'b', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
                                {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'} };

    std::vector<std::string> moves {"----"};
    Board board(initBoard, moves);
    //std::vector<std::string> possibleMoves = board.getPossibleMoves(false);
    //Evaluator evaluator(possibleMoves);
    while (false) {
        std::string move;
        std::cin >> move;
        board.movePiece(move.substr(0,2), move.substr(2));
        board.printBoard();
        std::vector<std::string> possibleMoves = board.getPossibleMoves(true);
        int num = rand() % possibleMoves.size(); 
        std::string nextMove = possibleMoves[num];
        board.movePiece(nextMove.substr(0, 2), nextMove.substr(2));
        board.printBoard();

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
void Initialize(v8::Local<v8::Object> exports) {
    NODE_SET_METHOD(exports, "generatePossibleMoves", generatePossibleMoves);
}
NODE_MODULE(Evaluator, Initialize)