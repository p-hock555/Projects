# hw-hocking

The rational class constructs a rational number in the form (numerator/denominator) and implements functions to perform many different operations on these numbers. 

Compile:
g++ -Wall -std=c++17 rational.cpp test-rational.cpp -o test-rational

Run:
./test-rational > test-rational.out

Compare the expected and output files:
diff test-rational.out test-rational.exp

The reversi class implements the reversi game. It includes a game board class, game class (with the game functions and board as a private data member), a checkpoint class, and a square class for the individual pieces on the board. The reversi game is carried out with any even dimension, which can be declared using the
command line.

Compile:
g++ -Wall -std=c++17 reversi.cpp test-reversi.cpp -o test-reversi

Run:
./test-reversi
