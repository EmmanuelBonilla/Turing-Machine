#include "tapealphabet.h"
#include "uppercase.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// method is designed to return true if the character is compared and found in the input alphabet. If not found return false
bool TapeAlphabet :: isElement (char value)
{
	bool found = false;
    for (int index = 0; index < (int)alphabet.size(); index++)
    {
        if (alphabet[index] == value)
        {
            found = true;
            return found;
        }
    }
    return found;
}

/* method is designed to read in from the definition file. 
   As well to return a true or false if the character is reserved, 
   not printable, or the next keyword does not follow. 
   It will display and appropriate message upon an error. */
void TapeAlphabet :: load (ifstream &file, bool &valid)
{
    string text;

    valid = true;
    while (file >> text)
    {
        if (stringToUppercase (text) == "TRANSITION_FUNCTION:")
            return;

        if (text.size() > 1)
        {
            cout << "Error: Invalid input character string " << text << endl;
            break;
        }
        if (text[0] == '[' || text[0] == ']' || text[0] == '<' || text[0] == '>' || text[0] == '\\')
        {
            cout << "Error: Reserved character found in the tape alphabet" << endl;
            break;
        }
        
        alphabet.push_back(text[0]);        
    }

    valid = false;
}

// method will display the character of the Turning Machine
void TapeAlphabet :: view () const
{
    cout<<"\u0393 = {";
    for (int index = 0; index < (int)alphabet.size (); index++)
    {
        cout << alphabet[index];
        if ((int)alphabet.size() - 1 != index)
            cout << ",";
    }
    cout << "}" << endl << endl; 
}