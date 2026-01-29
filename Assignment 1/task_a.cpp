//Task A: Matching Engine
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

vector<vector<int>> gsMatching(int n, vector<vector<int>> hospital_pref, vector<vector<int>> student_pref){
    /*
    Approach: three hasmaps, one stores visited pairs and the other two do exisitng pairs
    We iterate through hospital_pref -> with i in the outer while loop and and then hospital_pref[i] -> with j in the inner loop,
    we do the Gale-Shapely comparisons. 
    */

    unordered_map <int, vector<int>> visited; //student, hospitals
    unordered_map <int, int> student_pairs; //student, hospital
    unordered_map <int, int> hospital_pairs; //hospital, student
    unordered_set <int> completeness; //added later to prevent having to delete an entry from a hasmap which is O(n)

    int i = 1; //current_hospital

    while (completeness.size() < n){
        if (hospital_pairs[i] == 0 || !hospital_pairs[i]){

            int j = 1; // student being looked at
            while (find(visited[j].begin(), visited[j].end(), i) != visited[j].end()){ //Find the j 
                j = (j + 1) % n;
            }

            if (student_pairs[j] == 0 || !student_pairs[j]){

                student_pairs[j] = i;
                hospital_pairs[i] = j;
                completeness.insert(i);

            } else { // compare students preference 

                int cur_pref = 0;
                int prev_pref = 0;
                
                for (int k = 0; k < n; k++){
                    if (student_pref[j-1][k] == student_pairs[j]){//look through student's hospital preference list for current student-hospital pair
                        int prev_pref = k; 
                    }
                }

                for (int k = 0; k < n; k++){
                    if (student_pref[j-1][k] == i){//look through student's hospital preference list for proposed student_hospital pair
                        int cur_pref = k; 
                    }
                }

                //We may have to make the preference retrieval better

                if (cur_pref > prev_pref){ // this conditional statement lets me take care of the 'skip' else statement
                    completeness.erase(student_pairs[j]);
                    hospital_pairs[student_pairs[j]] = 0;
                    student_pairs[j] = i;
                    hospital_pairs[i] = j;
                    completeness.insert(i);
                } 
            } 
            visited[j].push_back(i);

        }
        i = (i + 1) % n;
    }
    // result packaging
    
    vector<vector<int>> result;
    for (auto hospital: hospital_pairs){
        result.push_back({hospital.first, hospital.second});
    }

    return result;

}