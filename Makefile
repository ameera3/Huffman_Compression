# Change the CXX variable assignment at your own risk.
CXX ?= g++ 
CXXFLAGS=-std=c++11 -Wall 
LDFLAGS=-g

all: huffman 

huffman: HCTree.o

HCTree.o: HCTree.hpp HCNode.hpp  

clean:
	rm -f huffman *.o core* *~

