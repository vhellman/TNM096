//
// Created by Viktor Hellman on 2017-03-31.
//

#include "PuzzleSolver.h"
#include "State.h"


const void showMenu();
short int readInput();
const void doAction(short int& action);
bool validate(const short int& action);
const void solvePuzzle(PuzzleSolver currentPuzzle);

//GLOBAL CONSTANTS: Goal and the Starting State
const vector<unsigned short int> GOAL_STATE = { 1, 2, 3, 4, 5, 6, 7, 8, 0 };

//const vector<unsigned short int> STARTING_STATE = { 1, 2, 3, 0, 6, 5, 7, 8, 4 }; //unsolvable
const vector<unsigned short int> STARTING_STATE = { 1, 2, 3, 4, 5, 6, 0, 7, 8 }; //solvable

int main()
{
    //declatarions
    PuzzleSolver s(STARTING_STATE, GOAL_STATE);
    short int action = 0;

    //RUNTIME
    while( action != 5 )
    {
        showMenu();
        action = readInput();

        switch (action) {
            case (1):
                s.getCurrentState().print(); //print the starting state
                break;

            case (2):
                solvePuzzle(s);
                break;


            case(5):
                cout << endl <<"Exiting." << endl
                     << "Goodbye!" << endl << endl;
                break;

            default:
                break;
        }
    }

    return 0;
}

/************************************************************************************************************
 *
 *                                       SUPPORTING FUNCITONS
 *
 ***********************************************************************************************************/

/*
 * Function that shows the menu
 */
const void showMenu(){
    cout << "THE 8-STAR PUZZLE SOLVER" << endl
         << "**********************************" << endl << endl;

    cout << "Menu:" << endl
         << "1. Show the starting state" << endl
         << "2. Find solution" << endl << endl
         << "5. Quit" << endl << endl;
}
/*
 * Reads input and returns the choice
 */
short int readInput()
{
    short int input;

    cout << "Your action: ";
    cin >> input;

    while( !validate(input) ) {
        cout << "Your action: ";
        cin >> input;
    }

    return input;
}


/*
 * Function to call the solver
 */

const void solvePuzzle(PuzzleSolver currentPuzzle)
{
    State theSolution;
    theSolution = currentPuzzle.solveWithAStar();
    theSolution.print();

    if ( theSolution.isTheSolution() ) {
        cout << "Hej!" << endl;
        cout << endl << "Solution is: " << endl;
        //print puzzle to check if ok
        theSolution.print();
        cout << "Solved in " << currentPuzzle.getDuration() << " seconds." << endl << endl;
    }
    else {
        cout << endl << "Not solvable!" << endl
             << "Search took " << currentPuzzle.getDuration() << " to finish." << endl << endl;
    }
}

/*
 * Function to check if input is correct
 */
bool validate(const short int& action){
    if( action == 1 || action == 2 || action == 5 ){
        return true;
    }
    else{
        cout << "Wrong input. Try again!" << endl;
        return false;
    }
}