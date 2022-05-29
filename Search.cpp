#include "Feature.h"
#include <iostream>
#include <time.h>
#include <string>
#include "Validator.h"
#include <vector>
//using namespace std;

bool AccuracyComparison(Feature* feature1, Feature* feature2) { // comparator used to help sort vector of all feature subsets
    return feature1->getAccuracy() < feature2->getAccuracy();
}

// Large-test-dataset.txt       Forward Selection ({27,1} = 95.4%), Backward Elimination ({27} = 84.7%)
// small-test-dataset.txt      Forward Selection ({5,3} = 92%), Backward Elimination ({4,5,7,8,9,10} = 80%)
// CS170_Spring_2022_Large_data__140.txt   Forward Selection ({17,10} = 97.2%), Backward Elimination( {17} = 86.2%)
// CS170_Spring_2022_Small_data__140.txt    Forward Selection ((9,7,1) = 93%), Backward Elimination ({7,9}) = 93%

int main() {
   Feature* F; // used to store feature obect that contains subset with highest accuracy
   Feature* holder;
   Validator* valid = new Validator();
   vector<Feature*> features; // stores all feature objects with highest accuracy subsets.
   int numFeatures; 
   int choice;
   double Accuracy = 0; 
   double HighestAccuracy = 0;
   string text;

   std::cout << "Welcome to Christian Maristela's Feature Selection Algorithm." << endl << endl;

   std::cout << "Type in the name of the text file: ";

   cin >> text;

   std::cout << endl;

   std::cout << "Type the number of the algorithm you want to run." << endl << "Forward Selection" << endl << "Backward Selection" << endl << "Christian's Special Algorithm" << endl;

   cin >> choice;

   valid->DataInput(text);
   numFeatures = valid->numFeatures();

   std::cout << "This dataset has " << numFeatures << " features (not including the class attribute) with " << valid->numInstances() << " instances." << endl << endl;

   std::cout << "Please wait while I normalize the data ... Done!" << endl << endl;

   valid->normalize(); // normalize data


   // forward selection  (based off code given in lecture) 
   if(choice == 1) {

       F = new Feature(); // initial state with features
       std::cout << "Running nearest neighbor with no features (default rate), using leaving-one-out evaluation, I get an accuracy of " <<  valid -> defaultRate() << "%" << endl << endl << "Beginning Search" << endl << endl;

       for(unsigned i = 1; i <= numFeatures; ++i) {
          Feature* feature;
          double best_so_far_accuracy = 0; 

           for(unsigned j = 1; j <= numFeatures; ++j) {
            
               if(F->empty(j)) {    // checks to see if feature is not in set 
                   feature = F->duplicate();    // assigns a duplicate of F to feature
                   feature->Insert(j);  // adds feature to subset
                   feature->getSubset(valid); // adds subset to validator
                   feature->setAccuracy(valid->classifierAccuracy());     // calculates accuracy
                   std::cout << "Using feature(s) ";
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
        std::cout << endl << "Feature Set ";
        features.back()->print(2);
        if(F->getAccuracy() < HighestAccuracy && HighestAccuracy != 0) {    // checks to see if the highest recorded accuracy of level is lower
            std::cout << endl << "(Warning, accuracy has decreased! Continuing Search in case of local maxima)";
        }

        HighestAccuracy = F->getAccuracy();

        std::cout << endl << endl;
       }
   }

   
   //backward elimination (similar to forward elimination with some differences)
   else if(choice == 2) {

       F = new Feature(numFeatures);    // adds all features to F
       F->getSubset(valid);
       std::cout << "Running nearest neighbor with all features and using leaving-one-out evaluation, I get an accuracy of " << valid->classifierAccuracy() << "%" << endl << endl << "Beginning Search" << endl << endl;
       valid->EmptyVector();

        for(unsigned i = 1; i <= numFeatures; ++i) {
          Feature* feature;
          double best_so_far_accuracy = 0; 

           for(unsigned j = 1; j <= numFeatures; ++j) {
               if(!F->empty(j)) {           // checks to see if val is in set of features
                   feature = F->duplicate();  
                   feature->Remove(j);      // removes a feature from set
                   feature->getSubset(valid);
                   feature->setAccuracy(valid->classifierAccuracy());
                   std::cout << "Using feature(s) ";
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
        std::cout << endl << "Feature Set ";
        features.back()->print(2);
        if(F->getAccuracy() < HighestAccuracy && HighestAccuracy != 0) {
            std::cout << endl << "(Warning, accuracy has decreased! Continuing search in case of local maxima)";
        }

        HighestAccuracy = F->getAccuracy();
        std::cout << endl << endl;

       }
   }

   
   else {
       std::cout << "To be added later" << endl;
   }


   sort(features.begin(), features.end(), AccuracyComparison);  // sorts set of all subsets based on accuracy
   std::cout << endl << "Finished Search!! The best feature subset is "; 
   features.back()->print(0);
   std::cout << ", which has an accuracy of " << features.back()->getAccuracy() << "%" << endl;  // returns last element in subset since it will have highest accuracy

   return 0;

}