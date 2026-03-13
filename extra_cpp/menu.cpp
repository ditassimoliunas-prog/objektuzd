#include <vector>
#include <iostream>
#include <string>
#include <stdexcept>

#include "../header_files/menu.h"
#include "../header_files/studentas.h"
#include "../header_files/input.h"
#include "../header_files/output.h"
#include "../header_files/duomenu_valdymas.h"
#include "../header_files/testavimas.h"

using std::cout;
using std::cin;
using std::string;
using std::vector;
using std::endl;
using std::invalid_argument;
using std::exception;

void menu() {
    vector<Studentas>grupe;
    int pas; // Pasirinkimas
    bool testi = true;

    while (testi) {
        cout << "---------------------------------------------------" << endl;
        cout << "Studentu Rezultatu skaiciavimo aplikacija" << endl;
        cout << "---------------------------------------------------" << endl;
        cout << "1. Ivesti duomenis ranka " << endl;
        cout << "2. Generuoti tik pazymius " << endl;
        cout << "3. Generuoti studentu vardus, pavardes ir pazymius " << endl;
        cout << "4. Nuskaityti duomenis is failo " << endl;
        cout << "5. Sukurti testavimo failus (1000 - 10000000 irasu)" << endl;
        cout << "6. Atlikti spartos analize (nuskaitymas, rusiavimas, dalijimas, isvedimas)" << endl;
        cout << "7. Baigti darba " << endl;

        try {
            if (!(cin >> pas)) {
                throw invalid_argument("Neteisingas ivedimas! Iveskite skaiciu.");
            }
        }
        catch (const invalid_argument& e) {
            cout << "Klaida: " << e.what() << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        // Pasirinkimo isvestis
        switch (pas) {
        case 1:
            try {
                cout << "1. Ivesti duomenis ranka " << endl;
                inputas(grupe);
                outputas(grupe);
                grupe.clear();
            }
            catch (const exception& e) {
                cout << "Klaida vykdant 1 funkcija: " << e.what() << endl;
                grupe.clear();
            }
            break;
        case 2:
            try {
                cout << "2. Generuoti tik pazymius " << endl;
                generuotiPaz(grupe);
                outputas(grupe);
                grupe.clear();
            }
            catch (const exception& e) {
                cout << "Klaida vykdant 2 funkcija: " << e.what() << endl;
                grupe.clear();
            }
            break;
        case 3:
            try {
                cout << "3. Generuoti studentu vardus, pavardes ir pazymius " << endl;
                generuotiVardIrPav(grupe);
                outputas(grupe);
                grupe.clear();
            }
            catch (const exception& e) {
                cout << "Klaida vykdant 3 funkcija: " << e.what() << endl;
                grupe.clear();
            }
            break;
        case 4:
            try {
                cout << "4. Nuskaityti duomenis is failo " << endl;
                skaitytiIsFailo(grupe);
                grupe.clear();
            }
            catch (const exception& e) {
                cout << "Klaida vykdant 4 funkcija: " << e.what() << endl;
                grupe.clear();
            }
            break;
        case 5:
            try {
                cout << "5. Testavimo failu kurimas " << endl;
                sukurtiTestavimoFailus();
            }
            catch (const exception& e) {
                cout << "Klaida vykdant generavima: " << e.what() << endl;
            }
            break;
        case 6:
            try {
                cout << "6. Spartos analizes vykdymas " << endl;
                atliktiSpartosAnalize();
            }
            catch (const exception& e) {
                cout << "Klaida vykdant spartos analize: " << e.what() << endl;
            }
            break;
        case 7:
            cout << "Programa uzdaroma " << endl;
            testi = false;
            break;

        // Isvestis ivedus netinkama pasirinkima
        default:
            cout << "Klaida! Pasirinkite skaiciu nuo 1 iki 7 " << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            break;
        }
    }
}