#ifndef KING_H
#define KING_H
#include"../Piece.h"
class King : public Piece {
    public:
        King(std::string initPos, bool pieceColor) : Piece(initPos, pieceColor){
        };
        bool movePiece(std::string to);
    private:
        std::vector<std::string> getAreasOfInfluence();
};
#endif