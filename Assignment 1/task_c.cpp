//Task c: Matching Engine
//Julio Leonardi
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include "cli.h"

using namespace std;

void testMatching(int base, int exponent){
    /*
    Generate tests using random numbers with an input size determined by params base^exponent (i) 
    */
    for (int i = 1; i < exponent + 1; i++) { //iterate through exponents
        int n = pow(base, i);
        vector<vector<int>> hospital_pref; 
        vector<vector<int>> student_pref;

        cout<< "n = "<< n << endl;

        int randNum = 1;

        for (int j = 0; j < n; j++) { //fills hospital and student pref with randomly generated nxn grids. 

            vector<int> hospital_List;
            vector<int> student_List;

            unordered_set <int> taken_Student;
            unordered_set <int> taken_Hospital;

            for (int k = 0; k < n; k++) {

                while (taken_Student.count(randNum)){
                    randNum = rand() % n + 1;
                }
                taken_Student.insert(randNum);
                hospital_List.push_back(randNum);

                randNum = rand() % n + 1;

                while (taken_Hospital.count(randNum)){
                    randNum = rand() % n + 1;
                }
                taken_Hospital.insert(randNum);
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

void testVerifying(int base, int exponent){//most stuff taken from testMatching

    for (int i = 1; i < exponent + 1; i++) { //iterate through exponents
        int n = pow(base, i);
        vector<vector<int>> hospital_pref; 
        vector<vector<int>> student_pref;

        cout<< "n = "<< n << endl;

        int randNum = 1;

        for (int j = 0; j < n; j++) { //fills hospital and student pref with randomly generated nxn grids. 

            vector<int> hospital_List;
            vector<int> student_List;

            unordered_set <int> taken_Student;
            unordered_set <int> taken_Hospital;

            for (int k = 0; k < n; k++) {

                while (taken_Student.count(randNum)){
                    randNum = rand() % n + 1;
                }
                taken_Student.insert(randNum);
                hospital_List.push_back(randNum);

                randNum = rand() % n + 1;

                while (taken_Hospital.count(randNum)){
                    randNum = rand() % n + 1;
                }
                taken_Hospital.insert(randNum);
                student_List.push_back(randNum);
            }

            hospital_pref.push_back(hospital_List);
            student_pref.push_back(student_List);
        }

        unordered_set <int> pair_student;
        unordered_set <int> pair_hospital;
        vector<pair<int, int>> matches;
        randNum = rand() % n + 1;

        for (int l = 0; l < n; l++){
            pair<int,int> match;
            while (pair_student.count(randNum)){
                    randNum = rand() % n + 1;
                }
                pair_student.insert(randNum);
                match.second = randNum;

                randNum = rand() % n + 1;

                while (pair_hospital.count(randNum)){
                    randNum = rand() % n + 1;
                }
                pair_hospital.insert(randNum);
                match.first = randNum;
                matches.push_back(match);
        }

        auto beg = chrono::high_resolution_clock::now();
        verify(n, hospital_pref, student_pref, matches);

        auto end = chrono::high_resolution_clock::now();

        auto duration = chrono::duration_cast<chrono::microseconds>(end - beg);
        cout << duration.count() << " microseconds" << endl;
    }

    return;
}

#ifdef TASK_C_STANDALONE
int main() {
    testMatching(2, 4);
    testVerifying(2, 4);
    return 0;
}
#endif