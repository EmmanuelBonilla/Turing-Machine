#include <iostream>
#include <string>
#include <cstdlib>
#include "commands.h"

using namespace std;

// method is designed to check users inputs correct file before starting the turing machine 
int main (int argc, char* argv[])
{  
    if (argc == 2)
    {
        string fileName = argv[1];
        Commands command;
        command.startTuringMachine(fileName);
    }
    
    if (argc < 2)
    {
        cout << "Error: No destination file" << endl;
        exit(EXIT_FAILURE);
    }

    cout << "Error: Too many command line arguments" << endl;
    return 0;
}