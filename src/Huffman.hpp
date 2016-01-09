#ifndef HUFFMAN_HPP_
#define HUFFMAN_HPP_

#include <map>
#include <iostream>
#include <string>
#include <queue>
#include "Node.hpp"
#include <list>
#include <fstream>

class Huffman {
private:
	static std::map<char, int> occurences_map;
	static std::map<char, std::vector<bool> > code_map;

public:
	static double compLength;
	static int length;
	static std::ofstream wFile;
	static std::vector<bool> word_code;

	static std::list<Node*> tree;

	static std::queue<Node*> leftQueue;
	static std::queue<Node*> rightQueue;

	static Node* makeNodeFromMin();
	static void readFile(const char*);
	static void initialize(const char*);
	static void count(std::string&);
	static void ini();
	static void printTree(Node*, int);
	static void build(Node*);
	static void printCodeMap();
	static void huffmanCoding(const char*);
	static void printCode(std::vector<bool>);
	bool operator()(const int& l, const int& r);

};

#endif /* HUFFMAN_HPP_ */
