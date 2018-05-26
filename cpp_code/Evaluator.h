#ifndef EVALUATOR_H
#define EVALUATOR_H
#include<string>
#include<vector>
#include"Board.h"

//  This class analyses the board and returns a numerical values from -10 to 10
//  0 means neutral, 10 means white advantage, -10 means black advantage
class Evaluator {
    public:
        Evaluator(std::vector<std::string> pieces);
        ~Evaluator();
};
#endif