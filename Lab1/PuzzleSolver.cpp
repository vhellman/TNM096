//
// Created by Viktor Hellman on 2017-03-31.
//

#include "PuzzleSolver.h"
#include "State.h"


//Standard constructor
PuzzleSolver::PuzzleSolver(const vector<unsigned short int> &sentState, const vector<unsigned short int> &sentGoal) :
                           goalState_(sentGoal) {
    State startingState(sentState);
    currentState_ = startingState;
}



/*
 *  A-star Algorithm Solver
 */
State PuzzleSolver::solveWithAStar() {

    //list to store successors of a given state
    vector<State> theSuccessors;

    //to keep track of visited states
    unsigned short int numberOfCheckedStates = 0;

    //initialize the open list
    priority_queue< State, vector<State>, State::Comparator>  openList;
    //initialize the closed list
    unordered_map<unsigned long int, State> closedList;

    /* ****************************************************************************
     *                                   RUNTIME
     *****************************************************************************/

    //start the clock
    startTime = clock();

    //put the starting node on the open list
    openList.push( currentState_ );


    //while the open list is not empty
    while( !openList.empty() )
    {
        //find the node with the least f on the open list, pop it off the list
        currentState_ = openList.top();
        openList.pop();

        checkedStates_++;

        //generate successors to current state and set their parents to currentState
        findSuccessorsTo(currentState_, theSuccessors);

        //for each successor
        for( const State& successor: theSuccessors )
        {
            /*
            if( successor.isTheSolution() )
            {
                //solution found, stop the timer
                endTime = clock();
                //calculate duration in seconds
                timeToComplete = (endTime - startTime) / (double) CLOCKS_PER_SEC;
                successor.print();

                //if soulution is found, return solution state.
                return successor;
            }
             */

            //check if a successor is on the closed list => it has been visited before
            auto temp = closedList.find( successor.getId() );

            if(temp != closedList.end() && temp->second.getCost() < successor.getCost() ){
                continue;
            }

            //add if it is on the closed list but lower?
            openList.push(successor);
        }
        //add the current state to the closed list
        closedList.insert( {currentState_.getId(), currentState_} );
    }

    //no solution found, stop the timer
    endTime = clock();
    //calculate duration in seconds
    timeToComplete = (endTime - startTime) / (double) CLOCKS_PER_SEC;

    cout << "No solution found. Searched " << numberOfCheckedStates << " states." << endl
         << "Exiting..." << endl;

    return currentState_;
}

/*
 * Function to generate successors of a given state
 * Returns a vector of States
 */

//TODO: Refactor this shit!
void PuzzleSolver::findSuccessorsTo( const State& theState, vector<State>& theSuccessors )
{
    //vector to store the allowed moves
    vector<unsigned short int> theMoves;

    //to store the index of the empty block
    short int emptyBlock;

    //RUNTIME
    emptyBlock = theState.findEmptyBlock();

    allowedMoves(emptyBlock, theMoves);

    for( auto toMove : theMoves )
    {
        State newState = createNewState(theState, toMove, emptyBlock);
        if(newState.getBoard() == goalState_)
        {
            newState.setSolutionTrue();
            cout << "Found the solution in " << newState.getG() << " steps." << endl
                 << "Checked " << checkedStates_ << " states!" << endl;

            newState.setH(0);
            newState.setCost();

            theSuccessors.clear();
            theSuccessors.push_back(newState);

            break;
        }

        newState.setH(0);
        newState.setCost( );

        theSuccessors.push_back(newState);
    }
}
/** *************************
 *
 *
 *
    & initialize the open list
    & initialize the closed list
    & put the starting node on the open list (you can leave its f at zero)

    & while the open list is not empty
    & find the node with the least f on the open list, call it "q"
    & pop q off the open list
    & generate q's 8 successors and set their parents to q
    & for each successor
    & if successor is the goal, stop the search
    & successor.g = q.g + distance between successor and q
    & successor.h = distance from goal to successor
    & successor.f = successor.g + successor.h

    if a node with the same position as successor is in the OPEN list \
            which has a lower f than successor, skip this successor
    if a node with the same position as successor is in the CLOSED list \
            which has a lower f than successor, skip this successor
    otherwise, add the node to the open list
    end
    push q on the closed list
    end **/

/* *********************************************************************************************************************
 *
 *                                              AUXILAR MEMBER FUNCTIONS
 *
 **********************************************************************************************************************/

void PuzzleSolver::allowedMoves(const short int& emptyBlockIn, vector<unsigned short int>& theMoves)
{
    switch (emptyBlockIn) {
        case (0):
            theMoves = {1, 3};
            break;
        case (1):
            theMoves = {0, 2, 4};
            break;
        case(2):
            theMoves = {1, 5};
            break;
        case(3):
            theMoves = {0, 4, 6};
            break;
        case(4):
            theMoves = {1, 3, 5, 7};
            break;
        case(5):
            theMoves = {2, 4, 8};
            break;
        case(6):
            theMoves = {3, 7};
            break;
        case(7):
            theMoves = {4, 6, 8};
            break;
        case(8):
            theMoves = {5, 7};
            break;

        default: break;
    }
}

State PuzzleSolver::createNewState(const State& theCurrentState, const unsigned short int& blockToMove, const unsigned short int& emptyBlockAt )
{
    //vector to store a temporary board to switch with
    vector<unsigned short int> tempBoard;

    //set up pointer to parent state
    shared_ptr<State> parentState;
    parentState = make_shared<State>(theCurrentState);

    tempBoard = theCurrentState.getBoard();

    swap(tempBoard[blockToMove], tempBoard[emptyBlockAt]);

    State newState( tempBoard, parentState, theCurrentState.getG() + 1 ) ;

    return newState;
};

bool PuzzleSolver::checkIfGoal(const State& theState){
    if(theState.getBoard() == goalState_ ) {
        theState.setSolutionTrue();
        cout << "Found the solution in " << theState.getG() << " steps." << endl
             << "Checked " << checkedStates_ << " states!" << endl;
    }

}