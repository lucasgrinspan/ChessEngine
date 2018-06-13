FLAGS = -std=c++11 -Wall -c
DEBUG = -g
WARNINGS = -std=c++11 -Wall
all: program

program: test.o Board.o Pieces.o EvaluatorTree.o
	g++ -std=c++11 test.o Board.o EvaluatorTree.o Bishop.o King.o Knight.o Pawn.o Queen.o Rook.o Blank.o -o program

test.o: test.cpp
	g++ $(FLAGS) test.cpp

Board.o: Board.cpp
	g++ $(FLAGS) Board.cpp

Pieces.o: Pieces/Pawn.cpp Pieces/Rook.cpp Pieces/Bishop.cpp Pieces/Knight.cpp Pieces/Queen.cpp Pieces/King.cpp Pieces/Blank.cpp
	g++ $(FLAGS) Pieces/Pawn.cpp Pieces/Rook.cpp Pieces/Bishop.cpp Pieces/Knight.cpp Pieces/Queen.cpp Pieces/King.cpp Pieces/Blank.cpp

EvaluatorTree.o: EvaluatorTree.cpp
	g++ $(FLAGS) EvaluatorTree.cpp

clean:
	rm -rf *o program