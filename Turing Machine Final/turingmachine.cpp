#include "turingmachine.h"
#include "tape.h"
#include "inputalphabet.h"
#include "tapealphabet.h"
#include "transitionfunction.h"
#include "state.h"
#include "finalstates.h"
#include "crash.h"
#include "uppercase.h"
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <fstream>

using namespace std;

// method to initialize its private members, attempt to open .def file.
TuringMachine :: TuringMachine (string definitionFileName)
{
    ifstream tmDefinitionFile;
    try
    {
        tmDefinitionFile.open(definitionFileName.c_str(), ifstream::in);
    }

    catch (...)
    {
        cout << "Error: unable to open defintion file. " << endl;
        exit(EXIT_FAILURE);
    }

    string text;

    while (tmDefinitionFile >> text)
    {
        if (stringToUppercase(text) != "STATES:")  
            description.push_back(text);

        else if (stringToUppercase(text) == "STATES:")
          break;  
    }   

    if (text != "STATES:")
    {
        cout << "Invalid definition file " << endl;
        exit (EXIT_FAILURE);
    }

    state.load (tmDefinitionFile, valid);
    inputAlphabet.load (tmDefinitionFile, valid);
    tapeAlphabet.load (tmDefinitionFile, valid);
    transitionFunction.load (tmDefinitionFile, valid);

    while (tmDefinitionFile >> text)
    {
        if (state.isElement(text) == true)
        {
            initialState = text;
            break;
        }
    }

    while (tmDefinitionFile >> text)
    {
        if (stringToUppercase (text) == "BLANK_CHARACTER:")
        {
            tape.load (tmDefinitionFile, valid);
            break;
        }
    }

    finalStates.load (tmDefinitionFile,valid);
}

// method is designed to display the entire description of the Turing Machine based on the .def file.  
void TuringMachine :: viewDefinition () const
{
    cout << endl;
    cout << "Turing machine defintion " << endl << endl;
    for (int index = 0; index < (int)description.size(); index++)
    {
        cout << description[index] << " ";
    }
    cout << endl; 
    state.view ();
    inputAlphabet.view ();
    tapeAlphabet.view ();
    transitionFunction.view ();
    cout << endl << "q0 = " << initialState << endl << endl;
    tape.view () ;
    cout << "F = ";
    finalStates.view ();
}

// method displays the current description of the tape.  
void TuringMachine :: viewInstantaneousDescription (int maximumNumberOfCells) const
{
    cout << numberOfTransitions << "." << tape.left (maximumNumberOfCells) << "[";
    cout << currentState << "]" << tape.right (maximumNumberOfCells) << endl;
}

// method stores the input string into the originalInputString.
void TuringMachine :: initialize (string inputString)
{
	used = true;
    operating = true;
    accepted = false; 
    rejected = false;
    tape.initialize (inputString); 
    numberOfTransitions = 0;
    originalInputString = inputString;
    currentState = initialState;
}
// method will take in a number of transition to be performed by the user. 
void TuringMachine :: performTransitions (int maximumNumberOfTransitions)
{
    char writeCharacter;
	string destinationState;
    direction moveDirection;

    for (int index = 0; index < maximumNumberOfTransitions; index++)
    {
        if (transitionFunction.findTransition (currentState, tape.currentChar(), destinationState, writeCharacter, moveDirection) == true)
        {    
            tape.update (writeCharacter, moveDirection);
            currentState = destinationState;
            numberOfTransitions++;

            if (finalStates.isElement (destinationState))
            {
                accepted = true;
                operating = false;
            }
        }
        else
        {
            rejected = true;
            operating = false;
            break;
        }
    }
}

// method will reset the Turing Machine to default and set the state to not operating.
void TuringMachine :: terminateOperation()
{
    operating = false; 
    cout << "Input string " << originalInputString << " not accepted in " << numberOfTransitions << " transitions" << endl;
}

// method will return originalInputString attribute
string TuringMachine :: inputString () const
{
    return originalInputString;
}

// method will return the attribute numberOfTransitions.
int TuringMachine :: totalNumberOfTransitions () const
{
    return numberOfTransitions;
}

// method determines if the .def file is Valid
bool TuringMachine :: isValidDefinition () const
{
    return valid;
}

// method determine if the input string contains only characters from the inputAlphabet.
bool TuringMachine :: isValidInputString (string value) const
{
    bool validInputString = true;
    for (int index = 0; index < (int)value.size(); index++)
    {
        char tempChar = value[index];
        if ((inputAlphabet.isElement(tempChar)) == false)
        {
            validInputString = false;
        }
    }
    return validInputString;
}

// method will return the attribute used
bool TuringMachine :: isUsed() const
{
    return used;
}

// method determine if the Turing machine is working on an input string. 
bool TuringMachine :: isOperating () const
{
    return operating;
}

// method checks if the current state is accepted.
bool TuringMachine :: isAcceptedInputString () const
{
    return accepted;
}

// method checks if the current state is rejected.
bool TuringMachine :: isRejectedInputString () const
{
    return rejected;
}