#include "state.h"
#include "turingmachine.h"
#include "commands.h"
#include "inputString.h"
#include "crash.h"

#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

// function prompts user for input
char getCommand()
{
    string input;
    do
    {
        cout << "COMMAND: ";
        cin >> input;
    } while (input.length() != 1);
      
    return toupper(input[0]);
}


// method is designed to initialize inputStrings, Commands, turingMachine, and start the user interface that will allow the user to run command
void Commands :: startTuringMachine (string file)
{
    InputString inputString;
    string stringFile = file;
    stringFile.append (".str");
    
    if (ifstream (stringFile.c_str()))
    {
        string textFromFile;
        ifstream inputStringStream;
        inputStringStream.open(stringFile.c_str(), ifstream::in);
        while (getline (inputStringStream, textFromFile))
        {
            inputString.load(textFromFile);
        }
    }
  
    bool doesInputStringFileExist = false;

    if (doesInputStringFileExist == false)
    {
        fstream newInputStringFile;
        newInputStringFile.open (stringFile.c_str(), ios::out);
        newInputStringFile << flush;
        newInputStringFile.close();
    }
  
    char input;
    int maxTransitions= 1;
    int maxCells = 32;
    int inputStringToDelete;
    int inputStringToOperateOn;
    bool overwrite = false;
    string userInput;
    string inputStringToAdd;
    string turingMachineStatus;
    string definitionFile = file;
    definitionFile.append (".def");
    TuringMachine turingMachine (definitionFile);
    string lastInputString;

    cout << endl << "Definition file: " << file << " is successfully loaded " << endl << endl;

    while (1)
    {
        input = getCommand();
        switch (input)
        {
			case 'D':
			case 'd':
                cout << endl << "Enter index to be deleted: ";
                cin >> userInput;
                cout << endl;
                inputStringToDelete = atoi(userInput.c_str());
                
                if (inputStringToDelete < 1 || inputStringToDelete > inputString.size())
                {
                    cout << "Error: No input string with an index " << userInput << endl << endl;
                    break;
                }

                inputString.remove (inputStringToDelete - 1);
                overwrite = true;
            break;

            case 'X':
            case 'x':
                if (!doesInputStringFileExist)
                {
                    inputString.writeListToFile(stringFile.c_str());
                    cout << endl << "Sucess: " << stringFile << " has been created" << endl;
                }

                if (overwrite)
                {
                    fstream overwriteInputStringFile;
                    overwriteInputStringFile.open (stringFile.c_str(), ios::out);
                    overwriteInputStringFile << flush;
                    for (int index = 0; index < inputString.size(); index++)
                    {
                        overwriteInputStringFile << inputString.element(index) << endl;
                    }
                }
            exit(EXIT_SUCCESS);

            case 'H':
            case 'h':
                cout << endl
                    << "(D)elete:   Delete input string from list" << endl
                    << "E(x)it:     Exit application" << endl
                    << "(H)elp:     Help user" << endl
                    << "(I)nsert:   Insert input string into list" << endl
                    << "(L)ist:     List input strings" << endl
                    << "(Q)uit:     Quit operation of Turing machine on input string" << endl
                    << "(R)un:      Run turing machine on input string" << endl
                    << "S(e)t:      Set maximum number of transitions to perform" << endl
                    << "Sho(W):	    Show status of application" << endl
                    << "(T)runcate: Truncate instantaneous descriptions" << endl
                    << "(V)iew:     View turing machine" << endl << endl;
            break;

            case 'I':
            case 'i':
                cout << endl << "Please enter an Input string: ";
                cin >> inputStringToAdd;
                if (((int)inputStringToAdd.size()) < 1)
                    break;

                if (turingMachine.isValidInputString(inputStringToAdd))
                {
                    inputString.insert(inputStringToAdd);
                    overwrite = true;
                }
                cout << endl;
            break;

            case 'L':
            case 'l':
                inputString.view();
            break;

            case 'Q':
            case 'q':
                if (!turingMachine.isOperating())
                {
                    cout << "Error: Turing Machine Unitialized" << endl;
                    break;
                }

                lastInputString = turingMachine.inputString();
                turingMachine.terminateOperation();
            break;

            case 'R':
            case 'r':
                if (!turingMachine.isOperating())
                {
                    cout << endl << "Enter Input String Index: ";
                    cin >> userInput;
                    inputStringToOperateOn = atoi(userInput.c_str());

                    if (inputStringToOperateOn < 1 || inputStringToOperateOn > inputString.size())
                    {
                        cout << "Error: Invalid Input String Index" << endl << endl;
                        break;
                    }
                    
                    turingMachine.initialize(inputString.element(inputStringToOperateOn-1)); 
                    cout << endl;
                }

                else if (turingMachine.isOperating())
                {
                    turingMachine.performTransitions (maxTransitions);
                    turingMachine.viewInstantaneousDescription (maxCells);
                    
                    if (!turingMachine.isOperating())
                    {
                        if (!turingMachine.isAcceptedInputString())
                        {
                            cout << "Total Amount of Transitions: " << turingMachine.totalNumberOfTransitions() << endl;
                            cout << "Rejected: Input string " << turingMachine.inputString() << "has been rejected" << endl << endl; 
                        }
                    } 
                }

                if (turingMachine.isAcceptedInputString())
                {
                    cout << "Original input string: " << turingMachine.inputString() << endl;
                    cout << "Accepted number of Transitions: " << turingMachine.totalNumberOfTransitions() << endl << endl;
                }
            break;

            case 'E':
            case 'e':
            {
                cout << endl;
                cout << "Configure Settings: Maximum Number of Transitions" << endl;
                cout << "Current setting: [" << maxTransitions << "]" << endl;
                cout << "Enter a new Value: ";
                cin >> userInput;
                if (atoi (userInput.c_str()) < 1)
                {
                    cout << "Error: Only positive integers allowed" << endl << endl;
                    break;
                }
                else if (atoi (userInput.c_str()) == maxTransitions)
                {
                    cout << "Success: Current setting has not been changed" << endl << endl;
                    break;
                }
                cout << "Sucess: Maximum number has been changed to " << atoi (userInput.c_str()) << endl << endl;
                maxTransitions = max(atoi (userInput.c_str()), 1);
            }
            break;

            case 'W':
            case 'w':
                cout << endl;
                cout << "Course:                    Computer Science 322" << endl;
                cout << "Semester and Year:         Fall, 2018 " << endl;
                cout << "Instructor:                Dr. Neil Corrigan " << endl;
                cout << "Aurthor:                   Emmanuel Bonilla" << endl;
                cout << "Version:                   1.0" << endl;
                cout << "Configuration Settings:    Max Transitions: " << maxTransitions << endl;
                cout << "	                   Max Left and Right cells: " << maxCells << endl;
                cout << "Turing Machine Name:       TM " << endl;
                cout << "Status of TM:              ";
                turingMachine.terminateOperation();
                cout << endl;
            break;

            case 'T':
            case 't':
                cout << endl;
                cout << "Configure Settings: Maximum # of cells, left and right of tape head" << endl;
                cout << "Current Setting: [" << maxCells << "]" << endl;
                cout << "Enter new value: ";
                cin >> userInput;
                if (atoi(userInput.c_str()) < 1)
                {
                    cout << "Error: Only positive integer" << endl << endl;
                    break;
                }
                else if (atoi(userInput.c_str()) == maxCells)
                {
                    cout << "Success: Current setting has not been changed" << endl << endl;
                    break;
                }
                maxCells = atoi(userInput.c_str());
                cout << "Success: Maximum # of cells changed to " << maxCells << endl << endl;

            break;
 
            case 'V':
            case 'v':
                turingMachine.viewDefinition();
                cout << endl;
            break;

            default:
                cout << "Invalid command, type 'H' for HELP" << endl; 
        }
    }
}
