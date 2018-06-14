CFLAG = -Wall
CC = g++
all: TM

TM: crash.o direction.o finalstates.o inputalphabet.o main.o state.o tape.o tapealphabet.o transition.o transitionfunction.o turingmachine.o uppercase.o inputString.o commands.o
	$(CC)  $^ -o $@

crash.o: crash.cpp
	$(CC) $(CFLAG) -c $<

direction.o: direction.cpp
	$(CC) $(CFLAG) -c $<

finalstates.o: finalstates.cpp
	$(CC) $(CFLAG) -c $<

inputalphabet.o: inputalphabet.cpp
	$(CC) $(CFLAG) -c $<

main.o: main.cpp
	$(CC) $(CFLAG) -c $<

state.o: state.cpp
	$(CC) $(CFLAG) -c $<

tape.o: tape.cpp
	$(CC) $(CFLAG) -c $<

tapealphabet.o: tapealphabet.cpp
	$(CC) $(CFLAG) -c $<

transition.o: transition.cpp
	$(CC) $(CFLAG) -c $<

transitionfunction.o: transitionfunction.cpp
	$(CC) $(CFLAG) -c $<

turingmachine.o: turingmachine.cpp
	$(CC) $(CFLAG) -c $<

uppercase.o: uppercase.cpp
	$(CC) $(CFLAG) -c $<

inputString.o: inputString.cpp
	$(CC) $(CFLAG) -c $<

commands.o: commands.cpp
	$(CC) $(CFLAG) -c $<

clean:
	rm TM *.o