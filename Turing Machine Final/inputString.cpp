#include"inputString.h"
#include <string>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

// method returns the attribute size 
int InputString::size()
{
    return (int)inputStrings.size();
}

// method returns the attribute names
string InputString::element(int index)
{   
    return inputStrings[index];    
}

// method loads to InputString
void InputString :: load (string textFromFile)
{
    inputStrings.push_back(textFromFile);
}

// method will display the character of the Turning Machine
void InputString :: view() const
{
    if ((int)inputStrings.size() > 0)
    {
        cout << endl;
        for(int index = 0; index < (int)inputStrings.size(); index++)
        {
            cout << index+1 << "." << inputStrings[index] << endl;
        }
        cout << endl;
    }
    else if ((int)inputStrings.size() == 0)
        cout << endl << "Error: No input string" << endl;
}

// method inserts to InputString
void InputString::insert(string input_string_to_add)
{
    inputStrings.push_back(input_string_to_add);

}

// method removes index depending on user input
void InputString :: remove (int inputStringFileToRemove)
{
   inputStrings.erase (inputStrings.begin() + inputStringFileToRemove); 
    cout << "Success: " << inputStrings[inputStringFileToRemove] << " has been deleted" << endl;
}

// method write list to file given the file path
void InputString :: writeListToFile (string filePath)
{
        fstream newInputStringFile;
        newInputStringFile.open (filePath.c_str());
        newInputStringFile << flush;
        for (int index = 0; index < (int)inputStrings.size(); index++)
        {
            newInputStringFile << inputStrings[index] << endl;
        }
        newInputStringFile.close();
}





