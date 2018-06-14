#ifndef TRANSITION_FUNCTION_H
#define TRANSITION_FUNCTION_H

#include "transition.h"
#include "direction.h"
#include <string>
#include <vector>

using namespace std;

class TransitionFunction
{
private:
    vector <Transition> transitions;
public:
    void load (ifstream& file, bool &valid);
    string destinationState (int index) const;
    bool findTransition (string sourceState, char readCharacter, string &destinationState, char &writeCharacter, direction &moveDirection) const;
    bool validate (string state) const;
    void view () const;
    char readCharacter (int index) const;
    char writeCharacter (int index) const;
    string sourceState (int index) const;
    int size () const;
};

#endif
