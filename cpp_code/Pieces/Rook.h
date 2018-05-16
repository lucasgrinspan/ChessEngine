#ifndef ROOK_H
#define ROOK_H
#include"../Piece.h"
class Rook : public Piece {
    public:
        Rook(std::string initPos, bool pieceColor) : Piece(initPos, pieceColor){
        };
        ~Rook() {};
        bool movePiece(std::string to);
    private:
        std::vector<std::string> getAreasOfInfluence();
};
#endif