#include <iomanip>
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <limits>
#include <ctime>
#include <fstream>

using std::cin;
using std::cout;
using std::string;
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
    string vardas = "A";
    string pavarde = "BB";
    int* paz;
    int pazSkaicius = 0;
    int pazTalpa = 0;
    int egz = 0;
    double rez = 0.0;
    double med = 0.0;

    Studentas() : paz(nullptr), pazSkaicius(0), pazTalpa(0), egz(0), rez(0.0), med(0.0) {}

    ~Studentas() {
        delete[] paz;
    }
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
double mediana(int* paz, int n) {
    if (n == 0) return 0.0;

    int* temp = new int[n];
    for (int i = 0; i < n; i++) {
        temp[i] = paz[i];
    }

    sort(temp, temp + n);

    double result;
    if (n % 2 == 0) {
        result = (temp[n / 2 - 1] + temp[n / 2]) / 2.0;
    }
    else {
        result = temp[n / 2];
    }

    delete[] temp;
    return result;
}

void inputas(Studentas*& grupe, int& grupesDydis, int& grupeTalpa);
void outputas(const Studentas* grupe, int grupesDydis);
void generuotiPaz(Studentas*& grupe, int& grupesDydis, int& grupeTalpa);
void generuotiVardIrPav(Studentas*& grupe, int& grupesDydis, int& grupeTalpa);
void menu();

int main() {
    menu();
    return 0;
}

void menu() {
    Studentas* grupe = nullptr;
    int grupesDydis = 0;
    int grupeTalpa = 0;
    int pas;
    bool testi = true;

    while (testi) {
        cout << "---------------------------------------------------" << endl;
        cout << "Studentu Rezultatu skaiciavimo aplikacija (Masyvai) " << endl;
        cout << "---------------------------------------------------" << endl;
        cout << "1. Ivesti duomenis ranka " << endl;
        cout << "2. Generuoti tik pazymius " << endl;
        cout << "3. Generuoti studentu vardus, pavardes ir pazymius " << endl;
        cout << "4. Baigti darba " << endl;
        cin >> pas;

        switch (pas) {
        case 1:
            cout << "1. Ivesti duomenis ranka " << endl;
            delete[] grupe;
            grupe = nullptr;
            grupesDydis = 0;
            grupeTalpa = 0;
            inputas(grupe, grupesDydis, grupeTalpa);
            outputas(grupe, grupesDydis);
            break;
        case 2:
            cout << "2. Generuoti tik pazymius " << endl;
            delete[] grupe;
            grupe = nullptr;
            grupesDydis = 0;
            grupeTalpa = 0;
            generuotiPaz(grupe, grupesDydis, grupeTalpa);
            outputas(grupe, grupesDydis);
            break;
        case 3:
            cout << "3. Generuoti studentu vardus, pavardes ir pazymius " << endl;
            delete[] grupe;
            grupe = nullptr;
            grupesDydis = 0;
            grupeTalpa = 0;
            generuotiVardIrPav(grupe, grupesDydis, grupeTalpa);
            outputas(grupe, grupesDydis);
            break;
        case 4:
            cout << "Programa uzdaroma " << endl;
            testi = false;
            break;
        default:
            cout << "Klaida! Pasirinkite skaiciu nuo 1 iki 4 " << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            break;
        }
    }

    delete[] grupe;
}

void inputas(Studentas*& grupe, int& grupesDydis, int& grupeTalpa) {
    bool testiStudenta = true;

    grupeTalpa = 10;
    grupe = new Studentas[grupeTalpa];

    while (testiStudenta) {
        if (grupesDydis >= grupeTalpa) {
            grupeTalpa *= 2;
            Studentas* naujaGrupe = new Studentas[grupeTalpa];
            for (int i = 0; i < grupesDydis; i++) {
                naujaGrupe[i].vardas = grupe[i].vardas;
                naujaGrupe[i].pavarde = grupe[i].pavarde;
                naujaGrupe[i].paz = grupe[i].paz;
                naujaGrupe[i].pazSkaicius = grupe[i].pazSkaicius;
                naujaGrupe[i].pazTalpa = grupe[i].pazTalpa;
                naujaGrupe[i].egz = grupe[i].egz;
                naujaGrupe[i].rez = grupe[i].rez;
                naujaGrupe[i].med = grupe[i].med;
                grupe[i].paz = nullptr;
            }
            delete[] grupe;
            grupe = naujaGrupe;
        }

        Studentas& A = grupe[grupesDydis];

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
        int pazTalpa = 10;
        A.paz = new int[pazTalpa];
        A.pazSkaicius = 0;

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
                if (A.pazSkaicius >= pazTalpa) {
                    pazTalpa *= 2;
                    int* naujasPaz = new int[pazTalpa];
                    for (int i = 0; i < A.pazSkaicius; i++) {
                        naujasPaz[i] = A.paz[i];
                    }
                    delete[] A.paz;
                    A.paz = naujasPaz;
                }
                A.paz[A.pazSkaicius++] = temp;
                sum += temp;
            }
        }
        A.pazTalpa = pazTalpa;

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
        if (A.pazSkaicius > 0) {
            A.rez = sum * 1.0 / A.pazSkaicius * 0.4 + A.egz * 0.6;
            // Medianos skaiciavimas
            A.med = mediana(A.paz, A.pazSkaicius) * 0.4 + A.egz * 0.6;
        }
        else {
            A.rez = A.egz * 0.6;
            A.med = A.egz * 0.6;
        }

        grupesDydis++;

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

void generuotiPaz(Studentas*& grupe, int& grupesDydis, int& grupeTalpa) {
    srand(time(0));

    bool testiStudenta = true;

    grupeTalpa = 10;
    grupe = new Studentas[grupeTalpa];

    while (testiStudenta) {
        if (grupesDydis >= grupeTalpa) {
            grupeTalpa *= 2;
            Studentas* naujaGrupe = new Studentas[grupeTalpa];
            for (int i = 0; i < grupesDydis; i++) {
                naujaGrupe[i].vardas = grupe[i].vardas;
                naujaGrupe[i].pavarde = grupe[i].pavarde;
                naujaGrupe[i].paz = grupe[i].paz;
                naujaGrupe[i].pazSkaicius = grupe[i].pazSkaicius;
                naujaGrupe[i].pazTalpa = grupe[i].pazTalpa;
                naujaGrupe[i].egz = grupe[i].egz;
                naujaGrupe[i].rez = grupe[i].rez;
                naujaGrupe[i].med = grupe[i].med;
                grupe[i].paz = nullptr;
            }
            delete[] grupe;
            grupe = naujaGrupe;
        }

        Studentas& A = grupe[grupesDydis];

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

        A.paz = new int[n];
        A.pazTalpa = n;

        // Automatiskai generuojami pazymiai
        cout << "Sugeneruota " << n << " pazymiu: ";
        for (int i = 0; i < n; i++) {
            int temp = rand() % 11;
            A.paz[i] = temp;
            sum += temp;
            cout << temp << " ";
        }
        A.pazSkaicius = n;
        cout << endl;

        // Automatiskai generuojamas egzaminas
        A.egz = rand() % 11;
        cout << "Egzamino ivertinimas: " << A.egz << endl;
        cout << "---------------------------------------------------" << endl;

        // Vidurkio skaiciavimas
        if (A.pazSkaicius > 0) {
            A.rez = sum * 1.0 / A.pazSkaicius * 0.4 + A.egz * 0.6;
            // Medianos skaiciavimas
            A.med = mediana(A.paz, A.pazSkaicius) * 0.4 + A.egz * 0.6;
        }
        else {
            A.rez = A.egz * 0.6;
            A.med = A.egz * 0.6;
        }

        grupesDydis++;

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

void generuotiVardIrPav(Studentas*& grupe, int& grupesDydis, int& grupeTalpa) {
    srand(time(0));

    // Nuskaitome failus i dinaminius masyvus
    string* vyruVard = nullptr;
    string* vyruPav = nullptr;
    string* motVard = nullptr;
    string* motPav = nullptr;
    int vyruVardSkaicius = 0, vyruPavSkaicius = 0;
    int motVardSkaicius = 0, motPavSkaicius = 0;
    int vyruVardTalpa = 100, vyruPavTalpa = 100;
    int motVardTalpa = 100, motPavTalpa = 100;

    vyruVard = new string[vyruVardTalpa];
    vyruPav = new string[vyruPavTalpa];
    motVard = new string[motVardTalpa];
    motPav = new string[motPavTalpa];

    ifstream vvard("../../vpv/vvard.txt");
    ifstream vpav("../../vpv/vpav.txt");
    ifstream mvard("../../vpv/mvard.txt");
    ifstream mpav("../../vpv/mpav.txt");

    // Patikrinimas ar failai atsidare
    if (!vvard.is_open() || !vpav.is_open() || !mvard.is_open() || !mpav.is_open()) {
        cout << "Klaida! Nepavyko atidaryti vieno ar daugiau failu su vardais ir pavardemis " << endl;
        delete[] vyruVard;
        delete[] vyruPav;
        delete[] motVard;
        delete[] motPav;
        return;
    }

    // Nuskaitomi visi vardai ir pavardes
    string eilute;
    while (vvard >> eilute) {
        if (vyruVardSkaicius >= vyruVardTalpa) {
            vyruVardTalpa *= 2;
            string* naujasVyruVard = new string[vyruVardTalpa];
            for (int i = 0; i < vyruVardSkaicius; i++) {
                naujasVyruVard[i] = vyruVard[i];
            }
            delete[] vyruVard;
            vyruVard = naujasVyruVard;
        }
        vyruVard[vyruVardSkaicius++] = eilute;
    }
    while (vpav >> eilute) {
        if (vyruPavSkaicius >= vyruPavTalpa) {
            vyruPavTalpa *= 2;
            string* naujasVyruPav = new string[vyruPavTalpa];
            for (int i = 0; i < vyruPavSkaicius; i++) {
                naujasVyruPav[i] = vyruPav[i];
            }
            delete[] vyruPav;
            vyruPav = naujasVyruPav;
        }
        vyruPav[vyruPavSkaicius++] = eilute;
    }
    while (mvard >> eilute) {
        if (motVardSkaicius >= motVardTalpa) {
            motVardTalpa *= 2;
            string* naujasMotVard = new string[motVardTalpa];
            for (int i = 0; i < motVardSkaicius; i++) {
                naujasMotVard[i] = motVard[i];
            }
            delete[] motVard;
            motVard = naujasMotVard;
        }
        motVard[motVardSkaicius++] = eilute;
    }
    while (mpav >> eilute) {
        if (motPavSkaicius >= motPavTalpa) {
            motPavTalpa *= 2;
            string* naujasMotPav = new string[motPavTalpa];
            for (int i = 0; i < motPavSkaicius; i++) {
                naujasMotPav[i] = motPav[i];
            }
            delete[] motPav;
            motPav = naujasMotPav;
        }
        motPav[motPavSkaicius++] = eilute;
    }

    vvard.close();
    vpav.close();
    mvard.close();
    mpav.close();

    // Patikrinama ar failai ne tusti
    if (vyruVardSkaicius == 0 || vyruPavSkaicius == 0 ||
        motVardSkaicius == 0 || motPavSkaicius == 0) {
        cout << "Klaida! Vienas ar daugiau failu yra tusti! " << endl;
        delete[] vyruVard;
        delete[] vyruPav;
        delete[] motVard;
        delete[] motPav;
        return;
    }

    bool testiStudenta = true;

    grupeTalpa = 10;
    grupe = new Studentas[grupeTalpa];

    while (testiStudenta) {
        if (grupesDydis >= grupeTalpa) {
            grupeTalpa *= 2;
            Studentas* naujaGrupe = new Studentas[grupeTalpa];
            for (int i = 0; i < grupesDydis; i++) {
                naujaGrupe[i].vardas = grupe[i].vardas;
                naujaGrupe[i].pavarde = grupe[i].pavarde;
                naujaGrupe[i].paz = grupe[i].paz;
                naujaGrupe[i].pazSkaicius = grupe[i].pazSkaicius;
                naujaGrupe[i].pazTalpa = grupe[i].pazTalpa;
                naujaGrupe[i].egz = grupe[i].egz;
                naujaGrupe[i].rez = grupe[i].rez;
                naujaGrupe[i].med = grupe[i].med;
                grupe[i].paz = nullptr;
            }
            delete[] grupe;
            grupe = naujaGrupe;
        }

        Studentas& A = grupe[grupesDydis];

        // Atsitiktinai parenka lyti (0 - vyras, 1 - moteris)
        int lytis = rand() % 2;

        // Generuojamas vardas ir pavarde pagal lyti
        if (lytis == 0) {
            int vardIndex = rand() % vyruVardSkaicius;
            int pavIndex = rand() % vyruPavSkaicius;
            A.vardas = vyruVard[vardIndex];
            A.pavarde = vyruPav[pavIndex];
        }
        else {
            int vardIndex = rand() % motVardSkaicius;
            int pavIndex = rand() % motPavSkaicius;
            A.vardas = motVard[vardIndex];
            A.pavarde = motPav[pavIndex];
        }

        cout << "Sugeneruotas vardas ir pavarde: " << A.vardas << " " << A.pavarde << endl;
        cout << "---------------------------------------------------" << endl;

        // Automatiskai generuojamas atsitiktinis pazymiu kiekis (3-10)
        int n = rand() % 8 + 3;
        int sum = 0;

        A.paz = new int[n];
        A.pazTalpa = n;

        // Automatiskai sugeneruojami pazymiai
        cout << "Sugeneruota " << n << " pazymiu: ";
        for (int i = 0; i < n; i++) {
            int temp = rand() % 11;
            A.paz[i] = temp;
            sum += temp;
            cout << temp << " ";
        }
        A.pazSkaicius = n;
        cout << endl;

        // Automatiskai sugeneruojamas egzaminas
        A.egz = rand() % 11;
        cout << "Egzamino ivertinimas: " << A.egz << endl;
        cout << "---------------------------------------------------" << endl;

        // Vidurkio skaiciavimas
        A.rez = sum * 1.0 / A.pazSkaicius * 0.4 + A.egz * 0.6;

        // Medianos skaiciavimas
        A.med = mediana(A.paz, A.pazSkaicius) * 0.4 + A.egz * 0.6;

        grupesDydis++;

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

    delete[] vyruVard;
    delete[] vyruPav;
    delete[] motVard;
    delete[] motPav;
}

void outputas(const Studentas* grupe, int grupesDydis) {
    for (int i = 0; i < grupesDydis; i++) {
        const Studentas& A = grupe[i];
        cout << left << setw(10) << "Vardas " << left << setw(20) << "Pavarde "
            << left << setw(30) << "Galutinis (Vid.) " << left << setw(40) << "Galutinis (Med.) " << endl;
        cout << left << setw(10) << A.vardas << left << setw(20) << A.pavarde;
        cout << left << setw(30) << fixed << setprecision(2) << A.rez
            << left << setw(40) << fixed << setprecision(2) << A.med << endl;
    }
}
