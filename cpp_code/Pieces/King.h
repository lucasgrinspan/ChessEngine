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
        ~King() {};
        bool movePiece(std::string to);
        void setMovedPiecesBool(bool movedPieces[6]);
    private:
        bool movedPiecesBool[6];
        std::vector<std::string> getAreasOfInfluence();
};
#endif