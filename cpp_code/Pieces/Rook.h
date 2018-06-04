#ifndef ROOK_H
#define ROOK_H
#include"../Piece.h"
class Rook : public Piece {
    public:
        Rook(std::string initPos, bool pieceColor) : Piece(initPos, pieceColor){
        };
        ~Rook() {};
        bool movePiece(std::string to);
        int getValue() {return 50;}
    private:
        std::vector<std::string> getAreasOfInfluence();
};
#endif