/*
 * Node.cpp
 *
 *  Created on: Jan 3, 2016
 *      Author: fox
 */

#include "Node.hpp"

Node::Node(char letter, int occurences) {
	_character = letter;
	_occurences = occurences;
	_leftSon = NULL;
	_rightSon = NULL;

}

Node::Node(Node *left, Node *right) {
	_character=NULL;
	_leftSon = left;
	_rightSon = right;
	_occurences = left->_occurences + right->_occurences;
}

Node* Node::getLeftson(){
	return _leftSon;
}
Node* Node::getRightSon(){
	return _rightSon;
}
char Node::getCharacter(){
	return _character;
}
int Node::getOccurences(){
	return _occurences;
}
bool Node::operator <(Node* other){
	return this->_occurences<other->_occurences;
}



Node::~Node() {
}

