#include "state.h"
#include "uppercase.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

/* method is designed to read in from the definition file. 
   As well to return a true or false if the character is reserved, 
   not printable, or the next keyword does not follow. 
   It will display and appropriate message upon an error. */
bool State :: load (ifstream &file, bool &valid)
{
    string text;

    valid = true;
    while (file >> text)
	{
        if (stringToUppercase (text) == "INPUT_ALPHABET:")
            return true;
        
		for (int index = 0; index < (int)text.size(); index++)
		{
			if (!isalnum (text[index]))
			{
				valid = false;
				cout << "Error: Invalid character " << text << endl;
                return false;
            }
        }

        if (isElement(text))
            cout << "Error: Cannot have duplicate states" << endl;
        else
            names.push_back(text);
    }

    valid = false;
    return false;
}

// method will display the character of the Turning Machine
void State :: view () const
{
    cout << endl;
    cout << "Q = {";
    for (int index = 0; index < (int)names.size(); index++)
	{
        cout << names[index];
        if ((int)names.size () - 1 != index)
            cout << ",";
    }
    cout << "}" << endl << endl;
}

// method takes a string value and returns true or false base on all the elements in the list.
bool State :: isElement (string value)
{
	for (int index = 0; index < (int)names.size(); index++)
	{
		if (names[index] == value)
			return true;
	}
	return false;
}