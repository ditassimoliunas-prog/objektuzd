#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

struct Studentas {
    string vardas = "A";
    string pavarde = "BB";
    vector<int> paz;
    int egz = 0; // Default inicializacija
    double rez = 0.0; // Pradinis balų priskyrimas
    double med = 0.0;
};
