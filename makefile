a.out: Board.o Coordinator.o HumanPlayer.o ComputerPlayer.o Validator.o main.o
	g++ Board.o Coordinator.o HumanPlayer.o ComputerPlayer.o Validator.o main.o

Validator.o: Validator.cpp Validator.hpp Board.hpp
	g++ -std=c++0x -c Validator.cpp

HumanPlayer.o: HumanPlayer.cpp HumanPlayer.hpp Board.hpp Validator.hpp
	g++ -std=c++0x -c HumanPlayer.cpp

ComputerPlayer.o: ComputerPlayer.cpp ComputerPlayer.hpp Board.hpp Validator.hpp
	g++ -std=c++0x -c ComputerPlayer.cpp

Coordinator.o: Coordinator.cpp Coordinator.hpp Board.hpp
	g++ -std=c++0x -c Coordinator.cpp

Board.o: Board.cpp Board.hpp BoardExceptions.hpp
	g++ -std=c++0x -c Board.cpp

main.o: main.cpp BoardExceptions.hpp Coordinator.hpp
	g++ -std=c++0x -c main.cpp


