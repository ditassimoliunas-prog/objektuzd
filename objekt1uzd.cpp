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

struct Studentas {
    string vardas = "A", pavarde = "BB";
    // int paz jei dinaminis masyvas
    vector <int> paz;
    int egz;
    double rez;
    double med;
};

// Funkcija patikrinti ar vardas/pavarde turi tik raides
bool arTikRaides(const string& str) {
    if (str.empty()) return false;
    for (char c : str) {
        if (!std::isalpha(c)) {
            return false;
        }
    }
    return true;
}

// Medianos funkcija
double mediana(vector <int> paz) {
    if (paz.empty()) return 0.0;

    vector <int> temp = paz;
    sort(temp.begin(), temp.end());
    int n = temp.size();
    if (n % 2 == 0) {
        return (temp[n / 2 - 1] + temp[n / 2]) / 2.0;
    }
    else {
        return temp[n / 2];
    }
}

void inputas(vector<Studentas>& grupe);
void outputas(const vector<Studentas>& grupe);
void generuotiPaz(vector<Studentas>& grupe);
void generuotiVardIrPav(vector<Studentas>& grupe);
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
        cout << "Studentu Rezultatu skaiciavimo aplikacija (Vektoriai) " << endl;
        cout << "---------------------------------------------------" << endl;
        cout << "1. Ivesti duomenis ranka " << endl;
        cout << "2. Generuoti tik pazymius " << endl;
        cout << "3. Generuoti studentu vardus, pavardes ir pazymius " << endl;
        cout << "4. Baigti darba " << endl;
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
            cout << "Programa uzdaroma " << endl;
            testi = false;
            break;

        // Isvestus ivedus netinkama pasirinkima
        default:
            cout << "Klaida! Pasirinkite skaiciu nuo 1 iki 4 " << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            break;
        }
    }
}
void inputas(vector<Studentas>& grupe) {
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
        cout << "Iveskite semestro ivertinimus (0-10). Iveskite -1 kad baigtumete: " << endl;
        int temp, sum = 0;
        while (true) {
            cout << "Iveskite pazymi (arba -1 kad baigtumete): ";
            if (!(cin >> temp)) {
                cout << "Klaida! Iveskite skaiciu!" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else if (temp == -1) {
                break;
            }
            else if (temp < 0 || temp > 10) {
                cout << "Klaida! Pazymys turi buti nuo 0 iki 10!" << endl;
            }
            else {
                A.paz.push_back(temp);
                sum += temp;
            }
        }

        cout << "---------------------------------------------------" << endl;

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
        if (!A.paz.empty()) {
            A.rez = sum * 1.0 / A.paz.size() * 0.4 + A.egz * 0.6;
            // Medianos skaiciavimas
            A.med = mediana(A.paz) * 0.4 + A.egz * 0.6;
        }
        else {
            A.rez = A.egz * 0.6;
            A.med = A.egz * 0.6;
        }

        // galima priskirti grupej, kai turime A.rez; pushbackinam studento varda
        grupe.push_back(A);
        A.paz.clear();

        // Klausimas ar testi
        char atsakymas;
        bool atsakymasTeisingas = false;
        while (!atsakymasTeisingas) {
            cout << "Ar norite ivesti dar viena studenta? (T/N): ";
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
        int sum = 0;

        // Automatiskai generuojami pazymiai
        cout << "Sugeneruota " << n << " pazymiu: ";
        for (int i = 0; i < n; i++) {
            int temp = rand() % 11;
            A.paz.push_back(temp);
            sum += temp;
            cout << temp << " ";
        }
        cout << endl;

        // Automatiskai generuojamas egzaminas
        A.egz = rand() % 11;
        cout << "Egzamino ivertinimas: " << A.egz << endl;
        cout << "---------------------------------------------------" << endl;

        // Vidurkio skaiciavimas
        if (!A.paz.empty()) {
            A.rez = sum * 1.0 / A.paz.size() * 0.4 + A.egz * 0.6;
            // Medianos skaiciavimas
            A.med = mediana(A.paz) * 0.4 + A.egz * 0.6;
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
            cout << "Ar norite ivesti dar viena studenta? (T/N): ";
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
        int sum = 0;

        // Automatiskai generuojami pazymiai
        cout << "Sugeneruota " << n << " pazymiu: ";
        for (int i = 0; i < n; i++) {
            int temp = rand() % 11;
            A.paz.push_back(temp);
            sum += temp;
            cout << temp << " ";
        }
        cout << endl;

        // Automatiskai sugeneruojamas egzaminas
        A.egz = rand() % 11;
        cout << "Egzamino ivertinimas: " << A.egz << endl;
        cout << "---------------------------------------------------" << endl;

        // Vidurkio skaiciavimas
        if (!A.paz.empty()) {
            A.rez = sum * 1.0 / A.paz.size() * 0.4 + A.egz * 0.6;
            // Medianos skaiciavimas
            A.med = mediana(A.paz) * 0.4 + A.egz * 0.6;
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



void outputas(const vector<Studentas>& grupe) {
    cout << left << setw(10) << "Vardas " << left << setw(20) << "Pavarde " << left << setw(30) << "Galutinis (Vid.) " << left << setw(40) << "Galutinis (Med.) " << endl;
    for (auto A : grupe) {
        cout << left << setw(10) << A.vardas << left << setw(20) << A.pavarde;
        //for (auto k : A.paz) cout << setw(3) << k;
        //cout << setw(5) << A.egz;
        cout << left << setw(30) << fixed << setprecision(2) << A.rez << left << setw(40) << fixed << setprecision(2) << A.med << endl;
    }
}