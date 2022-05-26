#include "Feature.h"
#include <iostream>
#include <time.h>
#include <string>
#include "Validator.h"
using namespace std;

bool AccuracyComparison(Feature* feature1, Feature* feature2) { // comparator used to help sort vector of feature subsets
    return feature1->getAccuracy() < feature2->getAccuracy();
}

// Large-test-dataset.txt       Forward Elimination ({27,1} = 95.4%), Backward Elimination ({27} = 84.7%)
// small-test-dataset.txt      Forward Elimination ({5,3} = 92%), Backward Elimination ({4,5,7,8,9,10} = 80%)
// CS170_Spring_2022_Large_data__140.txt   Forward Elimination ({1,7,10} = 97.2%), 
// CS170_Spring_2022_Small_data__140.txt    Forward Elimination ((9,7,1) = 93%), Backward Elimination ({7,9}) = 93%

int main() {
   Feature* F; // used to store feature subset with highest accuracy
   Feature* holder;
   Validator* valid = new Validator();
   vector<Feature*> features; 
   int numFeatures; 
   int choice;
   double Accuracy = 0; 
   double HighestAccuracy = 0;
   string text;

   cout << "Welcome to Christian Maristela's Feature Selection Algorithm." << endl << endl;

   cout << "Type in the name of the text file: ";

   cin >> text;

   cout << endl;

   cout << "Type the number of the algorithm you want to run." << endl << "Forward Selection" << endl << "Backward Selection" << endl << "Christian's Special Algorithm" << endl;

   cin >> choice;

   valid->DataInput(text);
   numFeatures = valid->numFeatures();


   // forward selection  (based off code given in lecture)
   if(choice == 1) {

       F = new Feature(); // initial state with features
    //   F->setAccuracy(AccuracyCalc(F));
     //  cout << "Using no features and random evaluation, I get an accuracy of " << F->getAccuracy() << "%" << endl << endl << "Beginning Search" << endl << endl;

       for(unsigned i = 1; i <= numFeatures; ++i) {
          Feature* feature;
          double best_so_far_accuracy = 0; 

           for(unsigned j = 1; j <= numFeatures; ++j) {
            
               if(F->empty(j)) {    // checks to see if feature is not in set 
                   feature = F->duplicate();    // assigns a duplicate of F to feature
                   feature->Insert(j);  // adds feature to subset
                   feature->getSubset(valid); // adds subset to validator
                   feature->setAccuracy(valid->classifierAccuracy());     // calculates accuracy
                   cout << "Using feature(s) ";
                   feature->print(1);
                   Accuracy = feature->getAccuracy();

                   if(Accuracy > best_so_far_accuracy) {        // check to see if accuracy is higher
                       best_so_far_accuracy = Accuracy;
                       holder = feature;        // if accuracy is higher than previosuly recorded, assing it to holder
                   }

                   valid->EmptyVector(); // empties subset vector for next input;
               }

           }

        F = holder; // set F equal to feature with highest accuracy
        features.push_back(F);      //add F to vector of all subsets 
        cout << endl << "Feature Set";
        features.back()->print(2);
        if(F->getAccuracy() < HighestAccuracy && HighestAccuracy != 0) {    // checks to see if the highest recorded accuracy of level is lower
            cout << endl << "(Warning, accuracy has decreased!)";
        }

        HighestAccuracy = F->getAccuracy();

        cout << endl << endl;
       }
   }

   
   //backward elimination (similar to forward elimination with some differences)
   else if(choice == 2) {

       F = new Feature(numFeatures);    // adds all features to F
      // F->setAccuracy(AccuracyCalc(F));
     //  cout << "Using all features and random evaluation, I get an accuracy of " << F->getAccuracy() << "%" << endl << endl << "Beginning Search" << endl << endl;

        for(unsigned i = 1; i <= numFeatures; ++i) {
          Feature* feature;
          double best_so_far_accuracy = 0; 

           for(unsigned j = 1; j <= numFeatures; ++j) {
               if(!F->empty(j)) {           // checks to see if val is in set of features
                   feature = F->duplicate();  
                   feature->Remove(j);      // removes a feature from set
                   feature->getSubset(valid);
                   feature->setAccuracy(valid->classifierAccuracy());
                   cout << "Using feature(s) ";
                   feature->print(1);
                   Accuracy = feature->getAccuracy();

                   if(Accuracy > best_so_far_accuracy) {
                       best_so_far_accuracy = Accuracy;
                       holder = feature;
                   }
               }

               valid->EmptyVector();

           }
        
        F = holder;
        features.push_back(F);
        cout << endl << "Feature Set";
        features.back()->print(2);
        if(F->getAccuracy() < HighestAccuracy && HighestAccuracy != 0) {
            cout << endl << "(Warning, accuracy has decreased!)";
        }

        HighestAccuracy = F->getAccuracy();
        cout << endl << endl;

       }
   }

   
   else {
       cout << "To be added later" << endl;
   }


   sort(features.begin(), features.end(), AccuracyComparison);  // sorts set of all subsets based on accuracy
   cout << endl << "Finished Search!! The best feature subset is "; 
   features.back()->print(0);
   cout << ", which has an accuracy of " << features.back()->getAccuracy() << "%" << endl;  // returns last element in subset since it will have highest accuracy

   return 0;

}