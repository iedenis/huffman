#include <map>
#include <string>
#include "Huffman.hpp"
#include <queue>
#include <iostream>
#include <fstream>
#include "Node.hpp"
int Huffman::length = 0;
std::queue<Node*> Huffman::leftQueue;
std::queue<Node*> Huffman::rightQueue;
std::list<Node*> Huffman::tree;
std::map<char, std::vector<bool> > Huffman::code_map;
std::vector<bool> Huffman::word_code;
double Huffman::compLength = 0.0;
std::map<char, int> Huffman::occurences_map;
std::ofstream Huffman::wFile;

void Huffman::initialize(const char* out_file) {
	try {
		wFile.open(out_file, std::ios::out);
	}

	catch (std::ifstream::failure & e) {
		std::cout << e.what() << std::endl;
		throw;
	}
}

void Huffman::readFile(const char* file_name) {
	char ch;
	std::ifstream rFile;
	std::string line;
	rFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		rFile.open(file_name, std::iostream::in);
		if (rFile.is_open() && !rFile.eof()) {

			while (rFile.get(ch)) {
				occurences_map[ch]++;
				length++;
			}
		}

	} catch (std::ifstream::failure & e) {
		if (!rFile.eof()) {
			std::cout << e.what() << std::endl;
			throw;
		}
	}

	rFile.close();
	return;
}

void Huffman::ini() {
	std::list<Node*>::const_iterator iter;
	std::map<char, int>::iterator it = Huffman::occurences_map.begin();

	while (it != Huffman::occurences_map.end()) {
		Node* temp = new Node(it->first, it->second);
		tree.push_back(temp);
		it++;
	}
	tree.sort(Node::CompareNodes());
	for (iter = tree.begin(); iter != tree.end();) {
		Node* temp = *iter;
		leftQueue.push(*iter);
		++iter;
		tree.remove(temp);
	}

}

Node* Huffman::makeNodeFromMin() {
	Node* leftTemp = NULL;
	Node* rightTemp = NULL;
	Node* firstMin = NULL;
	Node* secondMin = NULL;
	Node* parent = NULL;

	if (rightQueue.empty() && leftQueue.empty())
		return NULL;
	if (rightQueue.size() == 1 && leftQueue.size() == 1) {
		leftTemp = leftQueue.front();
		leftQueue.pop();
		rightTemp = rightQueue.front();
		if (leftTemp->getOccurences() > rightTemp->getOccurences())
			parent = new Node(leftTemp, rightTemp);
		else
			parent = new Node(rightTemp, leftTemp);
		tree.push_back(parent);
		return parent;
	} else if (rightQueue.empty()) {
		firstMin = leftQueue.front();
		leftQueue.pop();
		secondMin = leftQueue.front();
		leftQueue.pop();
		parent = new Node(firstMin, secondMin);
		rightQueue.push(parent);
		tree.push_back(parent);
		return parent;
	} else if (leftQueue.empty()) {
		firstMin = rightQueue.front();
		rightQueue.pop();
		secondMin = rightQueue.front();
		rightQueue.pop();
		parent = new Node(firstMin, secondMin);
		rightQueue.push(parent);
		tree.push_back(parent);
		return parent;
	} else {
		leftTemp = leftQueue.front();
		rightTemp = rightQueue.front();
		if (leftTemp->getOccurences() <= rightTemp->getOccurences()) {
			firstMin = leftTemp;
			leftQueue.pop();
		} else {
			firstMin = rightTemp;
			rightQueue.pop();
		}

		if (!leftQueue.empty() && !rightQueue.empty()) {
			leftTemp = leftQueue.front();
			rightTemp = rightQueue.front();

			if (leftTemp->getOccurences() < rightTemp->getOccurences()) {
				leftTemp = leftQueue.front();
				secondMin = leftTemp;
				leftQueue.pop();
			} else {
				secondMin = rightTemp;
				rightQueue.pop();
			}
		} else if (leftQueue.empty()) {
			if (rightQueue.size() == 1) //TODO
				return NULL;
			else {
				secondMin = rightQueue.front();
				rightQueue.pop();
				parent = new Node(firstMin, secondMin);
				tree.push_back(parent);
				rightQueue.push(parent);
				return parent;
			}
		} else if (rightQueue.empty()) {
			if (leftQueue.size() == 1)
				return NULL;
			else {
				secondMin = leftQueue.front();
				leftQueue.pop();
				parent = new Node(firstMin, secondMin);
				tree.push_back(parent);
				return parent;
			}
		}
		parent = new Node(firstMin, secondMin);
		rightQueue.push(parent);
		tree.push_back(parent);
		return parent;
	}
}

void Huffman::printTree(Node* root, int k = 0) {
	if (root != NULL) {
		Huffman::printTree(root->getLeftson(), k + 3);
		for (int i = 0; i < k; ++i) {
			std::cout << " ";
		}
		if (root->getCharacter())
			std::cout << root->getOccurences() << "(" << root->getCharacter()
					<< ")" << std::endl;
		else
			std::cout << root->getOccurences() << std::endl;
		Huffman::printTree(root->getRightSon(), k + 3);
	}
}

void Huffman::build(Node* root) {
	if (root->getLeftson() != NULL) {
		word_code.push_back(0);
		build(root->getLeftson());
	}
	if (root->getRightSon() != NULL) {
		word_code.push_back(1);
		build(root->getRightSon());
	}
	if (root->getCharacter() != '\0') {
		code_map[(char) root->getCharacter()] = word_code;
	}
	word_code.pop_back();
}
void Huffman::printCodeMap() {
	std::map<char, std::vector<bool> >::iterator it = Huffman::code_map.begin();
	wFile
			<< "======================================================================"
			<< std::endl;
	wFile << "coded words by Huffman algorithm" << std::endl;
	while (it != Huffman::code_map.end()) {
		std::vector<bool> vec;
		vec = it->second;
		compLength += (vec.size() * (occurences_map[it->first]));
		wFile << it->first << "-->";

		for (unsigned int i = 0; i < vec.size(); ++i) {
			wFile << vec[i];
		}
		wFile << std::endl;
		it++;
	}
	wFile
			<< "======================================================================"
			<< std::endl;
}
void Huffman::huffmanCoding(const char* file_name) {
	wFile << "\n****Huffman coding*****" << std::endl;
	char ch;
	std::ifstream rFile;
	std::string line;
	rFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		rFile.open(file_name, std::iostream::in);
		if (rFile.is_open() && !rFile.eof()) {
			while (rFile.get(ch)) {
				printCode(code_map[ch]);
				wFile << " ";
			}
			wFile << "======================================================"
					<< std::endl;
		}
	} catch (std::ifstream::failure & e) {
		if (!rFile.eof()) {
			std::cout << e.what() << std::endl;
			throw;
		}
	}
	rFile.close();
	return;
}
void Huffman::printCode(std::vector<bool> vec) {
	for (unsigned int i = 0; i < vec.size(); ++i) {
		wFile << vec[i];
	}
}

