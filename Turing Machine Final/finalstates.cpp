#include "finalstates.h"
#include "crash.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// method returns the attribute names. 
string FinalStates :: element (int index)
{
    return names[index];
}

// method takes a string value and returns true or false base on all the elements in the list.
bool FinalStates :: isElement (string value)
{
    for (int index = 0; index < (int) names.size(); index++)
    {
        if (names[index] == value)
            return true;
    }
    return false;
}

/* method is designed to read in from the definition file. 
   As well to return a true or false if the character is reserved, 
   not printable, or the next keyword does not follow. 
   It will display and appropriate message upon an error. */
void FinalStates :: load (ifstream &file, bool &valid)
{
    string value;
    
    while ((file>>value))
    {
        names.push_back(value);
    }
}

// method returns the attribute size 
int FinalStates :: size () const
{
    return names.size();
}

// method will display the character of the Turning Machine.
void FinalStates :: view () const
{
    for (int index = 0; index < (int)names.size(); index++)
    {
        cout << names [index] << endl;
    }
}