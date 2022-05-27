#include "Validator.h"
#include <iostream>
#include "Feature.h"
#include <vector>
using namespace std;

int main() {

   Feature* inputs = new Feature(); // cpp file used for testing

    inputs->Insert(3);
    inputs->Insert(5);
    inputs->Insert(7);
    
    Validator* validity = new Validator();

    validity->DataInput("small-test-dataset.txt");
    validity->normalize();

    inputs->getSubset(validity);
    inputs->setAccuracy(validity->classifierAccuracy());

    cout << inputs->getAccuracy() << endl;

    Feature* inputs2 = new Feature();

    inputs2->Insert(1);
    inputs2->Insert(15);
    inputs2->Insert(27);


    Validator* v2 = new Validator();

    v2->DataInput("Large-test-dataset.txt");
    v2->normalize();
    inputs2->getSubset(v2);
    inputs2->setAccuracy(v2->classifierAccuracy());
    cout << inputs2->getAccuracy() << endl;    



    return 0; 
}