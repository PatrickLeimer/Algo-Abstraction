#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "cli.h"

using namespace std;

static bool read_prefs(const string& infile, int &n,
                       vector<vector<int>> &hospital_pref,
                       vector<vector<int>> &student_pref) {
    ifstream fin(infile);
    if (!fin.is_open()) return false;

    if (!(fin >> n) || n <= 0) return false;

    hospital_pref.assign(n, vector<int>(n));
    student_pref.assign(n, vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fin >> hospital_pref[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fin >> student_pref[i][j];
        }
    }
    return true;
}

static bool read_matching(const string& outfile, int n, vector<pair<int,int>> &matches) {
    ifstream fout(outfile);
    if (!fout.is_open()) return false;

    matches.clear();
    matches.reserve(n);

    for (int k = 0; k < n; k++) {
        int h, s;
        if (!(fout >> h >> s)) return false;
        matches.push_back({h - 1, s - 1});
    }
    return true;
}

static void to_zero_based(vector<vector<int>> &prefs) {
    for (auto &row : prefs) {
        for (auto &v : row) {
            v -= 1;
        }
    }
}

static void write_matching(const string& outfile, const vector<vector<int>> &matches) {
    ofstream fout(outfile);
    for (const auto &pair : matches) {
        fout << pair[0] << " " << pair[1] << "\n";
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "Usage:\n"
             << "  cli a <input.in> <output.out>\n"
             << "  cli b <input.in> <matching.out>\n"
             << "  cli c <base> <exponent>\n";
        return 0;
    }

    string mode = argv[1];

    if (mode == "a") {
        if (argc < 4) {
            cout << "Usage: cli a <input.in> <output.out>\n";
            return 0;
        }
        string inPath = argv[2];
        string outPath = argv[3];

        int n;
        vector<vector<int>> hospital_pref, student_pref;
        if (!read_prefs(inPath, n, hospital_pref, student_pref)) {
            cout << "INVALID: could not read input file: " << inPath << endl;
            return 0;
        }

        vector<vector<int>> matches = gsMatching(n, hospital_pref, student_pref);
        write_matching(outPath, matches);
        cout << "Matching pairs:" << endl;
        for (const auto &pair : matches) {
            cout << pair[0] << " " << pair[1] << endl;
        }
        return 0;
    }

    if (mode == "b") {
        if (argc < 4) {
            cout << "Usage: cli b <input.in> <matching.out>\n";
            return 0;
        }
        string inPath = argv[2];
        string outPath = argv[3];

        int n;
        vector<vector<int>> hospital_pref, student_pref;
        vector<pair<int,int>> matches;

        if (!read_prefs(inPath, n, hospital_pref, student_pref)) {
            cout << "INVALID: could not read input file: " << inPath << endl;
            return 0;
        }
        if (!read_matching(outPath, n, matches)) {
            cout << "INVALID: could not read matching file: " << outPath << endl;
            return 0;
        }

        to_zero_based(hospital_pref);
        to_zero_based(student_pref);

        verify(n, hospital_pref, student_pref, matches);
        return 0;
    }

    if (mode == "c") {
        if (argc < 4) {
            cout << "Usage: cli c <base> <exponent>\n";
            return 0;
        }
        int base = stoi(argv[2]);
        int exponent = stoi(argv[3]);
        testMatching(base, exponent);
        testVerifying(base, exponent);
        return 0;
    }

    cout << "Unknown mode: " << mode << endl;
    return 0;
}
