#include "inputalphabet.h"
#include "crash.h"
#include "uppercase.h"
#include <iostream>
#include <locale>
#include <fstream>
#include <vector> 

using namespace std;

// method returns the attribute index, throws an error if out of bounds
char InputAlphabet:: element (int index)
{
	if ( index >= (int)alphabet.size())
		throw Crash ("Error: out of bounds");
    cout << endl;
	return alphabet[index];
}

/* method is designed to read in from the definition file. 
   As well to return a true or false if the character is reserved, 
   not printable, or the next keyword does not follow. It will display and appropriate message upon an error. */
void InputAlphabet :: load (ifstream &file, bool &valid)
{
    string text;

    valid = true;
    while (file >> text)
    {
        if (stringToUppercase (text) == "TAPE_ALPHABET:")
            return;

        for (int index = 0; index < (int)text.size(); index++)
        {
            if (!isalpha (text [index])) 
            {
                valid = false;
                cout << "Error: Only alpha characters allowed" << endl;
                return;
            }
        } 

        alphabet.push_back (text[0]);
    }

    valid = false;
}

// method returns the attribute size 
int InputAlphabet :: size () const
{
    return (int)alphabet.size ();
}

// method will display the character of the Turning Machine
void InputAlphabet :: view () const
{
	cout << "\u03A3 = {";
	for (int index = 0; index < (int)alphabet.size (); index++)
    {
        cout << alphabet[index];
        if ((int)alphabet.size () - 1 != index)
            cout << ",";
	}
	cout << "}" << endl << endl;
}

// method is designed to return true if the character is compared and found in the input alphabet. If not found return false
bool InputAlphabet:: isElement (char value) const
{
    bool isElement = false;
	for (int index = 0; index < (int) alphabet.size(); index ++)
    {
		if (alphabet [index] == value)
			isElement = true;
	}
	return isElement;
}