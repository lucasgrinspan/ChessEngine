FLAGS = -std=c++11 -Wall -c

all: program

program: main.o Board.o
	g++ -std=c++11 main.o Board.o -o program

main.o: main.cpp
	g++ $(FLAGS) main.cpp

Board.o: board.cpp
	g++ $(FLAGS) board.cpp

clean:
	rm -rf *o program