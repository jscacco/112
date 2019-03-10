compress: compress.o PriorityQueue.o 
	c++ -g -o compress compress.cc PriorityQueue.cc

compress.o: compress.cc PriorityQueue.h
	c++ -g -c compress.cc

PriorityQueue.o: PriorityQueue.cc PriorityQueue.h
	c++ -g -c PriorityQueue.cc
