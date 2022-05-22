#include "Validator.h"
#include <iostream>
#include "Feature.h"
#include "Classifier.h"

int main() {
    
    Validator* validity = new Validator();

    validity->DataInput("small-test-dataset.txt");

    //validity->print();

    cout << validity->classifierAccuracy() << endl;



    return 0;
}