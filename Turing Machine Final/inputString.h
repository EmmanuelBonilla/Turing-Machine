#ifndef INPUT_STRING_H
#define INPUT_STRING_H
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class InputString
{
private:
    vector <string> inputStrings;
    bool overWrite;
    bool loaded;
public:
    int size ();
    string element (int index);
    void load (string value);
    void view () const;
    void insert (string value);
    void remove (int inputStringToDelete);
    void writeListToFile (string filePath);
};
#endif