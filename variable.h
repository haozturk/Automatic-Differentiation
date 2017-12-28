#ifndef VARIABLE_H
#define VARIABLE_H

#include <vector>
#include <string>

#define PI 3.14159265
#define INF 0x3f3f3f3f
using namespace std;

class Function;

/*
Node class is created in order to construct directed graph structure
*/
class Node{
public:
    // represents id of the node
    int id;

    // represents name of the node
    string name; 

    // returns the incomming edges of the node
    virtual vector<Node *> getIncomings() = 0; 

    // returns the outgoing edges of the node
    virtual vector<Node *> getOutgoings() = 0;

    // destructor
    ~Node();
};

/*
Subclass of node class and represents the variables.
Due to the different functionality, we have variable and function classes.
*/
class Variable : public Node{

public:

    // represents the value of the variable
    double value;

    // represents the partial derivative value of the variable
    // i.e. (d output/ d variable)
    double derivative;

    //if a value is assigned to a
    bool initialized = 0;

    bool isNum = 0;


    // represents that which function determines the variable
    // it will be null for inputs or constants
    Function *from;

    // represents the list of functions that takes the variable as input
    vector<Function *> to;

    Variable(); // default constructor
    Variable(int _id, string _name, double _value = INF); // custom constructor
    ~Variable(); // destructor

    // sets the from pointer
    void setFrom(Function *_from);

    // adds the given function to 'to' vector
    void addTo(Function *_to);

    // these functions are inherited features from node class
    vector<Node *> getIncomings();
    vector<Node *> getOutgoings();
};

#endif // VARIABLE