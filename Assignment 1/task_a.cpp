//Task A: Matching Engine
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

vector<vector<int>> gsMatching(int n, vector<vector<int>> hospital_pref, vector<vector<int>> student_pref) {
    /*
    I changed my approach to use vectors so I can iterate over their lists a bit better than
    */
    vector<int> student_pairs(n + 1, 0);   // student, hospital
    vector<int> hospital_pairs(n + 1, 0);  // hospital, student
    //both are initialized to free (0 on all indeces)
    vector<int> next_idx(n + 1, 0); //used later to determine what student(hospital[idx]) a hospital(idx) will look at next based on inputted preference list

    vector<vector<int>> rank(n + 1, vector<int>(n + 1, 0)); //Precomputing ranks so that we have an easier time iterating through students when a student is already taken
    for (int s = 1; s <= n; s++) {
        for (int pos = 0; pos < n; pos++) {
            int h = student_pref[s - 1][pos];
            rank[s][h] = pos;
        }
    }

    int matched_count = 0; // more space efficient than the set I had before

    for (int h = 1; h <= n && matched_count < n; h++) {
        if (hospital_pairs[h] != 0) continue;
        if (next_idx[h] >= n) continue;

        int a = hospital_pref[h - 1][ next_idx[h] ]; // a index of next favorite student h has not proposed to in 
        next_idx[h]++;

        if (student_pairs[a] == 0) { //if a is free
            student_pairs[a] = h;
            hospital_pairs[h] = a;
            matched_count++;
        }
        
        else { // if student is already matched, compare preferences
            int h_prev = student_pairs[a];
            if (rank[a][h] < rank[a][h_prev]) {
                
                hospital_pairs[h_prev] = 0; // a switches to h, h_prev becomes free
                student_pairs[a] = h;
                hospital_pairs[h] = a;
                // matched_count unchanged
            }
            // else do nothing
        }
    }

    // result packaging
    vector<vector<int>> result;
    for (int h = 1; h <= n; h++) {
        result.push_back({h, hospital_pairs[h]});
    }
    return result;
}