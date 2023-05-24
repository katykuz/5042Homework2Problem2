/*
 * Name: Ekaterina (Katy) Kuznetsova
 * Date: May 23, 2023
 * Assignment: Homework 2 Problem 2
 * C++ Version: C++17
 *
 * Program description:
 */

#include <iostream>
#include <sstream>
#include <vector>
#include <thread>

using namespace std;

void clientProgram(vector<int> *& unsortedArr);
void splitA();

void mergeSort(vector<int> * A);
void merge(vector<int> * B, vector<int> * C, vector<int> * A);
void printArray(vector<int> * array);
void finalMerge(vector<int> * B, vector<int> * C, vector<int> * A);
//void testProgram();

//create vectors for holding number data and input
vector<int> * unsortedArr = new vector<int>;
vector<int> * halfOne = new vector<int>;
vector<int> * halfTwo = new vector<int>;
vector<int> * sortedArr = new vector<int>;

int main() {

    clientProgram(*& unsortedArr);

    cout << "Unsorted array: ";
    printArray(*& unsortedArr);

    splitA();

    //recursively call mergesort
    thread th1(mergeSort, halfOne);
    thread th2(mergeSort, halfTwo);

    th1.join();
    th2.join();

    //do the merge
    thread th3(finalMerge, halfOne, halfTwo, sortedArr);
    //finalMerge(halfOne, halfTwo, sortedArr);

    th3.join();

    cout << "\nSorted array: ";
    printArray(sortedArr);

    delete halfOne;
    delete halfTwo;

}

void clientProgram(vector<int> *& unsortedArr) {

//string variable to hold all of user input
    string longInput;

    //string variable to hold a section of string as separated by space
    string inputSection;

    //prompt user to enter a series of numbers
    cout << "Please enter a series of integers separated by spaces:";

    //assign input to string variable
    getline(cin, longInput);

    //create istringstream object copying the contents of string
    istringstream ss(longInput);

    //break up a section of long input and check if it is a digit
    while(getline(ss, inputSection, ' ')){

        //if it is a digit, put it on the vector
        for (int i = 0; i < inputSection.length(); i++){
            if (!isdigit(inputSection[i])) {
                i = inputSection.length();
            }

            if (i == inputSection.length() - 1){
                int num = stoi(inputSection);
                unsortedArr->push_back(num);
            }
        }
    }

    cout << "Number of elements: " << unsortedArr->size() << endl;
    cout << "Size of half of array: " << unsortedArr->size()/2 << endl;

}

void printArray(vector<int> * array){

    for (int i = 0; i < array->size(); i++){
        cout << array->at(i) << " ";
    }
}

void splitA() {

    //as long as the array is bigger than 1
    if (unsortedArr->size() > 1) {
        //if the array size is even
        if (unsortedArr->size() % 2 == 0) {

            //split array A into B and C
            for (int i = 0; i < unsortedArr->size() / 2; i++) {

                halfOne->push_back(unsortedArr->at(i));
                halfTwo->push_back(unsortedArr->at((unsortedArr->size() / 2)
                + i));
            }


            //if the array size is odd
        } else {

            //split the first half of A into B (1 bigger)
            for (int i = 0; i < ((unsortedArr->size()/2)+1); i++) {

                halfOne->push_back(unsortedArr->at(i));
            }

            //split the second half of A into C (smaller half)
            for (int i = 0; i < (unsortedArr->size()/2); i++) {

                halfTwo->push_back(unsortedArr->at(((unsortedArr->size()/2)+1)
                        + i));
            }
        }
    }
}

void mergeSort(vector<int> * A) {

    //as long as the array is bigger than 1
    if (A->size() > 1) {

        vector<int> *B = new vector<int>;
        vector<int> *C = new vector<int>;


        //if the array size is even
        if (A->size() % 2 == 0) {


            //split array A into B and C
            for (int i = 0; i < A->size() / 2; i++) {

                B->push_back(A->at(i));
                C->push_back(A->at((A->size() / 2) + i));
            }

            //recursively call mergesort
            mergeSort(B);
            mergeSort(C);

            //do the merge
            merge(B, C, A);

            //if the array size is odd
        } else {

            //split the first half of A into B (1 bigger)
            for (int i = 0; i < (A->size() / 2 + 1); i++) {

                B->push_back(A->at(i));
            }

            //split the second half of A into C (smaller half)
            for (int i = 0; i < (A->size() / 2); i++) {

                C->push_back(A->at((A->size() / 2 + 1) + i));
            }

                //recursively call mergesort
                mergeSort(B);
                mergeSort(C);

                //do the merge
                merge(B, C, A);
            }
        delete B;
        delete C;
    }
}


void merge(vector<int> * B, vector<int> * C, vector<int> * A){

    //establish counting variables for each array
    int i = 0;
    int j = 0;
    int k = 0;

    //while the count of each array is smaller than the size of that array
    while (i < B->size() && j < C->size()) {

        //compare the corresponding indexes of the two 'half' arrays and
        // place into the bigger array A
        if (B->at(i) <= C->at(j)){
            A->at(k) = B->at(i);
            i = i+1;
        }
        else {
            A->at(k) = C->at(j);
            j = j+1;
        }
        k = k + 1;
    }
    //if first half of the array reaches the end before the other, add the
    // rest of the leftover array to the end of the larger array
    if (i == B->size()){

        for (int m = j; m < C->size(); m++){
            A->at(k) = C->at(m);
            k++;
        }
    } else {
        for (int m = i; m < B->size(); m++){
            A->at(k) = B->at(m);
            k++;
        }
    }
}

void finalMerge(vector<int> * B, vector<int> * C, vector<int> * A){

    //establish counting variables for each array
    int i = 0;
    int j = 0;
    int k = 0;

    //while the count of each array is smaller than the size of that array
    while (i < B->size() && j < C->size()) {

        //compare the corresponding indexes of the two 'half' arrays and
        // place into the bigger array A
        if (B->at(i) <= C->at(j)){
            A->push_back(B->at(i));
            i = i+1;
        }
        else {
            A->push_back(C->at(j));
            j = j+1;
        }
    }
    //if first half of the array reaches the end before the other, add the
    // rest of the leftover array to the end of the larger array
    if (i == B->size()){

        for (int m = j; m < C->size(); m++){
            A->push_back(C->at(m));
        }
    } else {
        for (int m = i; m < B->size(); m++){
            A->push_back(B->at(m));
        }
    }
}