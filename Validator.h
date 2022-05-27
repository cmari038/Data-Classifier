#ifndef VALIDATOR_H
#define VALIDATOR_H
#include "Classifier.h"
#include <vector>

class Validator {

    private:
    Classifier* NN; // validator will have classifier input as a data member pointer
    int rows;
    int columns;
    vector<int> featureSubset;
    double dataSet[2048][64]; // maximum # of instances and features according to pdf

    public:

    Validator() {     // constructor which takes in a subset of features
        rows = 0;
        columns = 0;
        NN = new Classifier();
    }

    
    void EmptyVector() {    // clears vector for next subset
        featureSubset.clear();
    }
    
    void DataInput(const string& file) {    // gets dataset as input from textfile
    
    double info;
    ifstream FS; 
    FS.open(file);

    while(FS >> info) {

        if((info == 1 || info == 2) && columns != 0) {
            ++rows;
            columns = 0;
        }

        dataSet[rows][columns] = info; 
        ++columns;

    }

    FS.close();

    ++rows;
}

void getTrainingData() {    // gets training data and puts into classifier

    int counter = 0;
    vector<double> v;

    for(int i = 0; i < rows; ++i) {

        v.push_back(dataSet[i][0]);
        
        for(int j = 0; j < featureSubset.size(); ++j) {

            v.push_back(dataSet[i][featureSubset.at(j)]);
        }

       // NN->emptyVector();

        NN->train(v);

        v.clear();
    }
}

double classifierAccuracy() {   // performs leave one out validation and finds accuracy of NN

    int correctClassification = 0;
    int correctLabel;

    if(featureSubset.size() == 0) {
        return defaultRate();
    }

    getTrainingData();

    for(int i = 0; i < rows; ++i) {     // finds label of each object in dataset 
        
        correctLabel = dataSet[i][0];
        
        if(NN->test(i) == correctLabel) {
            ++correctClassification;
        }
    }

    NN->emptyVector();  // empty classifier's data for next set of data to test

    return (correctClassification / static_cast<double>(rows)) * 100;
}

void SubsetInput(vector<int>& v) {
      for(int i = 0; i < v.size(); ++i) {
            featureSubset.push_back(v.at(i));
        }
}

int numFeatures() {
    return columns - 1;
}

int numInstances() {
    return rows;
}


void normalize() {      // normalizes training data by finding mean and standard deviation

    double mean = 0;
    double std = 0;
    vector<double> averages;
    vector<double> deviations;

    // mean

    for(int j = 1; j < columns; ++j) {

        for(int i = 0; i < rows; ++i) {
            mean = mean + dataSet[i][j];
        }

       averages.push_back(mean/rows);
       mean = 0;
    }

    // standard deviation

    for(int j = 1; j < columns; ++j) {

        for(int i = 0; i < rows; ++i) {
            std += pow(dataSet[i][j] - averages.at(j-1), 2);
        }

        deviations.push_back(sqrt( std / (rows - 1) ));
        std = 0;
    }

    // normalization

    for(int j = 1; j < columns; ++j) {

        for(int i = 0; i < rows; ++i) {
           dataSet[i][j] = ( dataSet[i][j] - averages.at(j-1) ) / deviations.at(j-1);
        }
    }

}

double defaultRate() {  // calculates default rate
    double counter1 = 0;
    double counter2 = 0;

    for(int i = 0; i < rows; ++i) {
        if(dataSet[i][0] == 1) {
            ++counter1;
        }

        else if(dataSet[i][0] == 2) {
            ++counter2;
        }
    }

    if(counter1 >= counter2) {
        return (counter1 / static_cast<double>(rows)) * 100;
    }

    else {
         return (counter2 / static_cast<double>(rows)) * 100;
    }
}


};

#endif