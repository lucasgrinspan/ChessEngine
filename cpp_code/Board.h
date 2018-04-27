#ifndef BOARD_H
#define BOARD_H
#include<string>
class Board {
    public:
        Board();
        //For debugging
        void printBoard();
        bool movePiece(std::string from, std::string to);
    private: 
        char boardState[8][8] = {   {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}, 
                                    {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
                                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                                    {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
                                    {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'} };
        bool validateMove(std::string from, std::string to);
};
#endif