#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <chrono>

using namespace std;

vector<vector<int>> gsMatching(int n, vector<vector<int>> hospital_pref, vector<vector<int>> student_pref);
void verify(int n, vector<vector<int>> hospital_pref, vector<vector<int>> student_pref, vector<pair<int, int>> matches);
void testGen(int base, int exponent);
