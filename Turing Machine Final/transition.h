#ifndef TRANSITION_H
#define TRANSITION_H

#include "direction.h"
#include <string>

using namespace std;

class Transition
{
    private:
        char read;
        char write;
        string source;
        direction move;
        string destination;

    public:
        Transition (string sourceState, char readCharacter, string definitionState, char writeCharacter, direction moveDirection);
        string sourceState () const;
        char readCharacter () const;
        string destinationState () const;
        char writeCharacter () const;
        direction moveDirection () const;
};

#endif
