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

int main(int argc, char* argv[]){

    if (argc != 5) {
        cout << "Run the code with the following command: ./project1 [input_file] [output_file]" << endl;
        return 1;
    }

    Graph computationalGraph;
    computationalGraph.readGraph(argv[1]); //construct the graph

    cout << computationalGraph.isCyclic(); //check if there is a cycle

    ofstream outputValuesFile;
    outputValuesFile.open (argv[3]);
    outputValuesFile.precision(16);

    ofstream derivativeValuesFile;
    derivativeValuesFile.open (argv[4]);
    derivativeValuesFile.precision(16);

    if(computationalGraph.isCyclic()){
        outputValuesFile << "ERROR: COMPUTATION GRAPH HAS CYCLE!";
        derivativeValuesFile << "ERROR: COMPUTATION GRAPH HAS CYCLE!";
    }
    else{
        ifstream infile(argv[2]); //read the input file
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
            result= computationalGraph.forwardPass(inputNames,inputValues); //FORWARD PASS

            outputValuesFile << result << endl;

            computationalGraph.backwardPass(); //BACKWARD PASS
            cout.precision(16);
            for(int i=0;i<computationalGraph.inputNodes.size();i++){
                derivativeValuesFile << computationalGraph.vars[computationalGraph.inputNodes[i]]->derivative << " ";
            }
            derivativeValuesFile << endl;
        }

    }
    outputValuesFile.close();
    derivativeValuesFile.close();

    return 0;
}