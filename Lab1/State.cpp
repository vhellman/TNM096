//
// Created by Viktor Hellman on 2017-03-31.
//

#include "State.h"
#include <iostream>
#include <string>
#include <sstream>


using namespace std;

void State::print(  ) const
{
    cout << endl
         << "Puzzle:" << endl
         << "--------------";

    this->State::printBoard();

    cout << endl << endl
         << "id: " << id_ << endl
         << "Moves made: " << g_ << endl
         << "Total cost: " << cost_<< endl << endl;

         //<< "----------------------------------------------------------------------" << endl << endl;
}

void State::printBoard() const {
    auto theBoard = this->getBoard();

    for (int i = 0 ; i < 9 ; i++ ){ //loop puzzle, 0 is the open block.
        if( ( (i) % 3)  == 0 ) { cout << endl; } //if i is at column 3, insert linebreak.

        if( theBoard[i] == 0 ) {
            cout << "  " ;
            continue;
        }
        cout << theBoard[i] << " ";
    }
}


//TODO: Check this!
void State::setId( const vector<unsigned short int>& theState ){
    string temp = "";
    unsigned long int id;
    for ( unsigned short int i = 0 ; i< 9 ; i++ ){
        temp += to_string( theState[i] );
    }

    istringstream(temp) >> id;
    id_ = id;
}



short int State::findEmptyBlock( ) const {

    for(short int i = 0 ; i < 9 ; i++ ){
        if(theBoard_[i] == 0 ) return i;
    }
    return -1;
}

void State::setH(const int& newH) {
    h_ = newH;
}
void State::setG(const int& newG){
    g_ = newG;
}
void State::setCost() {
    cost_ = h_ + g_;
}


const State& State::operator=(State s) {
    this->theBoard_ = s.theBoard_;
    this->parent_ = s.parent_;
    this->id_ = s.id_;
    this->cost_ = s.cost_;
    this->g_= s.g_;
    this->h_ = s.h_;

    return *this;
}
