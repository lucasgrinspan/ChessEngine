#ifndef PAWN_H
#define PAWN_H
#include"../Piece.h"
class Pawn : public Piece {
    public:
        Pawn(std::string initPos, bool pieceColor) : Piece(initPos, pieceColor){};
        ~Pawn() {};
        bool movePiece(std::string to);
        int getValue() {return 10;}
    private:
        std::vector<std::string> getAreasOfInfluence();
};
#endif