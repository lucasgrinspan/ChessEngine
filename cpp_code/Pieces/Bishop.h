#ifndef BISHOP_H
#define BISHOP_H
#include"../Piece.h"
class Bishop : public Piece {
    public:
        Bishop(std::string initPos, bool pieceColor) : Piece(initPos, pieceColor){
        };
        ~Bishop() {};
        bool movePiece(std::string to);
        int getValue() {return 30;}
    private:
        std::vector<std::string> getAreasOfInfluence();
};
#endif