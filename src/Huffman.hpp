/*
 * Huffman.hpp
 *
 *  Created on: Dec 29, 2015
 *      Author: fox
 */

#ifndef HUFFMAN_HPP_
#define HUFFMAN_HPP_

#include <map>
#include <iostream>
#include <string>
#include <queue>
#include "Node.hpp"
#include <list>
class Huffman {
private:
	/*static std::priority_queue<double, std::vector<double>, std::greater<double> >
	 q1, q2;
	 */
	//static std::priority_queue<Node*> leftQueue;
	static std::map<char, int> occurences_map;
	static int length;
	/*
	 * Priority queues for another implementation with two priority quueues
	 */
	//static std::priority_queue<Node*, std::vector<Node*>, Node::CompareNodes> leftQueue;
	//static std::priority_queue<Node*, std::vector<Node*>, Node::CompareNodes> rightQueue;

public:
	static std::list<Node*> tree;

	static std::queue<Node*> leftQueue;
	static std::queue<Node*> rightQueue;

	static Node* makeNodeFromMin();
	static void readFile(const char*);
	static void writeToFile(const char*);
	static void count(std::string&);
	static void ini();
	static void printTree(Node*,int);
	bool operator()(const int& l, const int& r);

};

#endif /* HUFFMAN_HPP_ */
