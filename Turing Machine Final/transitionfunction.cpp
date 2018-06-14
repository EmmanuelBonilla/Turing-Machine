#include "transitionfunction.h"
#include "transition.h"
#include "direction.h"
#include "uppercase.h"
#include "crash.h"
#include <string>
#include <vector>
#include <fstream>
#include<iostream>

using namespace std;

/* method is designed to read in from the definition file. 
   As well to return a true or false if the character is reserved, 
   not printable, or the next keyword does not follow. 
   It will display and appropriate message upon an error.  */
void TransitionFunction :: load (ifstream &file, bool &valid)
{
    string sourceState;
    string readCharacter;
    string writeCharacter;
    string direction;
    string destinationState;

    valid = true;
    while (file >> sourceState)
	{
        if (stringToUppercase (sourceState) == "INITIAL_STATE:")
            return;
            
        file >> readCharacter;
        file >> destinationState;
        file >> writeCharacter;
        file >> direction;

        if ((readCharacter.size() == 0 || stringToUppercase (readCharacter) == "INITIAL_STATE:") ||
            (destinationState.size() == 0 || stringToUppercase (destinationState) == "INITIAL_STATE:") ||
            (writeCharacter.size() == 0 || stringToUppercase (writeCharacter) == "INITIAL_STATE:") ||
            (direction.size() == 0 || stringToUppercase (direction) == "INITIAL_STATE:"))
		{
            cout << "Error: Incorrect Transition format." << endl;
            break;
        }
    
        if ((readCharacter.size () == 1) && (direction.size() == 1) && (writeCharacter.size() == 1))
		{
            Transition transition (sourceState, readCharacter[0], destinationState, writeCharacter[0], direction[0]);
            transitions.push_back(transition);
        }
        else
        {
            cout << "Error: Incorrect Transition format." << endl;
            break;
        }
    }

    valid = false;
}

// method is designed to return the attribute destination.
string TransitionFunction :: destinationState(int index) const
{
    return transitions[index].destinationState();	
}

/* method is designed to find the transition based on the source state and in read character.
   Also write the character, move the direction and return true or false based
   on what transition is found. If and error, it will display and appropriate message. */
bool TransitionFunction :: findTransition (string sourceState, char readCharacter, string &destinationState, char &writeCharacter, direction &moveDirection) const
{
    bool isDefinedReturn = false;
    for (int index = 0; index < (int)transitions.size(); index++)
    {
        if ((transitions[index].sourceState() == sourceState) && (transitions[index].readCharacter() == readCharacter))
        {
            destinationState = transitions[index].destinationState();
            writeCharacter = transitions[index].writeCharacter();
            moveDirection = transitions[index].moveDirection();
            isDefinedReturn = true;
            return isDefinedReturn;
        }
    }
    return isDefinedReturn;
}

/* method is designed to check if the input alphabet is in the tape alphabet. 
   Return true if valid, false if not valid with an appropriate error message. */
bool TransitionFunction :: validate (string state) const
{
    bool isSourceState = false;
    for (int index = 0; index < (int)transitions.size(); index++)
    {
        if (transitions[index].sourceState() == state) 
        {
            isSourceState = true;
            return isSourceState;
        }
        return isSourceState;
    }
    return isSourceState;
}

// method will display the character of the Turning Machine
void TransitionFunction :: view () const
{
    for (int index = 0; index < (int)transitions.size(); index++)
    {
        cout << "\u03B4(" << transitions[index].sourceState () << ",";
        cout << transitions[index].readCharacter ()      << ") = (";
        cout << transitions[index].destinationState ()  << ", ";
        cout << transitions[index].writeCharacter ()    << ", ";
        cout << transitions[index].moveDirection ()     << ")" << endl;
     }
}

// method returns the attribute read. 
char TransitionFunction :: readCharacter(int index) const
{
    return transitions[index].readCharacter();	
}

// method returns the attribute write. 
char TransitionFunction :: writeCharacter(int index) const
{
    return transitions[index].writeCharacter();
}

// method checks to see if the index is out of bounds. 
string TransitionFunction :: sourceState (int index) const
{
    if (index < 0 || index >= (int)transitions.size())
	{
        throw Crash("Index is out of bounds");
        cout << endl;
	}
    return transitions[index].sourceState();
}

//method returns the attribute size 
int TransitionFunction :: size() const
{
    return (int)transitions.size();
}