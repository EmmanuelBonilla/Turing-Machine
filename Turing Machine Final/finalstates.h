#ifndef FINAL_STATES_H
#define FINAL_STATES_H

#include <iostream>
#include <fstream> 
#include <vector>
#include <string> 

using namespace std;

class FinalStates
{
    private:
        vector <string> names;
    public:
        void load (ifstream &file, bool &valid);
        void view () const;
        bool isElement (string value);
        string element (int index);
        int size () const;
};

#endif