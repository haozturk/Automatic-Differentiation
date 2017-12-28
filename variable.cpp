#include <iostream>
#include "variable.h"

Node::~Node(){

}

Variable::Variable(){

}

Variable::Variable(int _id, string _name, double _value) {

    this->id =_id;
    this->name = _name;
    this->value = _value;

}

Variable::~Variable(){

}

void Variable::setFrom(Function *_from){
    this->from = _from;
}

void Variable::addTo(Function *_to) {
    this->to.push_back(_to);
}

vector<Node*> Variable::getIncomings() {

}

vector<Node*> Variable::getOutgoings() {

}
