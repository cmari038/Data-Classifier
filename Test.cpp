#include "Validator.h"
#include <iostream>
#include "Feature.h"
#include "Classifier.h"

int main() {
    
    Validator* validity = new Validator();

    validity->DataInput("small-test-dataset.txt");

    cout << validity->classifierAccuracy() << endl;

    Validator* v2 = new Validator();

    v2->DataInput("Large-test-dataset.txt");
    cout << v2->classifierAccuracy() << endl;



    return 0;
}