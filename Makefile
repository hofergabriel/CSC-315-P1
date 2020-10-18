
# Usage: make target1 target2 ...

# Author: Isaac Egermier and Gabriel Hofer
# Class:  CSC 315 Data Structures & Algorithms (PA#1)
# Date:   Spring 2018

# compilation flags
CFLAGS += -O -Wall -fmax-errors=5
CXXFLAGS += $(CFLAGS) -std=c++11

# targets:


pa1:	main.cpp largeint.h isaac.cpp gabriel.cpp 
	g++ -o ../pa1 main.cpp isaac.cpp gabriel.cpp largeint.h -std=c++11



clean:
	rm -f *.o
