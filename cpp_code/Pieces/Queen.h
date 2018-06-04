#ifndef QUEEN_H
#define QUEEN_H
#include"../Piece.h"
class Queen : public Piece {
    public:
        Queen(std::string initPos, bool pieceColor) : Piece(initPos, pieceColor){
        };
        ~Queen() {};
        bool movePiece(std::string to);
        int getValue() {return 90;}
    private:
        std::vector<std::string> getAreasOfInfluence();
};
#endif