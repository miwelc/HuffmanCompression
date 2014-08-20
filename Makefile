
CC = g++
FLAGS = -Wall -O3

huffman: main.cpp huffman.cpp minheap.hpp list.hpp
	$(CC) $(FLAGS) main.cpp huffman.cpp -o huffman

clean:
	rm -f huffman