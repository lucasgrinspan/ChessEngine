#ifndef KNIGHT_H
#define KNIGHT_H
#include"../Piece.h"
class Knight : public Piece {
    public:
        Knight(std::string initPos, bool pieceColor) : Piece(initPos, pieceColor){
        };
        bool movePiece(std::string to);
    private:
        std::vector<std::string> getAreasOfInfluence();
};
#endif