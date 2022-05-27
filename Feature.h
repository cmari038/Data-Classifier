#ifndef FEATURE_H
#define FEATURE_H
#include <iostream>
#include <vector>
#include "Validator.h"
using namespace std;

class Feature {

private:
double accuracy;
vector<int> features; 
int vector_size;    // keeps track of size of vector

public:

Feature() {
    accuracy = 0;
    vector_size = 0;
}

Feature(int featuresCount) {        // constructor used for seocnd choice where set starts with all features
    for(unsigned i = 1; i <= featuresCount; ++i) {
        features.push_back(i);
    }

    vector_size = featuresCount;
    accuracy = 0;
}

void setAccuracy(double val) {
   accuracy = val;
}

double getAccuracy() {
    return accuracy;
}


void Insert(int val) {  // adds new feature to vector
    features.push_back(val);
    ++vector_size;
}

void Remove(int val) {  // removes feature from subset
    vector<int>::iterator i; // iterators learned from geeksforgeeks
    for(i = features.begin(); i <= features.end(); ++i) {
        if(*i == val) {
            features.erase(i);
        }
    }
    --vector_size;
}

bool empty(int val) {   // checks to see if feature is in vector set

    if(vector_size == 0) {
        return true;
    }

    for(unsigned i = 0; i < features.size(); ++i) {
        if(features.at(i) == val) {
            return false;
        }
    } 

    return true;
}

void print(int v) {     // prints out feature set of vector

    std::cout << "{";   
    for(unsigned i = 0; i < features.size(); ++i) {
        std::cout << features.at(i);

        if(i != features.size() - 1) {
            std::cout << ",";
        }
    }
    std::cout << "} ";

    if(v == 1) {
        std::cout << "accuracy is " << accuracy << "%" << endl; 
    }

    else if(v == 2){
        std::cout << "was best, " << "accuracy is " << accuracy << "%";
    }

    
}

Feature* duplicate() {      // returns a copy of a Feature object

    if(vector_size == 0) {
        return new Feature();
    }

    else {
        Feature* f = new Feature();

        for(unsigned i = 0; i < features.size(); ++i) {
            f->Insert(features.at(i));
        }

        //f->setAccuracy(accuracy);
        return f;
    }
}

void getSubset(Validator* v) {  // sends feature subset to validator

    v->SubsetInput(features);

}


};

#endif