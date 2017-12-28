#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include "graph.h"
#include "variable.h"
#include "function.h"
#include <queue>
#include <cmath>
#include <math.h>
#include <iterator>
#include <sstream>
#include <algorithm>

using namespace std;

template <class Container>
void split1(const string& str, Container& cont)
{
    istringstream iss(str);
    copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(cont));
}

// helper function that checks whether the given string is number or not.
bool isNumber(const string& s)
{
    char* end = 0;
    double val = strtod(s.c_str(), &end);
    return end != s.c_str() && val != HUGE_VAL;
}

int Graph::getVariable(string inp){
    int res;
    if( isNumber(inp) ){
        double val = stod(inp.c_str());
        idCount++;
        name[idCount] = inp;
        vars[idCount] = new Variable(idCount, inp, val);
        res = idCount;
        type[idCount] = VARIABLE;
        numCount++;
        vars[idCount]->initialized = 1;
        vars[idCount]->isNum = 1;
    }
    else{
        if(id.find(inp)==id.end()){
            idCount++;
            id[inp] = idCount;
            name[idCount] = inp;
            vars[idCount] = new Variable(idCount, inp);
            res = idCount;
            type[idCount] = VARIABLE;
        }
        else{
            res = id[inp];
        }
    }
    return res;
}

int Graph::getFunction(string fnc){
    idCount++;
    id[fnc] = idCount;
    name[idCount] = fnc;
    type[idCount] = FUNCTION;
    Function *f;
    if(fnc.compare("mult")==0)
        f = new Multiplication(idCount, fnc);
    else if(fnc.compare("add")==0)
        f = new Addition(idCount, fnc);
    else if(fnc.compare("subs")==0)
        f = new Subtraction(idCount, fnc);
    else if(fnc.compare("divide")==0)
        f = new Division(idCount, fnc);
    else if(fnc.compare("sin")==0)
        f = new Sine(idCount, fnc);
    else if(fnc.compare("cos")==0)
        f = new Cosine(idCount, fnc);
    else if(fnc.compare("identity")==0)
        f = new Identity(idCount, fnc);
    else if(fnc.compare("tan")==0)
        f = new Tangent(idCount, fnc);
    else if(fnc.compare("acos")==0)
        f = new ArcCosine(idCount, fnc);
    else if(fnc.compare("asin")==0)
        f = new ArcSine(idCount, fnc);
    else if(fnc.compare("atan")==0)
        f = new ArcTangent(idCount, fnc);
    else if(fnc.compare("exp")==0)
        f = new Exponential(idCount, fnc);
    else if(fnc.compare("log")==0)
        f = new Log(idCount, fnc);
    else if(fnc.compare("log10")==0)
        f = new Log10(idCount, fnc);
    else if(fnc.compare("pow")==0)
        f = new Power(idCount, fnc);
    else if(fnc.compare("sqrt")==0)
        f = new Sqrt(idCount, fnc);
    fncs[idCount] = f;
    return idCount;
}

void Graph::addAssignment(string lvalue, string rvalue,long status) {

    vector<string> words;
    split1(rvalue,words);
    //<var> = <var>
    if(status==1){
        addUnaryFunction("identity",words[0],lvalue);
    }
    //<var> = <func> <var>
    else if(status==2){
        addUnaryFunction(words[0],words[1],lvalue);
    }
    //var = <func> <var> <var>
    else if(status==3){
        addBinaryFunction(words[0],words[1],words[2],lvalue);
    }

}

void Graph::addUnaryFunction(string fnc, string inp, string out){

    int fId = getFunction(fnc);
    int inpId = getVariable(inp);
    int outId = getVariable(out);
    fncs[fId]->addInput(vars[inpId]);
    fncs[fId]->setOutput(vars[outId]);

    vars[inpId]->addTo(fncs[fId]);
    vars[outId]->setFrom(fncs[fId]);
}

void Graph::addBinaryFunction(string fnc, string inp1, string inp2, string out){

    int fId = getFunction(fnc);
    int inpId1 = getVariable(inp1);
    int inpId2 = getVariable(inp2);
    int outId = getVariable(out);
    fncs[fId]->addInput(vars[inpId1]);
    fncs[fId]->addInput(vars[inpId2]);
    fncs[fId]->setOutput(vars[outId]);

    vars[inpId1]->addTo(fncs[fId]);
    vars[inpId2]->addTo(fncs[fId]);
    vars[outId]->setFrom(fncs[fId]);

}

void Graph::readGraph(char argv[]){

    ifstream infile(argv);

    string line;
    getline(infile, line);

    vector<string> firstLine;
    split1(line,firstLine);
    if(firstLine[0]=="input"){
        inputNodes.push_back(getVariable(firstLine[1]));
        while(infile.good()){
            getline(infile, line);
            if(line == "")
                break;
            vector<string> words;
            split1(line,words);
            if(words[0]=="input")
                inputNodes.push_back(getVariable(words[1]));
            else if(words[0]=="output")
                outputNode = getVariable(words[1]);
                //assignment
            else{
                string rValue = "";
                for(int i=0;i<words.size()-2;i++)
                    rValue += words[2+i] + " ";
                addAssignment(words[0],rValue,words.size()-2);
            }
        }
    }
    else{
        cout << "Wrong format: First line must start with string 'input'";
    }

}

vector<int> Graph::topologicalSort() {

    vector< pair<int,int>> nodes;
    vector<int> result;
    //calculate the indegrees of variable nodes
    for (auto it : vars){
        if(it.second->from == nullptr){
            nodes.push_back(make_pair(it.first,0));
        }
        else {
            nodes.push_back(make_pair(it.first, 1));
        }
    }
    //calculate the indegrees of function variables
    for(auto it : fncs){
        nodes.push_back(make_pair(it.first,(int)it.second->inputs.size()));
    }

    while(!nodes.empty()){
        int currentNode;
        int index;
        for(int i=0;i<nodes.size();i++){
            if(nodes[i].second==0){
                currentNode = nodes[i].first;
                index=i;
                if(type[currentNode] == VARIABLE){
                    for(int j = 0;j < vars[currentNode]->to.size();j++){
                        int neighborFunc = vars[currentNode]->to[j]->id;
                        for(int t = 0; t < nodes.size();t++){
                            if(nodes[t].first==neighborFunc){
                                nodes[t].second--;
                                break;
                            }
                        }
                    }
                }
                else if(type[currentNode]== FUNCTION){
                    int neighborVar = fncs[currentNode]->output->id;
                    for(int t = 0; t < nodes.size();t++){
                        if(nodes[t].first==neighborVar){
                            nodes[t].second--;
                            break;
                        }
                    }
                }
                break;
            }
        }
        result.push_back(currentNode);
        nodes.erase(nodes.begin()+index);
    }
    reverse(result.begin(),result.end());
    return result;

}


bool Graph::isCyclic(){
    bool cycledetected = 1;
    for(auto it : vars){
        if(it.second->from == nullptr)
            cycledetected = 0;
    }
    return cycledetected;
}

double Graph::forwardPass(vector<string> inputNames,vector<string> inputValues){


    int varCount = numCount; //counts the number of variables to which a number is assigned

    //set the values of inputs
    for(int i=0;i<inputNames.size();i++){
        unordered_map<string,int>::iterator it;
        it = id.find(inputNames[i]);

        // Check if iterator points to end of map
        if (it != id.end())
        {
            vars[it->second]->value = stod(inputValues[i]);
            vars[it->second]->initialized = 1;
            varCount++;
        }
        else
        {
            cout << "Element Not Found" << endl;
        }
    }

    while(varCount != vars.size()){
        for (auto it : fncs){
            int initCount = 0;
            for(int j=0;j < (*(it.second)).inputs.size();j++){
                if((*((*(it.second)).inputs[j])).initialized == 0)
                    initCount++;
            }
            //means that inputs of current function are ready
            if((initCount == 0) && (it.second)->processed==0){
                (*(it.second)).doForward();
                varCount++;
            }
        }
    }
    for (auto it : vars){
        if(it.second->isNum == 0)
            it.second->initialized = 0;
    }

    for (auto it : fncs)
        it.second->processed = 0;

    return vars[outputNode]->value;
}

void Graph::backwardPass(){
    vector<int> initVec;
    for(int i=0;i<topologicalSort().size();i++){
        initVec.push_back(topologicalSort()[i]);
    }
    //initialize the derivatives
    for(auto it : vars){
        if(it.first==outputNode){
            it.second->derivative=1;
        }
        else{
            it.second->derivative=0;
        }
    }
    //skip the output variable, we've done it above which is df_df
    for(int i=1;i<initVec.size();i++){
        if(type[initVec[i]] == VARIABLE){
            vector<int> visitedFuncIds;
            for(int j=0;j<vars[initVec[i]]->to.size();j++){
                bool visited = 0;
                for(int t = 0;t<visitedFuncIds.size();t++){
                    if(visitedFuncIds[t] ==vars[initVec[i]]->to[j]->id)
                        visited = 1;
                }
                if(!visited){
                    vars[initVec[i]]->derivative += (vars[initVec[i]]->to[j]->doBackward(initVec[i]))*(vars[initVec[i]]->to[j]->output->derivative);
                    visitedFuncIds.push_back(vars[initVec[i]]->to[j]->id);
                }
            }
        }
    }

};

Graph::~Graph() {

}