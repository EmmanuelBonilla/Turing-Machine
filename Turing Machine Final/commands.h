#ifndef COMMANDS_H
#define COMMANDS_H

#include "state.h"
#include "uppercase.h"
#include "turingmachine.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>

class Commands
{
    private:
        vector<string> inputStrings;
    public:
        void startTuringMachine (string fileName);
};

#endif
