#include <iostream>
#include <iterator>
#include <sstream>
#include "graph.h"
#include <vector>

template <class Container>
void split1(const string& str, Container& cont)
{
    istringstream iss(str);
    copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(cont));
}

using namespace std;

int main(int argc, char* argv[]){ //BE CAREFUL WITH THE INPUT TAKING(line != "")

    if (argc != 5) {
        cout << "Run the code with the following command: ./project1 [input_file] [output_file]" << endl;
        return 1;
    }

    Graph computationalGraph;
    computationalGraph.readGraph(argv[1]);

    ofstream outputValuesFile;
    outputValuesFile.open (argv[3]);
    outputValuesFile.precision(16);

    ofstream derivativeValuesFile;
    derivativeValuesFile.open (argv[4]);
    derivativeValuesFile.precision(16);

    ifstream infile(argv[2]);
    string line;
    getline(infile, line); //get the first line which determines the order of inputs
    vector<string> words;
    vector<string> inputNames;
    split1(line,words);

    for(int i=0;i < words.size();i++)
        inputNames.push_back(words[i]);
    for(int i=0;i<inputNames.size();i++){
        derivativeValuesFile << "d" << computationalGraph.vars[computationalGraph.outputNode]->name << "/" << "d" << inputNames[i] << " ";
    }
    derivativeValuesFile << endl;
    outputValuesFile << computationalGraph.vars[computationalGraph.outputNode]->name << endl;
    double result;
    while(infile.good()){
        getline(infile,line);
        if(line == "")
            break;
        vector<string> inputValues;
        split1(line,inputValues);
        result= computationalGraph.forwardPass(inputNames,inputValues);

        outputValuesFile << result << endl;


        computationalGraph.backwardPass();
        cout.precision(16);
        for(int i=0;i<computationalGraph.inputNodes.size();i++){
            //cout << computationalGraph.vars[computationalGraph.inputNodes[i]]->derivative << " ";
            derivativeValuesFile << computationalGraph.vars[computationalGraph.inputNodes[i]]->derivative << " ";
        }
        derivativeValuesFile << endl;


    }

    return 0;
}