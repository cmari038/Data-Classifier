#include "Validator.h"
#include <iostream>
#include "Feature.h"
#include "Classifier.h"
#include <vector>
using namespace std;

int main() {

    vector<int> inputs; // input will be switched with feature class

    inputs.push_back(3);
    inputs.push_back(5);
    inputs.push_back(7);
    
    Validator* validity = new Validator(inputs);

    validity->DataInput("small-test-dataset.txt");

    cout << validity->classifierAccuracy() << endl;

    vector<int> inputs2;

    inputs2.push_back(1);
    inputs2.push_back(15);
    inputs2.push_back(27);


    Validator* v2 = new Validator(inputs2);

    v2->DataInput("Large-test-dataset.txt");
    cout << "Accuracy: " << v2->classifierAccuracy() << endl; 



    return 0;
}