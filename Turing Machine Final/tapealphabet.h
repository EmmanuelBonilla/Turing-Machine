#ifndef TAPE_ALPHABET_H
#define TAPE_ALPHABET_H

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class TapeAlphabet
{
	private:
		vector <char> alphabet;
	public:
		bool isElement (char value);
		void load (ifstream &definition, bool &valid);
		void view() const;
};

#endif