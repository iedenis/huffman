#include <map>
#include <string>
#include "Huffman.hpp"
#include <deque>
#include <iostream>
#include <fstream>
using namespace std;

std::map<char, int> Huffman::accurences;
void Huffman::writeToFile(const std::string &out_file) {
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
				accurences[ch]++;
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

/*void Huffman::count(std::string& line) {

 for (std::string::iterator it = line.begin(); it != line.end(); ++it) {
 accurences[*it]++;
 //cout << *it << endl;
 cout<<line.end();
 }
 */

