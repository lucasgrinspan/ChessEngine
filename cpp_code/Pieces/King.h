#ifndef KING_H
#define KING_H
#include"../Piece.h"
class King : public Piece {
    public:
        King(std::string initPos, bool pieceColor, bool movedPieces[6]) : Piece(initPos, pieceColor){
            for (int i = 0; i < 6; i++) {
                movedPiecesBool[i] = movedPieces[i];
            }
        };
        bool movePiece(std::string to);
    private:
        std::vector<std::string> getAreasOfInfluence();
        bool movedPiecesBool[6];
};
#endif