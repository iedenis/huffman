/*
 * Node.h
 *
 *  Created on: Jan 3, 2016
 *      Author: fox
 */

#ifndef NODE_HPP_
#define NODE_HPP_
#include <iostream>
class Node {
private:
	char _character;
	int _occurences;
	Node* _leftSon;
	Node* _rightSon;
	//Node* _parent;
public:
	Node(char letter, int occurences);
	Node(Node* left, Node* right);
	Node* getLeftson();
	Node* getRightSon();
	int getOccurences();
	char getCharacter();

	class CompareNodes
	{
	public:
		bool operator()(Node* n1, Node* n2){
			return n1->_occurences<n2->_occurences;
		}
	};
	bool operator<(Node* other);

	virtual ~Node();
};

#endif /* NODE_HPP_ */
