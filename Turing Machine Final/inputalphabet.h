#ifndef INPUTALPHABET_H
#define INPUTALPHABET_H

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class InputAlphabet
{
    private: 
        vector <char>  alphabet;
    public:
        int size () const;
        void view () const;
        char element (int index);
        bool isElement (char value) const;
        void load (ifstream &file, bool &valid);
};

#endif