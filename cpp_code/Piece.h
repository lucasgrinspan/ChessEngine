#ifndef PIECE_H
#define PIECE_H
#include<string>
#include<vector>
class Piece {
    public:
        Piece(std::string initPos, bool pieceColor) {position = initPos; color = pieceColor;}
        std::string getPosition() {return position;}
        bool getColor() {return color;}
        virtual bool movePiece(std::string to) = 0;
    private:
        std::string position;
        bool color;
        virtual std::vector<std::string> getAreasOfInfluence() = 0;
};
#endif