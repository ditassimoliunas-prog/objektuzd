#include "../header_files/output.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <chrono>

using std::cin;
using std::cout;
using std::string;
using std::vector;
using std::left;
using std::right;
using std::setw;
using std::endl;
using std::setprecision;
using std::sort;
using std::fixed;
using std::numeric_limits;
using std::streamsize;
using std::chrono::high_resolution_clock;
using std::chrono::duration;

void outputas(vector<Studentas>& grupe) {
    if (grupe.empty()) {
        cout << "Nera studentu duomenu!" << endl;
        return;
    }

    // Klausiame kaip rusiuoti
    cout << "---------------------------------------------------" << endl;
    cout << "Pasirinkite rusiavimo buda:" << endl;
    cout << "1. Pagal varda (A-Z)" << endl;
    cout << "2. Pagal pavarde (A-Z)" << endl;
    cout << "3. Pagal galutini bala (vidurki) - didejimo tvarka" << endl;
    cout << "4. Pagal galutini bala (mediana) - didejimo tvarka" << endl;

    int pasirinkimas;
    while (!(cin >> pasirinkimas) || pasirinkimas < 1 || pasirinkimas > 4) {
        cout << "Klaida! Iveskite skaiciu nuo 1 iki 4: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Pasirinktas rusiavimas: " << pasirinkimas << endl;

    // Pradedam rusiavimo laiko matavima
    auto pradzia = high_resolution_clock::now();

    // Rusiuojame pagal pasirinkima
    switch (pasirinkimas) {
    case 1:
        sort(grupe.begin(), grupe.end(), [](const Studentas& a, const Studentas& b) {
            return a.vardas < b.vardas;
            });
        break;
    case 2:
        sort(grupe.begin(), grupe.end(), [](const Studentas& a, const Studentas& b) {
            return a.pavarde < b.pavarde;
            });
        break;
    case 3:
        sort(grupe.begin(), grupe.end(), [](const Studentas& a, const Studentas& b) {
            return a.rez < b.rez;
            });
        break;
    case 4:
        sort(grupe.begin(), grupe.end(), [](const Studentas& a, const Studentas& b) {
            return a.med < b.med;
            });
        break;
    default:
        cout << "Klaida! Neteisingas pasirinkimas. Rodoma be rusiavimo." << endl;
        break;
    }

    // Antrastes eilute
    cout << "---------------------------------------------------" << endl;
    cout << left << setw(20) << "Vardas" << setw(20) << "Pavarde"
        << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)" << endl;
    cout << string(80, '-') << endl;

    // Studentu duomenys
    for (const auto& A : grupe) {
        cout << left << setw(20) << A.vardas << setw(20) << A.pavarde
            << setw(20) << fixed << setprecision(2) << A.rez
            << setw(20) << fixed << setprecision(2) << A.med << endl;
    }

    // Baigiamas rusiavimo laiko matavimas
    auto pabaiga = high_resolution_clock::now();
    duration<double> trukme = pabaiga - pradzia;
    cout << "---------------------------------------------------" << endl;
    cout << "Ivykdymo laikas: " << fixed << setprecision(7) << trukme.count() << " s" << endl;
}