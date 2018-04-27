FLAGS = -std=c++11 -Wall -c
WARNINGS = -std=c++11 -Wall
all: program

program: main.o Board.o Pawn.o
	g++ -std=c++11 Main.o Board.o Pawn.o -o program

main.o: main.cpp
	g++ $(FLAGS) main.cpp

Board.o: Board.cpp
	g++ $(FLAGS) Board.cpp

Pawn.o: Pieces/Pawn.cpp
	g++ $(FLAGS) Pieces/Pawn.cpp

clean:
	rm -rf *o program