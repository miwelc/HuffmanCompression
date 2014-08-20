/*
 * Created by Miguel Canton Cortes, 2014
 */
 
#include "huffman.h"

bool Huffman::HuffNode::operator<(const HuffNode& node) const {
	if(freq < node.freq)
		return true;
	if(freq > node.freq)
		return false;
	if(val < node.val)
		return true;
	if(val > node.val)
		return false;
	
	return false; // ==
}

bool Huffman::HuffNode::operator>(const HuffNode& node) const {
	return node < *this;
}

void Huffman::deleteSubtree(const HuffNode& node) {
	if(node.left) {
		deleteSubtree(*node.left);
		delete node.left;
	}
	if(node.right) {
		deleteSubtree(*node.right);
		delete node.right;
	}
}

void Huffman::createTree(unsigned* freqs, HuffNode& root) {
	MinHeap<HuffNode> minHeap;
	HuffNode node;
	
	node.left = node.right = 0;
	for(int i = 0; i < 256; i++) {
		if(freqs[i]) {
			node.freq = freqs[i];
			node.val = i;
			minHeap.insert(node);
		}
	}
	
	while(minHeap.size() > 1) {
		//R-L or L-R?
		HuffNode* nodeR = new HuffNode;
		HuffNode* nodeL = new HuffNode;
		*nodeR = minHeap.top(); minHeap.pop();
		*nodeL = minHeap.top(); minHeap.pop();
		
		node.freq = nodeL->freq + nodeR->freq;
		if(nodeL->val < nodeR->val)
			node.val = nodeL->val;
		else
			node.val = nodeR->val;
		node.left = nodeL;
		node.right = nodeR;
		
		minHeap.insert(node);
	}
	
	root = minHeap.top(); minHeap.pop();
}

void Huffman::createCodeTable(const HuffNode& root, List<bool>* table, List<bool> code) {
	if(root.left == 0 && root.right == 0)//Leaf
		table[root.val] = code;
	
	code.insert(false);
	
	if(root.left)
		createCodeTable(*root.left, table, code);
	
	if(root.right) {
		*code.last() = true;
		createCodeTable(*root.right, table, code);
	}
}

void Huffman::compress(istream &in, ostream &out) {
	unsigned char b, outByte;
	short nBits;
	unsigned frequencies[256] = {0};
	HuffNode root;
	List<bool> table[256];
	
	while(in.read((char*)&b, 1))
		frequencies[b]++;
	
	createTree(frequencies, root);
	createCodeTable(root, table);
	deleteSubtree(root); // We don't need it anymore
	
	out.write("HUFFMA5", 8);
	for(int i = 0; i < 256; i++)
		out.write((char*)&frequencies[i], 4);
	
	in.clear();
	in.seekg(0);
	nBits = 0;
	while(in.read((char*)&b, 1)) {
		for(List<bool>::iterator it = table[b].begin(); it != table[b].end(); it++) {
			if(*it)
				outByte |= (1<<nBits);
			else
				outByte &= ~(1<<nBits);
			
			if(++nBits == 8) {
				nBits = 0;
				out.write((char*)&outByte, 1);
			}
		}
	}
	
	if(nBits > 0) { //Padding
		outByte &= (0xFF>>(8-nBits));
		out.write((char*)&outByte, 1);
	}
}

void Huffman::decompress(istream &in, ostream &out) {
	unsigned char b;
	char cookie[8];
	unsigned frequencies[256] = {0};
	unsigned frequenciesPrinted[256] = {0};
	HuffNode root, *node;
	
	in.read(cookie, 8);
	
	for(int i = 0; i < 256; i++)
		in.read((char*)&frequencies[i], 4);
	
	createTree(frequencies, root);
	
	node = &root;
	while(in.read((char*)&b, 1)) {
		for(int i = 0; i < 8; i++) {
			if(b & (1<<i))
				node = node->right;
			else
				node = node->left;
			if(node->left == 0 && node->right == 0) {
				//Fix last_character<->padding issue
				if(++frequenciesPrinted[node->val] <= frequencies[node->val])
					out.write((char*)&node->val, 1);
				node = &root;
			}
		}
	}
	
	deleteSubtree(root);
}





