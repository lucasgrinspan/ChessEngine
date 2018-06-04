#ifndef KNIGHT_H
#define KNIGHT_H
#include"../Piece.h"
class Knight : public Piece {
    public:
        Knight(std::string initPos, bool pieceColor) : Piece(initPos, pieceColor){
        };
        ~Knight() {};
        bool movePiece(std::string to);
        int getValue() {return 30;}
    private:
        std::vector<std::string> getAreasOfInfluence();
};
#endif