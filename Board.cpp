 #include<iostream>
 #include"Board.h"
 Board::Board() { }

 void Board::printBoard() {
     for (int i = 0; i < 8; i++) {
         for (int j = 0; j < 8; j++) {
            std::cout << boardState[i][j] << " ";
         }
         std::cout << std::endl;
     }
 }