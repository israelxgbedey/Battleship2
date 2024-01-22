# Battle Ship Assignment #

Your assigment is to solve the battleship problem. you have a 100x100 grid with 25 ships.  You have to find each ship in less moves than the control. For every Guess of the board it will increment the move counter

Your assignment is to implement the `solve` method in lib/game.h for the `AssignmentGame` implementation of `BaseGame`

``` c++
class AssignmentGame : public BaseGame {
    int solve() override {
        //IMPLEMENT YOUR SEARCH ALGORITHM HERE
        return SHIP_COUNT;
    }
}
```

to compile the assignment use 
`g++ -g -I ../lib/ main.cpp board.cpp game.cpp -o app`

to run the assignment run
`./app`

If you get a failure, your grade for the assignment is an F
for every guess above the control you lose a letter grade. The output of the program is your letter grade
