//
//
// Created by Viktor Hellman on 2017-03-31.
//
//
#include "State.h"

#include <iostream>
#include <ctime>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

class PuzzleSolver {

public:
    //constructors
    PuzzleSolver() = default;
    PuzzleSolver( const vector<unsigned short int>& sentState, const vector<unsigned short int>& sentGoal );

    //destructor
    ~PuzzleSolver() = default;

    //getters
    State getCurrentState(){ return currentState_; }
    double getDuration(){ return timeToComplete; }
    unsigned short int numberOfCheckedStates() { return checkedStates_; }

    //member functions
    State solveWithAStar();


private:
    State currentState_;
    const vector<unsigned short int> goalState_;
    clock_t startTime, endTime;
    double timeToComplete;
    unsigned short int checkedStates_ = 0;

    //auxilar member functions
    void findSuccessorsTo( const State& theState, vector<State>& theSuccessors );
    void allowedMoves(const short int& emptyBlockIn, vector<unsigned short int>& theMoves);
    State createNewState(const State& theCurrentState, const unsigned short int& numberToSwitch, const unsigned short int& emptyBlockAt );
    bool checkIfGoal(const State& theState);
};

