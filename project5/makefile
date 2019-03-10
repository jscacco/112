all: puzzle

puzzle: sudoku.o  Stack.o 
		c++ -o puzzle sudoku.o Stack.o

sudoku.o: sudoku.cc  Stack.h 
		c++ -c sudoku.cc

Stack.o: Stack.cc Stack.h
		c++ -c Stack.cc
