#ifndef Classifier_h
#define Classifier_h
#include <iostream>
#include "Feature.h"
#include <fstream>
#include <cmath>
using namespace std;

class Classifier {

private:

int trainingColumn;
vector<vector<double>> trainingData;



public:

void train(vector<double> instance) {
    trainingColumn = instance.size();
    trainingData.push_back(instance);
}


int test(int test) {

    double distance = 0;
    double minDistance = 0;
    int label;

    for(int i = 0; i < trainingData.size(); ++i) {
        if(i != test) { 
            
            for(int j = 1; j <= trainingColumn-1; ++j) {

                distance += sqrt(pow(trainingData.at(test).at(j) - trainingData.at(i).at(j), 2)); 
            
                if(minDistance < distance) {
                    minDistance = distance;
                    label = trainingData.at(i).at(0);
                }
            }

        }
    }

    return label;
}


};

#endif 