#include "transition.h"
#include "direction.h"
#include <string>

using namespace std;

// method transition will be considered as the constructor of the transition class, because it will initialize source, read, write, move.
Transition :: Transition (string sourceState, char readCharacter, string destinationState, char writeCharacter, direction moveDirection)
    : read (readCharacter),
      write (writeCharacter),
      source (sourceState),
      move (moveDirection),
      destination (destinationState)
{
}

// method sourceState returns the attribute source.
string Transition :: sourceState () const
{
    return source;
}

// method readCharacter returns the attribute read.
char Transition :: readCharacter () const
{
    return read;
}

// method destinationState returns the attribute destination.
string Transition :: destinationState () const
{
    return destination;
}

// method writeCharacter returns the attribute write.
char Transition :: writeCharacter () const
{
    return write;
}

// method moveSirection returns the attribute move.
direction Transition :: moveDirection () const
{
    return move;
}