//
// Created by Viktor Hellman on 2017-03-31.
//

#ifndef LAB1_STATE_H
#define LAB1_STATE_H


#include <vector>

using namespace std;

class State {


public:
    //constructors
    State() = default;

    State( const vector<unsigned short int>& theNumbers ) :
           theBoard_(theNumbers) { setId(theNumbers); }

    State( const vector<unsigned short int>& theNumbers, shared_ptr<State> theParent, unsigned short int numberOfMoves ) :
                        theBoard_(theNumbers), parent_(theParent), g_(numberOfMoves) { setId(theNumbers); }

    //destructor
    ~State() = default;


    //getters
    vector<unsigned short int> getBoard() const { return theBoard_; } ;
    short unsigned int getCost() const { return cost_; }
    short unsigned int getG() const { return g_; }
    short unsigned int getH() const { return h_; }
    unsigned long int getId() const { return id_; }
    bool isTheSolution() const { return isSolution; }

    //setters
    void setH(const int& newH);
    void setG(const int& newG);
    void setCost();
    void setSolutionTrue() { isSolution = true; }


    //member functions
    short int findEmptyBlock() const ;//the Search of the Holy Zero
    void print(  ) const ; //const vector<unsigned short int>& theState


    const State& operator=(State s);
    friend bool operator<( const State& lhs, const State& rhs ){ return lhs.getCost() < rhs.getCost(); }
    //friend bool operator()(const State& lhs, const State& rhs ){ return lhs.getCost() < rhs.getCost(); }


    struct Comparator {
        bool operator()(const State &lhs, const State &rhs) {
            return lhs.getCost() > rhs.getCost();
        }
    };

private:
    shared_ptr<State> parent_;
    vector<unsigned short int> theBoard_;
    unsigned long int id_ = 0;
    int h_ = 0; //h -evaluation function
    int g_ = 0; //steps from starting state. That is, the number of moves.
    int cost_ = 0; //f(n)
    bool isSolution = false;

    void setId( const vector<unsigned short int>& theState ) ;
    void printBoard() const ;
};



#endif //LAB1_STATE_H
