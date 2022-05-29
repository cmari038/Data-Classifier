#ifndef Classifier_h
#define Classifier_h
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

class Classifier {

private:

int trainingColumn;     // size of each vector in training data
vector< vector<double> > trainingData;  // stores training data



public:

Classifier() {
    trainingColumn = 0;
}

void train(vector<double>& instance) {  // train method which takes in an instance and adds it to vector data member
    trainingColumn = instance.size();
    trainingData.push_back(instance);
}


double test(int index) {     // test method which labels a training instance based on indicated index

// based off algorithm in discussion slides

    double distance = 0;
    double minDistance = 0;
    double label;
    int neighbor;

    for(int i = 0; i < trainingData.size(); ++i) {
       
        if(i != index) {
            
            for(int j = 1; j < trainingColumn; ++j) {
                 distance += pow(trainingData.at(index).at(j) - trainingData.at(i).at(j), 2);    // gets distance = (feature_test - feature_j)^2
            }

            distance = sqrt(distance);  // distance = square root(distance)

            if(minDistance == 0) {
                minDistance = distance;
            }
            
            else if(distance < minDistance) {
                    minDistance = distance;
                    label = trainingData.at(i).at(0);
                    neighbor = i;
                }
        }

        distance = 0;
    }

    return label;
}

void emptyVector() {
    trainingData.clear();
    trainingColumn = 0;
}


};

#endif 