#ifndef PIECE_H
#define PIECE_H
#include<string>
#include<vector>
class Piece {
    public:
        std::string position;
        virtual bool movePiece(std::string to) = 0;
    private:
        virtual std::vector<std::string> getAreasOfInfluence();
};
#endif