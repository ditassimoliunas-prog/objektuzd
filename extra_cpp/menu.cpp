#include <vector>
#include <iostream>
#include <string>

#include "../header_files/menu.h"
#include "../header_files/studentas.h"
#include "../header_files/input.h"
#include "../header_files/output.h"
#include "../header_files/duomenu_valdymas.h"

using std::cout;
using std::cin;
using std::string;
using std::vector;
using std::endl;


void menu() {
    vector<Studentas>grupe;
    int pas; // pasirinkimas
    bool testi = true;

    while (testi) {
        cout << "---------------------------------------------------" << endl;
        cout << "Studentu Rezultatu skaiciavimo aplikacija" << endl;
        cout << "---------------------------------------------------" << endl;
        cout << "1. Ivesti duomenis ranka " << endl;
        cout << "2. Generuoti tik pazymius " << endl;
        cout << "3. Generuoti studentu vardus, pavardes ir pazymius " << endl;
        cout << "4. Nuskaityti duomenis is failo " << endl;
        cout << "5. Baigti darba " << endl;
        cin >> pas;

        // Pasirinkimo isvestys
        switch (pas) {
        case 1:
            cout << "1. Ivesti duomenis ranka " << endl;
            inputas(grupe);
            outputas(grupe);
            grupe.clear();
            break;
        case 2:
            cout << "2. Generuoti tik pazymius " << endl;
            generuotiPaz(grupe);
            outputas(grupe);
            grupe.clear();
            break;
        case 3:
            cout << "3. Generuoti studentu vardus, pavardes ir pazymius " << endl;
            generuotiVardIrPav(grupe);
            outputas(grupe);
            grupe.clear();
            break;
        case 4:
            cout << "4. Nuskaityti duomenis is failo " << endl;
            skaitytiIsFailo(grupe);
            grupe.clear();
            break;
        case 5:
            cout << "Programa uzdaroma " << endl;
            testi = false;
            break;

            // Isvestus ivedus netinkama pasirinkima
        default:
            cout << "Klaida! Pasirinkite skaiciu nuo 1 iki 5 " << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            break;
        }
    }
}