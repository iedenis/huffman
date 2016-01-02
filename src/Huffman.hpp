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
#include <deque>

class Huffman {
public:

	static std::map<char, int> accurences;
	static std::deque<std::string> d;
public:

	static void readFile(const char*);
	static void writeToFile(const std::string&);
	static void count( std::string&);

};

#endif /* HUFFMAN_HPP_ */
