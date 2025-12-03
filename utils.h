#pragma once
#include <string>
using namespace std;

inline string simpleHash(const string& input) {
    string hash = input;
    for (char& c : hash) c = (c + 7) ^ 21; // просте XOR-кодування
    return hash;
}

// оголошення функцій інших модулів
void editList();
void confirmOrder();

