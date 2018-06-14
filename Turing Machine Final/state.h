#ifndef  STATE_H
#define STATE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class State
{
	private:
		vector <string> names;
	public:
		bool load (ifstream &file, bool &valid);
		void view () const;
		bool isElement (string value);
};

#endif