#include "uppercase.h"
#include <string>

using namespace std;

string stringToUppercase (string stringToChange)
{
    string capitalOutput = stringToChange;
    for (int index = 0; index < (int)capitalOutput.size (); index++)
    {
        capitalOutput[index] = toupper(capitalOutput[index]);
    }
    return capitalOutput;
}

char characterToUppercase(char characterToChange)
{
	char capital_input = characterToChange;
    return toupper(capital_input);
}