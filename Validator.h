#ifndef VALIDATOR_H
#define VALIDATOR_H
#include "Classifier.h"
#include "Feature.h"

class Validator {

    private:
    Classifier* NN; // validator will have classifier input as a data member pointer
    int rows;
    int columns;
    vector<int> featureSubset;
    double dataSet[2048][64]; // maximum # of instances and features according to pdf

    public:

    Validator(vector<int>& v) {     // constructor which takes in a subset of features
        rows = 0;
        columns = 0;
        NN = new Classifier();

        for(int i = 0; i < v.size(); ++i) {
            featureSubset.push_back(v.at(i));
        }
    }

    
    void DataInput(const string& file) {    // gets dataset as input
    
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

    int featureID = 1;
    int counter = 0;
    vector<double> v;

    for(int i = 0; i < rows; ++i) {

        v.push_back(dataSet[i][0]);
        
        for(int j = 0; j < featureSubset.size(); ++j) {

            v.push_back(dataSet[i][featureSubset.at(j)]);
        }

        NN->train(v);

        v.clear();
    }
}

double classifierAccuracy() {   // performs K-fold validation function

    int correctClassification = 0;
    int correctLabel;

    getTrainingData();
    NN -> normalize();
    //NN -> print();

    for(int i = 0; i < rows; ++i) {
        
        correctLabel = dataSet[i][0];
        
        if(NN->test(i) == correctLabel) {
            ++correctClassification;
        }
    }

    cout << "Accuracy: ";

    return correctClassification / static_cast<double>(rows);
}

/*void print() {
    
    for(int i = 0; i < rows; ++i) {
        for(int j = 0; j < columns; ++j) {
            cout << dataSet[i][j] << " ";
        }

        cout << endl;
    }
} */


};

#endif