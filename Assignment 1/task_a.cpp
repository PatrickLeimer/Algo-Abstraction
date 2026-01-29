//Task A: Matching Engine
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

vector<vector<int>> gsMatching(int n, vector<vector<int>> hospital_pref, vector<vector<int>> student_pref){
    /*
    Approach: three hasmaps, one stores visited pairs and the other two do exisitng pairs
    We iterate through hospital_pref -> with i in the outer while loop and and then hospital_pref[i] -> with j in the inner loop,
    we do the Gale-Shapely comparisons. 
    */

    unordered_map <int, int> visited; //student, hospital
    unordered_map <int, int> student_pairs; //student, hospital
    unordered_map <int, int> hospital_pairs; //hospital, student

    int i = 0; //current_hospital

    while (hospital_pairs.size() < n){
        if (hospital_pairs.count(i)){
            
        }
   }

}