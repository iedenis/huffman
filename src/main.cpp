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
	string out_file=argv[2];

	Huffman h;

	if (argc != 3) {
		cerr << argv[0] << ": requires <exe file> <input file> <output file>"
				<< endl;
		return 1;
	}
	Huffman::readFile(in_file);
	cout << "read successfully" << endl;
				std::map<char, int>::iterator it = Huffman::accurences.begin();
				while (it != Huffman::accurences.end()){
					std::cout << it->first << " " << it->second<<endl;
					it++;
				}
	return 0;

}

