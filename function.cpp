#include <iostream>
#include "function.h"
#include <math.h>

Function::Function() {

}

Function::Function(int _id, string _name){

    this->id = _id;
    this->name = _name;

}

Function::~Function(){

}

void Function::addInput(Variable* _input){
    this->inputs.push_back(_input);
}

void Function::setOutput(Variable* _output) {
    this->output = _output;
}

vector<Node*> Function::getIncomings() {

}

vector<Node*> Function::getOutgoings() {

}


Multiplication::Multiplication(int _id, string _name){
    this->id = _id;
    this->name = _name;
}


void Multiplication::doForward() {
    (*(this->output)).value = ((*(this->inputs[0])).value)*((*(this->inputs[1])).value);
    (*(this->output)).initialized = 1;
    this->processed = 1;
}
double Multiplication::doBackward(int currentVar) {
    if(this->inputs[0]->id==currentVar && this->inputs[1]->id==currentVar ){
        return 2*this->inputs[0]->value;
    }
    else{
        if(this->inputs[0]->id==currentVar){
            return this->inputs[1]->value;
        }
        else{
            return this->inputs[0]->value;
        }
    }

}

Addition::Addition(int _id, string _name){
    this->id = _id;
    this->name = _name;
}

void Addition::doForward(){
    (*(this->output)).value = ((*(this->inputs[0])).value) + ((*(this->inputs[1])).value);
    (*(this->output)).initialized = 1;
    this->processed = 1;
}
double Addition::doBackward(int currentVar){
    if(this->inputs[0]->id==currentVar && this->inputs[1]->id==currentVar){
        return 2;
    }
    else{
        return 1;
    }

}

Sine::Sine(int _id, string _name){
    this->id = _id;
    this->name = _name;
}
void Sine::doForward(){
    (*(this->output)).value = sin((*(this->inputs[0])).value);

    (*(this->output)).initialized = 1;
    this->processed = 1;
}
double Sine::doBackward(int){
    return cos(this->inputs[0]->value);
}

Subtraction::Subtraction(int _id, string _name){
    this->id = _id;
    this->name = _name;
}
void Subtraction::doForward(){
    (*(this->output)).value = ((*(this->inputs[0])).value) - ((*(this->inputs[1])).value);
    (*(this->output)).initialized = 1;
    this->processed = 1;
}
double Subtraction::doBackward(int currentVar){
    if(this->inputs[0]->id==currentVar && this->inputs[1]->id==currentVar){
        return 0;
    }
    else{
        if(this->inputs[0]->id==currentVar){
            return 1;
        }
        else{
            return -1;
        }
    }

}

Division::Division(int _id, string _name){
    this->id = _id;
    this->name = _name;
}
void Division::doForward(){
    (*(this->output)).value = ((*(this->inputs[0])).value)/((*(this->inputs[1])).value);
    (*(this->output)).initialized = 1;
    this->processed = 1;
}
double Division::doBackward(int currentVar){
    if(this->inputs[0]->id==currentVar && this->inputs[1]->id==currentVar){
        return 0;
    }
    else{
        // f(x) = x/a
        if(this->inputs[0]->id==currentVar){
            return 1/(this->inputs[1]->value);
        }
            //f(x) = a/x
        else{
            //return (-this->inputs[0]->value)*pow(this->inputs[1]->value,-2);
            return (-this->inputs[0]->value)/pow(this->inputs[1]->value,2);
        }
    }

}

Cosine::Cosine(int _id, string _name){
    this->id = _id;
    this->name = _name;
}
void Cosine::doForward(){
    (*(this->output)).value = cos((*(this->inputs[0])).value);
    (*(this->output)).initialized = 1;
    this->processed = 1;
}
double Cosine::doBackward(int){
    return -sin(this->inputs[0]->value);
}

Identity::Identity(int _id, string _name){
    this->id = _id;
    this->name = _name;
}
void Identity::doForward(){
    (*(this->output)).value = (*(this->inputs[0])).value;
    (*(this->output)).initialized = 1;
    this->processed = 1;
}
double Identity::doBackward(int){
    return 1;
}

Tangent::Tangent(int _id, string _name){
    this->id = _id;
    this->name = _name;
}
void Tangent::doForward(){
    (*(this->output)).value = tan((*(this->inputs[0])).value);
    (*(this->output)).initialized = 1;
    this->processed = 1;
}
double Tangent::doBackward(int){
    return 1/pow(cos(this->inputs[0]->value),2);
}

ArcCosine::ArcCosine(int _id, string _name){
    this->id = _id;
    this->name = _name;
}
void ArcCosine::doForward(){
    (*(this->output)).value = acos((*(this->inputs[0])).value);
    (*(this->output)).initialized = 1;
    this->processed = 1;
}
double ArcCosine::doBackward(int){
    return (-1)/(sqrt(1-pow(this->inputs[0]->value,2)));
}

ArcSine::ArcSine(int _id, string _name){
    this->id = _id;
    this->name = _name;
}
void ArcSine::doForward(){
    (*(this->output)).value = asin((*(this->inputs[0])).value);
    (*(this->output)).initialized = 1;
    this->processed = 1;
}
double ArcSine::doBackward(int){
    return 1/(sqrt(1-pow(this->inputs[0]->value,2)));
}

ArcTangent::ArcTangent(int _id, string _name){
    this->id = _id;
    this->name = _name;
}
void ArcTangent::doForward(){
    (*(this->output)).value = atan((*(this->inputs[0])).value);
    (*(this->output)).initialized = 1;
    this->processed = 1;
}
double ArcTangent::doBackward(int){
    return 1/(1+pow(this->inputs[0]->value,2));
}


Exponential::Exponential(int _id, string _name){
    this->id = _id;
    this->name = _name;
}
void Exponential::doForward(){
    (*(this->output)).value = exp((*(this->inputs[0])).value);
    (*(this->output)).initialized = 1;
    this->processed = 1;
}
double Exponential::doBackward(int){
    return exp(this->inputs[0]->value);
}

Log::Log(int _id, string _name){
    this->id = _id;
    this->name = _name;
}
void Log::doForward(){
    (*(this->output)).value = log((*(this->inputs[0])).value);
    (*(this->output)).initialized = 1;
    this->processed = 1;
}
double Log::doBackward(int){
    return 1/this->inputs[0]->value;
}

Log10::Log10(int _id, string _name){
    this->id = _id;
    this->name = _name;
}
void Log10::doForward(){
    (*(this->output)).value = log10((*(this->inputs[0])).value);
    (*(this->output)).initialized = 1;
    this->processed = 1;
}
double Log10::doBackward(int){
    return 1/((this->inputs[0]->value)*(log(10)));
}

Power::Power(int _id, string _name){
    this->id = _id;
    this->name = _name;
}
void Power::doForward(){
    (*(this->output)).value = pow((*(this->inputs[0])).value,(*(this->inputs[1])).value);
    (*(this->output)).initialized = 1;
    this->processed = 1;
}
double Power::doBackward(int currentVar){
    if(this->inputs[0]->id==currentVar && this->inputs[1]->id==currentVar){
        return (pow(this->inputs[0]->value,this->inputs[0]->value))*(log(this->inputs[0]->value)+1);
    }
    else{
        //polinomial derivation : x^a -> a*x^(a-1)
        if(this->inputs[0]->id==currentVar){
            return (this->inputs[1]->value)*(pow(this->inputs[0]->value,this->inputs[1]->value - 1));
        }
            //exponential function derivation  :  a^x -> a^x * ln(a)
        else{
            return pow(this->inputs[0]->value,this->inputs[1]->value)*(log(this->inputs[0]->value));
        }
    }

}

Sqrt::Sqrt(int _id, string _name){
    this->id = _id;
    this->name = _name;
}
void Sqrt::doForward(){
    (*(this->output)).value = sqrt((*(this->inputs[0])).value);
    (*(this->output)).initialized = 1;
    this->processed = 1;
}

double Sqrt::doBackward(int){
    return 1/(2*sqrt(this->inputs[0]->value));
}