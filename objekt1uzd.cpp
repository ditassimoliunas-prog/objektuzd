#include <iomanip>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <limits>
#include <random>
#include <ctime>
#include <fstream>
#include <filesystem>
#include <chrono>

#include "extra_cpp/mat_funkcijos.cpp"
#include "header_files/input.h"

using std::cin;
using std::cout;
using std::string;
using std::vector;
using std::numeric_limits;
using std::streamsize;
using std::ifstream;
using std::left;
using std::right;
using std::setw;
using std::endl;
using std::setprecision;
using std::sort;
using std::fixed;
using std::chrono::high_resolution_clock;
using std::chrono::duration;

void outputas(vector<Studentas>& grupe);
void generuotiPaz(vector<Studentas>& grupe);
void generuotiVardIrPav(vector<Studentas>& grupe);
void skaitytiIsFailo(vector<Studentas>& grupe);
void menu();
int main() {
    menu();
    return 0;
}

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
            outputas(grupe);
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

    for (int ii = 0; ii < studentuKiekis; ii++ ) {
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