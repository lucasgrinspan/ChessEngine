#ifndef KING_H
#define KING_H
#include"../Piece.h"
class King : public Piece {
    public:
        King(std::string initPos, bool pieceColor) : Piece(initPos, pieceColor){
        };
        ~King() {};
        bool movePiece(std::string to);
        int getValue() {return 1000;}
    private:
        std::vector<std::string> getAreasOfInfluence();
};
#endif