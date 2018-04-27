#ifndef PAWN_H
#define PAWN_H
#include"../Piece.h"
class Pawn : public Piece {
    public:
        bool movePiece(std::string to);
    private:
        std::vector<std::string> getAreasOfInfluence();
};
#endif