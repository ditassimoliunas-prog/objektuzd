#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <limits>
#include <random>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <stdexcept>

#include "../header_files/duomenu_valdymas.h"
#include "../header_files/mat_funkcijos.h"
#include "../header_files/output.h"

using std::cin;
using std::cout;
using std::string;
using std::vector;
using std::numeric_limits;
using std::streamsize;
using std::ifstream;
using std::ofstream;
using std::endl;
using std::left;
using std::setw;
using std::fixed;
using std::setprecision;
using std::sort;
using std::chrono::high_resolution_clock;
using std::chrono::duration;
using std::runtime_error;
using std::exception;




// Atsitiktiniiu skaiciu generavimas
void generuotiPaz(vector<Studentas>& grupe) {
    srand(time(0));

    bool testiStudenta = true;

    while (testiStudenta) {
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

        // Automatiskai generuojamas atsitiktinis pazymiu kiekis (3-10)
        int n = rand() % 8 + 3;

        // Automatiskai generuojami pazymiai
        cout << "Sugeneruota " << n << " pazymiu: ";
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

        // Klausimas ar testi
        char atsakymas;
        bool atsakymasTeisingas = false;
        while (!atsakymasTeisingas) {
            cout << "Ar norite generuoti dar viena studenta? (T/N): ";
            cin >> atsakymas;
            if (atsakymas == 'T' || atsakymas == 't') {
                testiStudenta = true;
                atsakymasTeisingas = true;
                cout << "---------------------------------------------------" << endl;
            }
            else if (atsakymas == 'N' || atsakymas == 'n') {
                testiStudenta = false;
                atsakymasTeisingas = true;
            }
            else {
                cout << "Klaida! Iveskite T arba N!" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }
}

void generuotiVardIrPav(vector<Studentas>& grupe) {
    srand(time(0));

    try {
        // Nuskaitome failus
        vector<string> vyruVard, vyruPav, motVard, motPav;
        ifstream vvard("../vpv/vvard.txt");
        ifstream vpav("../vpv/vpav.txt");
        ifstream mvard("../vpv/mvard.txt");
        ifstream mpav("../vpv/mpav.txt");

        // Patikrinimas ar failai atsidare
        if (!vvard.is_open() || !vpav.is_open() || !mvard.is_open() || !mpav.is_open()) {
            throw runtime_error("Nepavyko atidaryti vieno ar daugiau failu su vardais ir pavardemis!");
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
            throw runtime_error("Vienas ar daugiau failu yra tusti!");
        }

    bool testiStudenta = true;

    while (testiStudenta) {
        Studentas A;

        // Atsitiktinai parenka lyti (0 - vyras, 1 - moteris)
        int lytis = rand() % 2;

        // Generuojamas vardas ir pavarde pagal lyti
        if (lytis == 0) {
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

        cout << "Sugeneruotas vardas ir pavarde: " << A.vardas << " " << A.pavarde << endl;
        cout << "---------------------------------------------------" << endl;

        // Automatiskai generuojamas atsitiktinis pazymiu kiekis (3-10)
        int n = rand() % 8 + 3;

        // Automatiskai sugeneruojami pazymiai
        cout << "Sugeneruota " << n << " pazymiu: ";
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

        // Klausimas ar testi
        char atsakymas;
        bool atsakymasTeisingas = false;
        while (!atsakymasTeisingas) {
            cout << "Ar norite generuoti dar viena studenta? (T/N): ";
            cin >> atsakymas;
            if (atsakymas == 'T' || atsakymas == 't') {
                testiStudenta = true;
                atsakymasTeisingas = true;
                cout << "---------------------------------------------------" << endl;
            }
            else if (atsakymas == 'N' || atsakymas == 'n') {
                testiStudenta = false;
                atsakymasTeisingas = true;
            }
            else {
                cout << "Klaida! Iveskite T arba N!" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }
    }
    catch (const runtime_error& e) {
        cout << "Klaida generuojant studentus: " << e.what() << endl;
    }
    catch (const exception& e) {
        cout << "Netiketa klaida: " << e.what() << endl;
    }
}

void skaitytiIsFailo(vector<Studentas>& grupe) {
    try {
        string failoPavadinimas;
        cout << "Iveskite failo pavadinima: ";
        cin >> failoPavadinimas;

        // Pridedame Studentai_test kataloga
        string kelias = "..\\Studentai_test\\" + failoPavadinimas;

        ifstream failas(kelias);
        if (!failas.is_open()) {
            throw runtime_error("Nepavyko atidaryti failo: " + kelias);
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

        if (grupe.empty()) {
            throw runtime_error("Failas yra tuscias arba neteisingai formatuotas!");
        }

        cout << "Nuskaityta " << grupe.size() << " studentu!" << endl;

        // Klausiame kur isvesti rezultatus
        if (!grupe.empty()) {
            cout << "---------------------------------------------------" << endl;
            cout << "Pasirinkite isvesties buda:" << endl;
            cout << "1. Isvesti i terminala" << endl;
            cout << "2. Irasyti i faila" << endl;
            int isvestiesPasirinkimas;
            while (!(cin >> isvestiesPasirinkimas) || (isvestiesPasirinkimas != 1 && isvestiesPasirinkimas != 2)) {
                cout << "Klaida! Pasirinkite 1 arba 2: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            if (isvestiesPasirinkimas == 1) {
                outputas(grupe);
            }
            else {
                rasytIFaila(grupe);
            }
        }
    }
    catch (const runtime_error& e) {
        cout << "Klaida skaitant is failo: " << e.what() << endl;
    }
    catch (const exception& e) {
        cout << "Netiketa klaida: " << e.what() << endl;
    }
}

void rasytIFaila(vector<Studentas>& grupe) {
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

    // Klausiame failo pavadinimo
    string isvestiesFailas;
    cout << "---------------------------------------------------" << endl;
    cout << "Iveskite isvesties failo pavadinima: ";
    cin >> isvestiesFailas;

    // Sukuriame kelią į Studentai_test katalogą
    string kelias = "..\\Studentai_test\\" + isvestiesFailas;

    ofstream failas(kelias);
    if (!failas.is_open()) {
        cout << "Klaida! Nepavyko sukurti failo: " << kelias << endl;
        return;
    }

    // Antrastes eilute
    failas << left << setw(20) << "Vardas" << setw(20) << "Pavarde"
        << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)" << endl;
    failas << string(80, '-') << endl;

    // Studentu duomenys
    for (const auto& A : grupe) {
        failas << left << setw(20) << A.vardas << setw(20) << A.pavarde
            << setw(20) << fixed << setprecision(2) << A.rez
            << setw(20) << fixed << setprecision(2) << A.med << endl;
    }

    failas.close();

    // Baigiamas rusiavimo ir rasymo laiko matavimas
    auto pabaiga = high_resolution_clock::now();
    duration<double> trukme = pabaiga - pradzia;
    cout << "---------------------------------------------------" << endl;
    cout << "Duomenys sekmingai irasyti i faila: " << kelias << endl;
    cout << "Ivykdymo laikas: " << fixed << setprecision(7) << trukme.count() << " s" << endl;
}