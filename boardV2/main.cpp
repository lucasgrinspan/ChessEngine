#include"Board.h"
#include<vector>
#include<string>
#include<iostream>

int main() {
    std::vector<std::string> pieces   {"r00", "n01", "b02", "q03", "k04", "b05", "n06", "r07",
                                       "p10", "p11", "p12", "p13", "p14", "p15", "p16", "p17",




                                       "P60", "P61", "P62", "P63", "P64", "P65", "P66", "P67",
                                       "R70", "N71", "B72", "Q73", "K74", "B75", "N76", "R77"};
    
    std::vector<bool> movedPieces     {false, false, false, false, false, false};

    Board board(pieces, movedPieces);

    board.printBoard();
}