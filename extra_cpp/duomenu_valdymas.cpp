#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <limits>
#include <random>
#include <ctime>
#include <fstream>

#include "../header_files/duomenu_valdymas.h"
#include "../header_files/mat_funkcijos.h"

using std::cin;
using std::cout;
using std::string;
using std::vector;
using std::numeric_limits;
using std::streamsize;
using std::ifstream;
using std::endl;




// Atsitiktiniiu skaiciu generavimas
void generuotiPaz(vector<Studentas>& grupe) {
    srand(time(0)); //Inicializuoja atsitiktine seed pagal laika

    int studentuKiekis;
    cout << "Kiek studentu norite sugeneruoti? ";
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
        cout << "Iveskite semestro pazymiu kieki: " << endl;
        int n;
        while (!(cin >> n) || n < 0) {
            cout << "Klaida! Iveskite teigiama skaiciu: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "---------------------------------------------------" << endl;

        // Automatiskai generuojami pazymiai
        cout << "Pazymiu ivertinmai: ";
        for (int i = 0; i < n; i++) {
            int temp = generuotiPazymi();
            A.paz.push_back(temp);
            cout << temp << " ";
        }

        cout << endl;

        // Automatiskai generuojamas egzaminas
        A.egz = generuotiEgzamina();
        cout << "Egzamino ivertinimas: " << A.egz << endl;
        cout << "---------------------------------------------------" << endl;

        // Vidurkio skaiciavimas
        double vid = vidurkis(A.paz);
        A.rez = galutinisBalas(vid, A.egz);

        // Medianos skaiciavimas
        double med = mediana(A.paz);
        A.med = galutinisBalas(med, A.egz);

        grupe.push_back(A);
        A.paz.clear();
    }
}

void generuotiVardIrPav(vector<Studentas>& grupe) {
    srand(time(0));

    // Nuskaitome failus
    vector<string> vyruVard, vyruPav, motVard, motPav;
    ifstream vvard("../vpv/vvard.txt");
    ifstream vpav("../vpv/vpav.txt");
    ifstream mvard("../vpv/mvard.txt");
    ifstream mpav("../vpv/mpav.txt");

    // Patikrinimas ar failai atsidare
    if (!vvard.is_open() || !vpav.is_open() || !mvard.is_open() || !mpav.is_open()) {
        cout << "Klaida! Nepavyko atidaryti vieno ar daugiau failu su vardais ir pavardemis " << endl;
        return;
    }

    // Nuskaitomi visi vardai ir pavardes
    string eilute;
    while (vvard >> eilute) vyruVard.push_back(eilute);
    while (vpav >> eilute) vyruPav.push_back(eilute);
    while (mvard >> eilute) motVard.push_back(eilute);
    while (mpav >> eilute) motPav.push_back(eilute);

    vvard.close();
    vpav.close();
    mvard.close();
    mpav.close();

    // Patikrinama ar failai ne tusti
    if (vyruVard.empty() || vyruPav.empty() || motVard.empty() || motPav.empty()) {
        cout << "Klaida! Vienas ar daugiau failu yra tusti! " << endl;
        return;
    }

    int studentuKiekis;
    cout << "Kiek studentu norite sugeneruoti? ";
    while (!(cin >> studentuKiekis) || studentuKiekis < 1) {
        cout << "Klaida! Iveskite teigiama skaiciu: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "---------------------------------------------------" << endl;

    for (int ii = 0; ii < studentuKiekis; ii++) {
        Studentas A;

        // Lyties pasirinkimas
        char lytis;
        bool lytisTinka = false;
        while (!lytisTinka) {
            cout << "Pasirinkite lyti (V - vyras, M - moteris): ";
            cin >> lytis;

            if (lytis == 'V' || lytis == 'v' || lytis == 'M' || lytis == 'm') {
                lytisTinka = true;
            }
            else {
                cout << "Klaida! Iveskite V arba M! " << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        // Generuojamas vardas ir pavarde pagal lyti
        if (lytis == 'V' || lytis == 'v') {
            int vardIndex = rand() % vyruVard.size();
            int pavIndex = rand() % vyruPav.size();
            A.vardas = vyruVard[vardIndex];
            A.pavarde = vyruPav[pavIndex];
        }
        else {
            int vardIndex = rand() % motVard.size();
            int pavIndex = rand() % motPav.size();
            A.vardas = motVard[vardIndex];
            A.pavarde = motPav[pavIndex];
        }

        cout << "Sugenruotas vardas ir pavarde: " << A.vardas << " " << A.pavarde << endl;
        cout << "---------------------------------------------------" << endl;

        // Klausimas kiek pazymiu sugeneruoti
        cout << "Iveskite semestro pazymiu kieki: " << endl;
        int n;
        while (!(cin >> n) || n < 0) {
            cout << "Klaida! Iveskite teigiama skaiciu: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "---------------------------------------------------" << endl;

        // Automatiskai sugeneruojami pazymiai
        cout << "Pazymiu ivertinimai: ";
        for (int i = 0; i < n; i++) {
            int temp = generuotiPazymi();
            A.paz.push_back(temp);
            cout << temp << " ";
        }
        cout << endl;

        // Automatiskai sugeneruojamas egzaminas
        A.egz = generuotiEgzamina();
        cout << "Egzamino ivertinimas: " << A.egz << endl;
        cout << "---------------------------------------------------" << endl;

        // Vidurkio skaiciavimas
        double vid = vidurkis(A.paz);
        A.rez = galutinisBalas(vid, A.egz);

        // Medianos skaiciavimas
        double med = mediana(A.paz);
        A.med = galutinisBalas(med, A.egz);

        grupe.push_back(A);
        A.paz.clear();
    }

}

void skaitytiIsFailo(vector<Studentas>& grupe) {
    string failoPavadinimas;
    cout << "Iveskite failo pavadinima: ";
    cin >> failoPavadinimas;

    // Pridedame Studentai_test kataloga
    string kelias = "..\\Studentai_test\\" + failoPavadinimas;

    ifstream failas(kelias);
    if (!failas.is_open()) {
        cout << "Klaida! Nepavyko atidaryti failo: " << kelias << endl;
        return;
    }

    // Praleisti antraste
    string eilute;
    getline(failas, eilute);

    // Skaityti studentus
    while (failas >> eilute) {
        Studentas A;
        A.vardas = eilute;
        failas >> A.pavarde;

        vector<int> paz;
        int sk;
        while (failas >> sk) {
            paz.push_back(sk);
            if (failas.peek() == '\n') break;
        }

        if (!paz.empty()) {
            A.egz = paz.back();
            paz.pop_back();
            A.paz = paz;
            A.rez = galutinisBalas(vidurkis(A.paz), A.egz);
            A.med = galutinisBalas(mediana(A.paz), A.egz);
            grupe.push_back(A);
        }
        failas.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    failas.close();
    cout << "Nuskaityta " << grupe.size() << " studentu!" << endl;
}