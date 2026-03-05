#include "../header_files/input.h"
#include "../header_files/mat_funkcijos.h"
#include <iostream>
#include <limits>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::numeric_limits;
using std::streamsize;

void inputas(vector<Studentas>& grupe) {
    int studentuKiekis;
    cout << "Kiek studentu norite ivesti? ";
    while (!(cin >> studentuKiekis) || studentuKiekis < 1) {
        cout << "Klaida! Iveskite teigiama skaiciu: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "---------------------------------------------------" << endl;

    for (int ii = 0; ii < studentuKiekis; ii++) {
        Studentas A;

        bool vardasGeras = false;
        while (!vardasGeras) {
            cout << "Iveskite varda ir pavarde: ";
            cin >> A.vardas >> A.pavarde;

            if (!arTikRaides(A.vardas) || !arTikRaides(A.pavarde)) {
                cout << "Klaida! Vardas ir pavarde turi buti sudaryti tik is raidziu!" << endl;
                cin.clear();
            }
            else {
                vardasGeras = true;
            }
        }

        cout << "---------------------------------------------------" << endl;
        cout << "Iveskite semestro ivertinimus. Kiek ju bus? " << endl;
        int n;
        while (!(cin >> n) || n < 0) {
            cout << "Klaida! Iveskite teigiama skaiciu: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << "---------------------------------------------------" << endl;
        for (int i = 0; i < n; i++) {
            int temp;
            bool pazymisTeisingas = false;
            while (!pazymisTeisingas) {
                cout << "Iveskite " << i + 1 << " pazymio ivertinima is " << n << " (0-10): ";
                if (!(cin >> temp)) {
                    cout << "Klaida! Iveskite skaiciu!" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                else if (temp < 0 || temp > 10) {
                    cout << "Klaida! Pazymys turi buti nuo 0 iki 10!" << endl;
                }
                else {
                    pazymisTeisingas = true;
                }
            }
            A.paz.push_back(temp);
        }

        bool egzaminasTeisingas = false;
        while (!egzaminasTeisingas) {
            cout << "Iveskite egzamina (0-10): ";
            if (!(cin >> A.egz)) {
                cout << "Klaida! Iveskite skaiciu!" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else if (A.egz < 0 || A.egz > 10) {
                cout << "Klaida! Egzaminas turi buti nuo 0 iki 10!" << endl;
            }
            else {
                egzaminasTeisingas = true;
            }
        }
        cout << "---------------------------------------------------" << endl;

        // Vidurkio skaiciavimas
        double vid = vidurkis(A.paz);
        A.rez = galutinisBalas(vid, A.egz);

        // Medianos skaiciavimas
        double med = mediana(A.paz);
        A.med = galutinisBalas(med, A.egz);

        grupe.push_back(A);
        A.paz.clear();

    }// galima priskirti grupej, kai turime A.rez; pushbackinam studento varda
}

