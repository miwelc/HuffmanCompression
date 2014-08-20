/*
 * Created by Miguel Canton Cortes, 2014
 */

#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_

#include <fstream>
#include "minheap.hpp"
#include "list.hpp"

using namespace std;

class Huffman {
	private:
		class HuffNode {
			public:
				unsigned freq;
				unsigned char val;
				HuffNode* left;
				HuffNode* right;
				HuffNode() : freq(0), val(0), left(0), right(0) {};
				bool operator<(const HuffNode& node) const;
				bool operator>(const HuffNode& node) const;
		};
		void deleteSubtree(const HuffNode& node);
		void createTree(unsigned* freqs, HuffNode& root);
		void createCodeTable(const HuffNode& root, List<bool>* table, List<bool> code = List<bool>());
		
	public:
		Huffman() {};
		~Huffman() {};
		void compress(istream &in, ostream &out);
		void decompress(istream &in, ostream &out);
};

#endif