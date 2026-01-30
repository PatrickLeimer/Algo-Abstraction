//Task c: Matching Engine
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include <algorithm>
#include <chrono>

#include "abc.h"

using namespace std;

void testGen(int base, int exponent){
    /*
    Generate tests using random numbers with an input size determined by params base^exponent (i)
    */
    for (int i = 1; i < exponent + 1; i++) { //iterate through exponents
        int n = pow(base, i);
        vector<vector<int>> hospital_pref; 
        vector<vector<int>> student_pref;

        cout<< "n = "<< n << endl;

        int randNum = 1;

        vector<int> hospital_List;
        vector<int> student_List;

        for (int j = 0; j < n; j++) { //fills hospital and student pref with randomly generated nxn grids. 

            unordered_set <int> taken_Student;
            unordered_set <int> taken_Hospital;

            for (int k = 0; k < n; k++) {

                while (taken_Student.count(randNum)){
                    int randNum = rand() % n + 1;
                }
                hospital_List.push_back(randNum);

                while (taken_Hospital.count(randNum)){
                    int randNum = rand() % n + 1;
                }
                student_List.push_back(randNum);
            }

            hospital_pref.push_back(hospital_List);
            student_pref.push_back(student_List);
        }

        //https://www.geeksforgeeks.org/cpp/measure-execution-time-function-cpp/

        auto beg = chrono::high_resolution_clock::now();
        //now we run the gsmatch and print the time
        vector<vector<int>> result = gsMatching(n, hospital_pref, student_pref);

        auto end = chrono::high_resolution_clock::now();

        auto duration = chrono::duration_cast<chrono::microseconds>(end - beg);
        cout << duration.count() << " microseconds" << endl;
    }

    return;
}

int main() {
    testGen(2, 4);
    return 0;
}