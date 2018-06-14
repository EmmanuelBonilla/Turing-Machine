#ifndef TAPE_H
#define TAPE_H

#include "inputalphabet.h"
#include "tapealphabet.h"
#include "direction.h"
#include <string>
#include <fstream>

using namespace std;

class Tape
{
    private:
        string cells;
        int currentCell;
        char blankCharacter;
    public:
        void load (ifstream &file, bool &valid);
        void validate (const InputAlphabet &inputAlphabet, const TapeAlphabet& tapeAlphabet, bool& valid) const;
        void view () const;
        void initialize (string inputString);
        void update (char writeCharacter, direction moveDirection);
        string left (int maximumNumberOfCells) const;
        string right (int maximumNumberOfCells) const;
        char currentChar () const;
        bool isFirstCell () const;
        Tape ();
};
#endif
