#ifndef TURINGMACHINE_H
#define TURINGMACHINE_H

#include "tape.h"
#include "inputalphabet.h"
#include "tapealphabet.h"
#include "transitionfunction.h"
#include "state.h"
#include "finalstates.h"
#include <string>
#include <vector>

using namespace std;

class TuringMachine
{
	private:
		Tape tape;
		InputAlphabet inputAlphabet;
		TapeAlphabet tapeAlphabet;
		TransitionFunction transitionFunction;
		State state;
		FinalStates finalStates;
		vector <string> description;
		string initialState;
		string currentState;
		string originalInputString;
		int numberOfTransitions;
		bool valid;
		bool used;
		bool operating;
		bool accepted;
		bool rejected;

	public:
		TuringMachine (string definitionFileName);
		void viewDefinition () const;
		void viewInstantaneousDescription (int maximumNumberOfCells) const;
		void initialize (string inputString);
		void performTransitions (int maximumNumberOfTransitions);
		void terminateOperation ();
		string inputString () const;
		int totalNumberOfTransitions () const;
		bool isValidDefinition () const;
		bool isValidInputString (string value) const;
		bool isUsed () const;
		bool isOperating () const;
		bool isAcceptedInputString () const;
		bool isRejectedInputString () const;
};

#endif
