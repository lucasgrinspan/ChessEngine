#ifndef BLANK_H
#define BLANK_H
#include"../Piece.h"
class Blank : public Piece {
    public:
        Blank(std::string initPos, bool pieceColor) : Piece(initPos, pieceColor){
        };
        ~Blank() {};
        bool movePiece(std::string to);
    private:
        std::vector<std::string> getAreasOfInfluence();
};
#endif