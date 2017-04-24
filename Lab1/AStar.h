/*
//
// Created by Viktor Hellman on 2017-04-05.
//

#ifndef LAB1_ASTAR_H
#define LAB1_ASTAR_H

#include "State.h"
#include "PuzzleSolver.h"

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

class AStar : public PuzzleSolver {

public:
    //constructors

    //destructor

    void AStarSolver(); //the algorithm
private:
    priority_queue< vector<unsigned long int> > openList_;
    unordered_set< vector<unsigned long int> > closedList_;



};


#endif //LAB1_ASTAR_H



//to implement the Astar algorithm
*/
/** ***********

// A*
initialize the open list
initialize the closed list
put the starting node on the open list (you can leave its f at zero)

while the open list is not empty
    find the node with the least f on the open list, call it "q"
    pop q off the open list
    generate q's 8 successors and set their parents to q
    for each successor
    	if successor is the goal, stop the search
        successor.g = q.g + distance between successor and q
        successor.h = distance from goal to successor
        successor.f = successor.g + successor.h

        if a node with the same position as successor is in the OPEN list \
            which has a lower f than successor, skip this successor
        if a node with the same position as successor is in the CLOSED list \
            which has a lower f than successor, skip this successor
        otherwise, add the node to the open list
    end
    push q on the closed list
end **/
