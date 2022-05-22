#ifndef VALIDATOR_H
#define VALIDATOR_H
#include "Classifier.h"
#include "Feature.h"

class Validator {

    private:
    Classifier* NN;
    int rows = 0;
    int columns = 0;
    vector<int> featureSubset;
    double dataSet[2048][64]; // maximum # of instances and features according to pdf

    public:

    
    void DataInput(const string& file) {
    
    double info;
    ifstream FS; 
    FS.open(file);

    while(FS >> info) {

        if((info == 1 || info == 2) && columns != 0) {
            ++rows;
        }

        dataSet[rows][columns] = info; 
        ++columns;

    }

    FS.close();

    normalise();
}

void normalise() {

    double mean = 0;
    double std = 0;
    vector<double> averages;
    vector<double> deviations;

    for(int j = 1; j <= columns-1; ++j) {

        for(int i = 0; i < rows; ++i) {
            mean += dataSet[i][j];
        }

        averages.push_back(mean/rows);
        mean = 0;
    }


    int counter = 0;

    for(int j = 1; j <= columns; ++j) {

        for(int i = 0; i < rows; ++i) {
            std += pow(dataSet[i][j] - averages.at(counter), 2);
        }

       deviations.push_back(std/(rows - 1));
       std = 0;
       ++counter;
    }


    counter = 0;

    for(int j = 1; j <= columns; ++j) {

        for(int i = 0; i < rows; ++i) {
           dataSet[i][j] = ( dataSet[i][j] - averages.at(counter) ) / deviations.at(counter);
        }

       ++counter;
    }

}

void getTrainingData() {

    int featureID = 1;
    int counter = 0;
    vector<double> v;

    while(featureID != 0) {
        cin >> featureID;
        featureSubset.push_back(featureID);
    }

    for(int k = 0; k < featureSubset.size(); ++k) {
         for(int i = 0; i < rows; ++i) {
            for(int j = 1; j <= columns-1; ++j) {
                if(j == k) {
                    v.push_back(dataSet[i][j]);
                }
            }

            NN->train(v);
        }
    }
}

int classifierAccuracy();


};

#endif