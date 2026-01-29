//Task B: Verifier 
#include <iostream> 
#include <vector>
using namespace std;

void verify(int n, vector<vector<int>> hospital_pref, vector<vector<int>> student_pref, vector<pair<int, int>> matches) {
    /*
    Approach: 
    Pairs in vectors, go through each pair checking for validity by using lists of booleans to mark matched hospitals and students.
    Then check for stability by checking each unmatched hospital-student pair to see if they prefer each other over their current matches.
    */

    // Validity Check
    vector<bool> seenHosptial(n, false); 
    vector<bool> seenStudent(n, false); 

    // Check each is matched only once 
    for (int i = 0; i < n; i++) {
        int temp = matches[i].first;
        if ( seenHosptial[temp] == false ) {
            seenHosptial[temp] = true;
        } else {
            cout << "INVALID: Hospital " << temp << " is matched more than once." << endl;
            return;
        }

        temp = matches[i].second;
        if ( seenStudent[temp] == false ) {
            seenStudent[temp] = true;
        } else {
            cout << "INVALID: Student " << temp << " is matched more than once." << endl;
            return;
        }

        
    }
    
    // Check for completness, every single hospital and student is matched
    for (int i = 0; i < n; i++) {
        if ( seenHosptial[i] == false || seenStudent[i] == false ) {
            cout << "INVALID: Hospital " << i << " is unmatched because hospital or student was not matched." << endl;
            return;
        }
    }

    cout << "VALID STABLE" << endl;
    // Stability Check
    
    

}

/*
Output Format for Verifier Algorithm
Your verifier should print either:

VALID STABLE or
a clear failure message, e.g. INVALID (with reason) or UNSTABLE (with an example blocking pair).  If it is both UNSTABLE and INVALID then you can output both or one, your choice.
*/