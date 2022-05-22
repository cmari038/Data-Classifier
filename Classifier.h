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
vector< vector<double> > trainingData;



public:

Classifier() {
    trainingColumn = 0;
}

void normalize() {

    double mean = 0;
    double std = 0;
    vector<double> averages;
    vector<double> deviations;
    int counter = 0;

    //cout << trainingData.size() << " " << trainingColumn << endl;

    for(int j = 1; j < trainingColumn; ++j) {

        for(int i = 0; i < trainingData.size(); ++i) {
            mean = mean + trainingData.at(i).at(j);
        }

       averages.push_back(mean/trainingData.size());
       mean = 0;
    }

    for(int j = 1; j < trainingColumn; ++j) {

        for(int i = 0; i < trainingData.size(); ++i) {
            std += pow(trainingData.at(i).at(j) - averages.at(j-1), 2);
        }

        deviations.push_back(sqrt( std / (trainingData.size() - 1) ));
        std = 0;
    }

    for(int j = 1; j < trainingColumn; ++j) {

        for(int i = 0; i < trainingData.size(); ++i) {
           trainingData.at(i).at(j) = ( trainingData.at(i).at(j) - averages.at(j-1) ) / deviations.at(j-1);
        }
    }

} 

void train(vector<double>& instance) {
    trainingColumn = instance.size();
    trainingData.push_back(instance);
}


double test(int test) {

    double distance = 0;
    double minDistance = 0;
    double label;

    for(int i = 0; i < trainingData.size(); ++i) {
       
        if(i != test) { 

             cout << "Ask if " << test << " is nearest neighbor with " << i << endl;
            
            for(int j = 1; j < trainingColumn; ++j) {
                 distance += pow(trainingData.at(test).at(j) - trainingData.at(i).at(j), 2);
            }

            distance = sqrt(distance);

            if(minDistance == 0) {
                minDistance = distance;
            }
            
            else if(distance < minDistance) {
                    minDistance = distance;
                    label = trainingData.at(i).at(0);
                }
        }

        distance = 0;
    }

    return label;
}

void print() {
    for(int i = 0; i < trainingData.size(); ++i) {
        for(int j = 0; j < trainingColumn; ++j) {
            cout << trainingData.at(i).at(j) << " ";
        }

        cout << endl;
    }
}


};

#endif 