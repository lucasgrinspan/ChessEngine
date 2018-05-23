#ifndef PIECE_H
#define PIECE_H
#include<string>
#include<vector>
class Piece {
    public:
        Piece(std::string initPos, bool pieceColor) {position = initPos; color = pieceColor;}
        virtual ~Piece() {};
        std::string getPosition() {return position;}
        void setPosition(std::string to) {position = to;}
        bool getColor() {return color;}
        std::string toStrCoord(int x, int y) {
            return std::to_string(y) + std::to_string(x);
        }
        bool withinBounds(int x, int y) {
            return (((x >= 0) && (x <= 7)) && ((y >= 0) && (y <= 7)));
        }
        virtual bool movePiece(std::string to) = 0;
        virtual std::vector<std::string> getAreasOfInfluence() = 0;
    private:
        std::string position;
        bool color;
        //  bool inDanger;
};
#endif