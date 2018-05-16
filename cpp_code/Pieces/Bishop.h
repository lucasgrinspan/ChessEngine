#ifndef BISHOP_H
#define BISHOP_H
#include"../Piece.h"
class Bishop : public Piece {
    public:
        Bishop(std::string initPos, bool pieceColor) : Piece(initPos, pieceColor){
        };
        ~Bishop() {};
        bool movePiece(std::string to);
    private:
        std::vector<std::string> getAreasOfInfluence();
};
#endif