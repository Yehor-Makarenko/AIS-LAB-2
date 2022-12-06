#ifndef AISLAB2_FUNCTIONS
#define AISLAB2_FUNCTIONS

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <random>

using namespace std::chrono;
using namespace std;

bool isCyclicRotation(string str1, string str2);
bool isCyclicRotationKMP(string str1, string str2);
vector<int> prefixFunction(string str);
string getRandomString(int length);
void doBenchmarks(int length, int accuracy);

bool isCyclicRotation(string str1, string str2) {
    if (str1.length() != str2.length()) return false;

    bool isCyclicRotation = true;
    int len = str1.length();

    if (len == 0) return true;
    if (len == 1) return str1 == str2;

    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            if (str1[(i + j) % len] != str2[j]) {
                isCyclicRotation = false;
                break;
            }
        }

        if (isCyclicRotation) return true;
        isCyclicRotation = true;
    }

    return false;
}

bool isCyclicRotationKMP(string str1, string str2) {
    if (str1.length() != str2.length()) return false;

    int len = str1.length();

    if (len == 0) return true;
    if (len == 1) return str1 == str2;

    vector<int> pi = prefixFunction(str2);
    int j = 0;

    for (int i = 0; i < len * 2; i++) {
        if (len - j > len * 2 - i) break;

        if (str1[i % len] == str2[j]) {
            if (j == len - 1) return true;

            j++;
        }
        else if (j != 0) {
            j = pi[j - 1];
            i--;
        }
    }

    return false;
}

vector<int> prefixFunction(string str) {
    vector<int> pi = { 0 };
    int j = 0;

    for (int i = 1; i < str.length(); i++) {
        if (str[i] == str[j]) {
            pi.push_back(j + 1);
            j++;
        }
        else if (j == 0) {
            pi.push_back(0);
        }
        else {
            j = pi[j - 1];
            i--;
        }
    }

    return pi;
}

string getRandomString(int length) {
    string result = "";

    for (int i = 0; i < length; i++) {
        int randomNum = rand() % 52;
        if (randomNum < 26) randomNum += 65;
        else randomNum += 71;
        result += (char)randomNum;
    }

    return result;
}

void doBenchmarks(int length, int repeats) {
    auto start = high_resolution_clock::now();
    auto creationStart = start;
    auto creationStop = start;
    string str1 = getRandomString(length);
    string str2 = getRandomString(length);

    for (int i = 0; i < repeats; ++i) {
        creationStart = high_resolution_clock::now();

        isCyclicRotationKMP(str1, str2);

        creationStop = high_resolution_clock::now();
        start -= (creationStart - creationStop);
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    long long int res = duration.count() / repeats;
    cout << "Average execution time: ";
    cout << res / 1000000 << " seconds, "
        << (res % 1000000) / 1000 << " milliseconds and "
        << res % 1000 << " microseconds" << endl;
    cout << endl;
}

#endif