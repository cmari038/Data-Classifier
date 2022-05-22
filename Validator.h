#ifndef VALIDATOR_H
#define VALIDATOR_H
#include "Classifier.h"
#include "Feature.h"

class Validator {

    private:
    Classifier* NN;
    int rows;
    int columns;
    vector<int> featureSubset;
    double dataSet[2048][64]; // maximum # of instances and features according to pdf

    public:

    Validator(vector<int>& v) {
        rows = 0;
        columns = 0;
        NN = new Classifier();

        for(int i = 0; i < v.size(); ++i) {
            featureSubset.push_back(v.at(i));
        }
    }

    
    void DataInput(const string& file) {
    
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

    //normalise();
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

    for(int j = 1; j <= columns-1; ++j) {

        for(int i = 0; i < rows; ++i) {
            std += pow(dataSet[i][j] - averages.at(counter), 2);
        }

       deviations.push_back(sqrt(std/(rows - 1)));
       std = 0;
       ++counter;
    }


    counter = 0;

    for(int j = 1; j <= columns-1; ++j) {

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

    for(int i = 0; i < rows; ++i) {

        v.push_back(dataSet[i][0]);
        
        for(int j = 0; j < featureSubset.size(); ++j) {

            v.push_back(dataSet[i][featureSubset.at(j)]);
        }

        NN->train(v);

        v.clear();
    }
}

double classifierAccuracy() {

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