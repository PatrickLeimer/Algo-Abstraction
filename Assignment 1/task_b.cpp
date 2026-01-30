//Task B: Verifier 
#include <iostream> 
#include <vector>
#include <fstream>
using namespace std;

void verify(int n, vector<vector<int>> hospital_pref, vector<vector<int>> student_pref, vector<pair<int, int>> matches) {
    /*
    Approach: 
    Pairs in vectors, go through each pair checking for validity by using lists of booleans to mark matched hospitals and students.
    Then check for stability by checking each unmatched hospital-student pair to see if they prefer each other over their current matches.
    */

    // Validity Check
    vector<bool> seenHospital(n, false); 
    vector<bool> seenStudent(n, false); 

    vector<int> matchH(n, -1); // hospital -> student
    vector<int> matchS(n, -1); // student -> hospital

    // Check each is matched only once 
    for (int i = 0; i < n; i++) {
        int hospital = matches[i].first;
        int student = matches[i].second;

        if (hospital < 0 || hospital >= n || student < 0 || student >= n) {
            cout << "INVALID: Out of range pair (" << hospital << ", " << student << ")." << endl;
            return;
        }

        if ( seenHospital[hospital] == false ) {
            seenHospital[hospital] = true;
        } else {
            cout << "INVALID: Hospital " << hospital << " is matched more than once." << endl;
            return;
        }

        if ( seenStudent[student] == false ) {
            seenStudent[student] = true;
        } else {
            cout << "INVALID: Student " << student << " is matched more than once." << endl;
            return;
        }

        matchH[hospital] = student;
        matchS[student] = hospital;

        
    }
    
    // Check for completness, every single hospital and student is matched
    for (int i = 0; i < n; i++) {
        if ( seenHospital[i] == false || seenStudent[i] == false ) {
            cout << "INVALID: Hospital " << i << " is unmatched because hospital or student was not matched." << endl;
            return;
        }
    }


    // Stability Check
    
    for (int h = 1; h < n; h++) {
        for (int s = 1; s < n; s++) {
            // If h and s are not matched, to avoid checking the blocked pairs with existing pairs
            if ( matchH[h] != s ) {
                int currentMatchS = matchH[h];
                int currentMatchH = matchS[s];
                cout << "Checking unmatched pair (" << h + 1 << ", " << s + 1 << ") with current matches (" << h + 1 << ", " << currentMatchS + 1 << ") and (" << currentMatchH + 1 << ", " << s + 1 << ")." << endl;
                // h and s not matchted what do you mean? 
                
                // Check if h prefers s over current match
                bool hPrefersS = false;
                for (int pref : hospital_pref[h]) {
                    if (pref == s) {
                        hPrefersS = true;
                        break;
                    }
                    if (pref == currentMatchS) {
                        break;
                    }
                }

                // Check if s prefers h over current match
                bool sPrefersH = false;
                for (int pref : student_pref[s]) {
                    if (pref == h) {
                        sPrefersH = true;
                        break;
                    }
                    if (pref == currentMatchH) {
                        break;
                    }
                }

                // If both prefer each other over their current matches, it's unstable
                cout << "Checking pair (" << h + 1 << ", " << s + 1 << "): hPrefersS=" << hPrefersS + 1 << ", sPrefersH=" << sPrefersH + 1 << endl;
                if (hPrefersS && sPrefersH) {
                    return;
                }
            }
        }
    }


    cout << " \nVALID STABLE" << endl;

}


#ifdef TASK_B_STANDALONE
int main(int argc, char** argv) {
    string infilePath = "exampleIN.txt";
    string outfilePath = "exampleOUT.txt";

    if (argc >= 2) infilePath = argv[1];
    if (argc >= 3) outfilePath = argv[2];

    ifstream infile(infilePath);
    if (!infile.is_open()) {
        cout << "INVALID: could not read input file: " << infilePath << endl;
        return 0;
    }

    int n;
    if (!(infile >> n) || n <= 0) {
        cout << "INVALID: could not read n from input file: " << infilePath << endl;
        return 0;
    }

    vector<vector<int>> hospital_pref(n, vector<int>(n));
    vector<vector<int>> student_pref(n, vector<int>(n));
    vector<pair<int, int>> matches(n);

    // Read hospital preferences (convert to 0-based)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            infile >> hospital_pref[i][j];
            hospital_pref[i][j]--;
        }
    }
    

    // Read student preferences (convert to 0-based)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            infile >> student_pref[i][j];
            student_pref[i][j]--;
        }
    }

    infile.close();

    ifstream outfile(outfilePath);
    if (!outfile.is_open()) {
        cout << "INVALID: could not read matching file: " << outfilePath << endl;
        return 0;
    }

    // Read matches (convert to 0-based)
    for (int i = 0; i < n; i++) {
        int h, s;
        if (!(outfile >> h >> s)) {
            cout << "INVALID: could not read matching file: " << outfilePath << endl;
            return 0;
        }
        matches[i] = {h - 1, s - 1};
    }

    outfile.close();

    verify(n, hospital_pref, student_pref, matches);

    return 0;
}
#endif

