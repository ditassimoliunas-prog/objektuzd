#include <iostream>
#include <limits>

#include "../header_files/input.h"
#include "../header_files/mat_funkcijos.h"

using std::cin;
using std::cout;
using std::vector;
using std::string;
using std::numeric_limits;
using std::streamsize;

void inputas(vector<Studentas>& grupe) {
    bool testiStudenta = true;

    while (testiStudenta) {
        Studentas A;

        bool vardasGeras = false;
        while (!vardasGeras) {
            cout << "Iveskite varda ir pavarde: ";
            cin >> A.vardas >> A.pavarde;

            if (!arTikRaides(A.vardas) || !arTikRaides(A.pavarde)) {
                cout << "Klaida! Vardas ir pavarde turi buti sudaryti tik is raidziu!\n";
                cin.clear();
            }
            else {
                vardasGeras = true;
            }
        }

        cout << "---------------------------------------------------\n";
        cout << "Iveskite semestro ivertinimus (0-10). Iveskite -1 kad baigtumete: \n";
        A.paz.reserve(15); // Rezervuojama vieta pazymiams (sumazina atminties reallokacijas)
        int temp;
        while (true) {
            cout << "Iveskite pazymi (arba -1 kad baigtumete): ";
            if (!(cin >> temp)) {
                cout << "Klaida! Iveskite skaiciu!\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else if (temp == -1) {
                break;
            }
            else if (temp < 0 || temp > 10) {
                cout << "Klaida! Pazymys turi buti nuo 0 iki 10!\n";
            }
            else {
                A.paz.push_back(temp);
            }
        }

        cout << "---------------------------------------------------\n";

        bool egzaminasTeisingas = false;
        while (!egzaminasTeisingas) {
            cout << "Iveskite egzamina (0-10): ";
            if (!(cin >> A.egz)) {
                cout << "Klaida! Iveskite skaiciu!\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else if (A.egz < 0 || A.egz > 10) {
                cout << "Klaida! Egzaminas turi buti nuo 0 iki 10!\n";
            }
            else {
                egzaminasTeisingas = true;
            }
        }
        cout << "---------------------------------------------------\n";

        // Vidurkio skaiciavimas
        if (!A.paz.empty()) {
            double vid = vidurkis(A.paz);
            A.rez = galutinisBalas(vid, A.egz);
            // Medianos skaiciavimas
            double med = mediana(A.paz);
            A.med = galutinisBalas(med, A.egz);
        }
        else {
            A.rez = A.egz * 0.6;
            A.med = A.egz * 0.6;
        }

        grupe.push_back(A);
        A.paz.clear();

        // Klausimas ar testi rankini generavima
        char atsakymas;
        bool atsakymasTeisingas = false;
        while (!atsakymasTeisingas) {
            cout << "Ar norite ivesti dar viena studenta? (T/N): ";
            cin >> atsakymas;
            if (atsakymas == 'T' || atsakymas == 't') {
                testiStudenta = true;
                atsakymasTeisingas = true;
                cout << "---------------------------------------------------\n";
            }
            else if (atsakymas == 'N' || atsakymas == 'n') {
                testiStudenta = false;
                atsakymasTeisingas = true;
            }
            else {
                cout << "Klaida! Iveskite T arba N!\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }
}

