#include <map>
#include <string>
#include "Huffman.hpp"
#include <queue>
#include <iostream>
#include <fstream>
#include "Node.hpp"
using namespace std;
int Huffman::length = 0;
std::queue<Node*> Huffman::leftQueue;
std::queue<Node*> Huffman::rightQueue;
std::list<Node*> Huffman::tree;
std::map<char, std::vector<bool> > Huffman::code_map;
std::vector<bool> Huffman::word_code;
/*
 * queues for implementing with two priority queues
 */
//std::priority_queue<Node*,std::vector<Node*>,Node::CompareNodes> Huffman::leftQueue;
//std::priority_queue<Node*,std::vector<Node*>,Node::CompareNodes> Huffman::rightQueue;
std::map<char, int> Huffman::occurences_map;

void Huffman::writeToFile(const char* out_file) {
	ofstream wFile;

	try {
		wFile.open(out_file, ios::out);
	}

	catch (ifstream::failure & e) {
		cout << e.what() << endl;
		throw;
	}

	wFile.close();
}
void Huffman::readFile(const char* file_name) {
	char ch;
	ifstream rFile;
	string line;
	rFile.exceptions(ifstream::failbit | ifstream::badbit);
	try {
		rFile.open(file_name, iostream::in);
		if (rFile.is_open() && !rFile.eof()) {
			cout << "file opened" << endl;

			while (rFile.get(ch)) {
				occurences_map[ch]++;
				length++;
			}

		}
	} catch (ifstream::failure & e) {
		if (!rFile.eof()) {  // either badbit or failbit are set
			cout << e.what() << endl;
			throw;
		}
	}

	rFile.close();
	return;
}

void Huffman::ini() {
	std::list<Node*>::const_iterator iter;

	std::map<char, int>::iterator it = Huffman::occurences_map.begin();
	//it=Huffman::occurences_map.rbegin();
	while (it != Huffman::occurences_map.end()) {
		Node* temp = new Node(it->first, it->second);
		tree.push_back(temp);
		//leftQueue.push(temp);
		it++;
	}
	tree.sort(Node::CompareNodes());
	for (iter = tree.begin(); iter != tree.end();) {
		Node* temp = *iter;
		leftQueue.push(*iter);
		++iter;
		tree.remove(temp);
	}
	Node* tempFirst = leftQueue.front();
	leftQueue.pop();
	Node* tempSecond = new Node(tempFirst, leftQueue.front());
	leftQueue.pop();
	rightQueue.push(tempSecond);

	/*	while (!leftQueue.empty()) {
	 Node* temp = leftQueue.front();
	 std::cout << temp->getOccurences() << " ";
	 std::cout << temp->getCharacter() << std::endl;
	 leftQueue.pop();
	 }*/

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
		tree.push_back(parent);
		return parent;
	} else if (leftQueue.empty()) {
		firstMin = rightQueue.front();
		rightQueue.pop();
		secondMin = rightQueue.front();
		rightQueue.pop();
		parent = new Node(firstMin, secondMin);
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
				//firstMin = rightQueue.front();
				//rightQueue.pop();
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
				firstMin = leftQueue.front();
				leftQueue.pop();
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

	//Node* min=(leftTemp->_occurences<rightTemp->_occurences)?leftTemp:rightTemp;

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
			std::cout << root->getOccurences() << endl;
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
		code_map[(char)root->getCharacter()] = word_code;
	}
	word_code.pop_back();
}
void Huffman::printCodeMap() {
	std::map<char, std::vector<bool> >::iterator it = Huffman::code_map.begin();
	std::cout<<"================================"<<std::endl;
	std::cout<<"Huffman coding"<<std::endl;
	while (it != Huffman::code_map.end()) {
		vector<bool> vec;
		vec = it->second;
		for (unsigned int i = 0; i < vec.size(); ++i) {
			std::cout << vec[i];
		}
		std::cout<<" ";
		it++;
	}
}

