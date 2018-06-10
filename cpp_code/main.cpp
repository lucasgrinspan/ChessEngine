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
#include"../node.h"
char initBoard[8][8] = {    {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}, 
                            {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
                            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                            {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
                            {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'} };

std::vector<std::string> moveList {"----"};
Board board(initBoard, moveList);

void generatePossibleMoves(const v8::FunctionCallbackInfo<v8::Value>& args){
    v8::Isolate* isolate = args.GetIsolate();
    std::vector<std::string> moves = board.getPossibleMoves(false);
    v8::Local<v8::Array> v8MoveList = v8::Array::New(isolate);

    for (unsigned int i = 0; i < moves.size(); i++) {
        char *MoveCharArr = &moves[i][0u];
        auto v8MoveString = v8::String::NewFromUtf8(isolate, MoveCharArr);
        v8MoveList->Set(i, v8MoveString);
    }
    
    args.GetReturnValue().Set(v8MoveList);
}
void updateBoard(const v8::FunctionCallbackInfo<v8::Value>& args) {
    //  Read args from js
    v8::Isolate* isolate = args.GetIsolate();
    v8::String::Utf8Value str(args[0]->ToString());
    auto moveChar = (const char*)(*str);
    //  Convert to std::string for the movePiece() function
    std::string move(moveChar);
    //  Remove undefined chars at end
    for (int i = 0; i < 9; i++) {
        move.erase(move.size() - 1);
    }
    std::cout << move << std::endl;
    bool result = board.movePiece(move.substr(0,2), move.substr(2), false, true);
    //  Create js bool type from result and return it
    v8::Local<v8::Boolean> v8Result = v8::Boolean::New(isolate, result);
    args.GetReturnValue().Set(v8Result); 
}
void getOpponentMove(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Isolate* isolate = args.GetIsolate();
    EvaluatorTree evaluator(board);
    std::string nextMove = evaluator.returnMove();

    board.movePiece(nextMove.substr(0, 2), nextMove.substr(2), false, true);

    char *MoveCharArr = &nextMove[0u];
    auto v8MoveString = v8::String::NewFromUtf8(isolate, MoveCharArr);

    std::cout << nextMove << std::endl;

    args.GetReturnValue().Set(v8MoveString);
}
void Initialize(v8::Local<v8::Object> exports) {
    NODE_SET_METHOD(exports, "generatePossibleMoves", generatePossibleMoves);
    NODE_SET_METHOD(exports, "updateBoard", updateBoard);
    NODE_SET_METHOD(exports, "getOpponentMove", getOpponentMove);
}
NODE_MODULE(Evaluator, Initialize)