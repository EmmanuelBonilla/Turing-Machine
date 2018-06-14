#include "tape.h"
#include "crash.h"
#include "inputalphabet.h"
#include "tapealphabet.h"
#include "direction.h"
#include "uppercase.h"
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

 //the constructor that sets the attributes to default, cells (“ “), currentCell(0), blankCharacter (‘ ‘).
Tape::Tape()
    : cells(" "), 
    currentCell(0), 
    blankCharacter(' ')
{
}

/* Method reads from the definition file. An error message will display if the character found is a reserved character or the next keyword does not follow. */
void Tape :: load (ifstream &file, bool &valid)
{
    string value;
    valid = true;

    if ((file >> value) && (value.length() == 1) && (value[0] != '\\') && (value[0] != '[') && (value[0] != ']') && (value[0] != '<') && (value[0] != '>') && (value[0] != '!') && (value[0] != '~'))
    {
        blankCharacter = value[0];

        if ((!(file >> value)) || (stringToUppercase (value) != "FINAL_STATES:"))
        {
            valid = false;
        }
    }
    else
    {
        cout << "Error: Invalid blank character" << endl;
        valid = false;
    }
}

// method checks if the blank character is the tapeAalphabet. It will display an appropriate error message if it is in the inputAlphabet. 
void Tape :: validate (const InputAlphabet& inputAlphabet, const TapeAlphabet& tapeAlphabet, bool &valid) const
{
    if (inputAlphabet.isElement (blankCharacter))
    {
		cout << "blank character " << blankCharacter << " is in input alphabet " << endl;
        valid = false;
    }

    else
    {
		cout << "blank character " << blankCharacter << " is in tape alphabet " << endl;
        valid = false;
    }
}

// method will display the character of the Turning Machine
void Tape :: view () const
{
    cout << "B = " << blankCharacter << endl << endl;
}

// ethod sets the cells to the inputString plus the blankCharacter, and sets currentCell to zero.
void Tape :: initialize (string inputString)
{
    cells = inputString + blankCharacter;
    currentCell = 0;
}

// method will write a character to the current cell location, then move the cell left or right. Update method will then increment or decrement the index.
void Tape :: update (char writeCharacter, direction moveDirection)
{
    moveDirection = characterToUppercase (moveDirection);
    
    if  ( (moveDirection == 'L') && (currentCell == 0))
    {
        throw Crash ("left move from first cell");
        cout << endl;
    }

    if ( (moveDirection == 'R') && (currentCell == (int)cells.length() -1) )
    {
        cells += blankCharacter;
    }

    cells[currentCell] = writeCharacter;
    
    if (moveDirection == 'L')
        -- currentCell;
    else 
        ++currentCell;
}

/* method will return a string of characters left of the current cell from the Turing Machine tape not including the current cell. 
   If the string is truncated, the reserved character ‘<’ will be inserted to the front of the string. */
string Tape :: left (int maximumNumberOfCells) const
{
    int firstCell = max (0, currentCell - maximumNumberOfCells);
    string value = cells.substr (firstCell, currentCell - firstCell);
    
    if ((int)value.length() < currentCell)
    {
        value.insert (0,"<");
    }
    return value;
}

/* method will return a string of characters right of the current cell from the Turing Machine tape not including the current cell. 
   If the string is truncated, the reserved character ‘>’ will be truncated. */
string Tape::right(int maximumNumberOfCells) const
{
    int endCell = (int)cells.length() - 1;

    while ((endCell >= currentCell) && (cells[endCell] == blankCharacter ))
    {
        --endCell;
    }
    
 	int last_cell = min(endCell, currentCell + maximumNumberOfCells - 1);
    string value = cells.substr(currentCell, last_cell - currentCell + 1);

    if ((int)value.length() < endCell - currentCell + 1)
        value.append(">");
    return value;
}

// method returns the character in the current cell on the Turing Machine Tape.
char Tape:: currentChar () const
{
    return cells[currentCell];
}

 //method will only return true if the current cell is in the zero index.
bool Tape :: isFirstCell () const 
{
    return currentCell == 0;
}