/*
 * main.cpp
 *
 *  Created on: Dec 29, 2015
 *      Author: fox
 */

//============================================================================
// Name        : huffman.cpp
// Author      :
// Version     :
// Description :
//============================================================================
#include <iostream>
#include <fstream>
#include "Huffman.hpp"

using namespace std;

int main(int argc, char **argv) {
	const char* in_file = argv[1];
	const char* out_file = argv[2];

	if (argc != 3) {
		cerr << argv[0] << ": requires <exe file> <input file> <output file>"
				<< endl;
		return 1;
	}
	Huffman::readFile(in_file);
	cout << "***read successfully*****" << endl;
	Huffman::ini();
	while ((Huffman::rightQueue.size() != 1 && Huffman::leftQueue.size() != 0)
			|| (Huffman::leftQueue.size() != 1
					&& Huffman::rightQueue.size() != 0)) {
		Huffman::makeNodeFromMin();
	}
	Node* root = Huffman::tree.back();
	std::cout<<"\nThis is the tree rotated by 90 degrees to the left side"<<std::endl;
	Huffman::printTree(root, 0);
	Huffman::build(root);
	Huffman::printCodeMap();

	//TODO
	std::cout<<" Percent: "<<(Huffman::length/Huffman::compLength)*100;
	return 0;

}

