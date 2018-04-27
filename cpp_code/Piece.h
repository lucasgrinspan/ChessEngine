#ifndef PIECE_H
#define PIECE_H
#include<string>
#include<vector>
class Piece {
    public:
        Piece(std::string initPos, bool pieceColor) {position = initPos; color = pieceColor;}
        std::string returnPosition() {return position;}
        std::string position;
        bool color;
        virtual bool movePiece(std::string to) = 0;
        virtual std::vector<std::string> getAreasOfInfluence() = 0;
};
#endif