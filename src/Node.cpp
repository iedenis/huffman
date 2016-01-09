#include "Node.hpp"

Node::Node(char letter, int occurences) {
	_character = letter;
	_occurences = occurences;
	_leftSon = NULL;
	_rightSon = NULL;

}

Node::Node(Node *left, Node *right) {
	_character='\0';
	_leftSon = left;
	_rightSon = right;
	_occurences = left->_occurences + right->_occurences;
}

void Node:: setLeftSon(Node* left){
	_leftSon=left;
}
void Node::setRightSon(Node* right){
	_rightSon=right;
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
/*bool Node::operator <(Node* other){
	//TODO
	if(this->_occurences==other->_occurences){
		return this->_character<other->_character;
	}
	return this->_occurences<other->_occurences;
}*/



Node::~Node() {
}

