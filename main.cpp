/*
 * Created by Miguel Canton Cortes, 2014
 */

#include "huffman.h"

#include <iostream>
#include <ctime>

using namespace std;

int main(int argc, char** argv) {
	Huffman hm;
	
	if(argc == 1) {
		hm.compress(cin, cout);
	}
	else if(argc == 2 && argv[1][0] == '-'
					  && argv[1][1] == 'd'
					  && argv[1][2] == '\0') {
		hm.decompress(cin, cout);
	}

	return 0;
}
