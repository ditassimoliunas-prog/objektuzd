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

const int MAX_STUDENTU = 1000;
const int MAX_PAZYMIU = 100;
const int MAX_VARDU = 1000;

struct Studentas {
    string vardas = "A";
    string pavarde = "BB";
    int paz[MAX_PAZYMIU];
    int pazSkaicius = 0;
    int egz = 0;
    double rez = 0.0;
    double med = 0.0;
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
double mediana(int paz[], int n) {
    if (n == 0) return 0.0;

    int temp[MAX_PAZYMIU];
    for (int i = 0; i < n; i++) {
        temp[i] = paz[i];
    }

    sort(temp, temp + n);

    if (n % 2 == 0) {
        return (temp[n / 2 - 1] + temp[n / 2]) / 2.0;
    }
    else {
        return temp[n / 2];
    }
}

void inputas(Studentas grupe[], int& grupesDydis);
void outputas(const Studentas grupe[], int grupesDydis);
void generuotiPaz(Studentas grupe[], int& grupesDydis);
void generuotiVardIrPav(Studentas grupe[], int& grupesDydis);
void menu();

int main() {
    menu();
    return 0;
}

void menu() {
    Studentas grupe[MAX_STUDENTU];
    int grupesDydis = 0;
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
            inputas(grupe, grupesDydis);
            outputas(grupe, grupesDydis);
            grupesDydis = 0; // Isvaloma grupe
            break;
        case 2:
            cout << "2. Generuoti tik pazymius " << endl;
            generuotiPaz(grupe, grupesDydis);
            outputas(grupe, grupesDydis);
            grupesDydis = 0;
            break;
        case 3:
            cout << "3. Generuoti studentu vardus, pavardes ir pazymius " << endl;
            generuotiVardIrPav(grupe, grupesDydis);
            outputas(grupe, grupesDydis);
            grupesDydis = 0;
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
}

void inputas(Studentas grupe[], int& grupesDydis) {
    int studentuKiekis;
    cout << "Kiek studentu norite sugeneruoti? ";
    while (!(cin >> studentuKiekis) || studentuKiekis < 1) {
        cout << "Klaida! Iveskite teigiama skaiciu: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "---------------------------------------------------" << endl;

    for (int ii = 0; ii < studentuKiekis; ii++) {
        if (grupesDydis >= MAX_STUDENTU) {
            cout << "Pasiektas maksimalus studentu skaicius!" << endl;
            return;
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
        cout << "Iveskite semestro ivertinimus. Kiek ju bus? " << endl;
        int n, sum = 0;
        while (!(cin >> n) || n < 0 || n > MAX_PAZYMIU) {
            cout << "Klaida! Iveskite teigiama skaiciu (max " << MAX_PAZYMIU << "): ";
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
            A.paz[i] = temp;
            sum += temp;
        }
        A.pazSkaicius = n;

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
        A.rez = sum * 1.0 / (n * 1.0) * 0.4 + A.egz * 0.6;

        // Medianos skaiciavimas
        A.med = mediana(A.paz, A.pazSkaicius) * 0.4 + A.egz * 0.6;

        grupesDydis++;
    }
}

void generuotiPaz(Studentas grupe[], int& grupesDydis) {
    srand(time(0));

    int studentuKiekis;
    cout << "Kiek studentu norite sugeneruoti? ";
    while (!(cin >> studentuKiekis) || studentuKiekis < 1) {
        cout << "Klaida! Iveskite teigiama skaiciu: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "---------------------------------------------------" << endl;

    for (int ii = 0; ii < studentuKiekis; ii++) {
        if (grupesDydis >= MAX_STUDENTU) {
            cout << "Pasiektas maksimalus studentu skaicius!" << endl;
            return;
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
        cout << "Iveskite semestro pazymiu ivertinmu kieki: " << endl;
        int n, sum = 0;
        while (!(cin >> n) || n < 0 || n > MAX_PAZYMIU) {
            cout << "Klaida! Iveskite teigiama skaiciu (max " << MAX_PAZYMIU << "): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "---------------------------------------------------" << endl;

        // Automatiskai generuojami pazymiai
        cout << "Pazymiu ivertinmai: ";
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
        A.rez = sum * 1.0 / (n * 1.0) * 0.4 + A.egz * 0.6;

        // Medianos skaiciavimas
        A.med = mediana(A.paz, A.pazSkaicius) * 0.4 + A.egz * 0.6;

        grupesDydis++;
    }
}

void generuotiVardIrPav(Studentas grupe[], int& grupesDydis) {
    srand(time(0));

    // Nuskaitome failus i masyvus
    string vyruVard[MAX_VARDU], vyruPav[MAX_VARDU];
    string motVard[MAX_VARDU], motPav[MAX_VARDU];
    int vyruVardSkaicius = 0, vyruPavSkaicius = 0;
    int motVardSkaicius = 0, motPavSkaicius = 0;

    ifstream vvard("../../vpv/vvard.txt");
    ifstream vpav("../../vpv/vpav.txt");
    ifstream mvard("../../vpv/mvard.txt");
    ifstream mpav("../../vpv/mpav.txt");

    // Patikrinimas ar failai atsidare
    if (!vvard.is_open() || !vpav.is_open() || !mvard.is_open() || !mpav.is_open()) {
        cout << "Klaida! Nepavyko atidaryti vieno ar daugiau failu su vardais ir pavardemis " << endl;
        return;
    }

    // Nuskaitomi visi vardai ir pavardes
    string eilute;
    while (vvard >> eilute && vyruVardSkaicius < MAX_VARDU) {
        vyruVard[vyruVardSkaicius++] = eilute;
    }
    while (vpav >> eilute && vyruPavSkaicius < MAX_VARDU) {
        vyruPav[vyruPavSkaicius++] = eilute;
    }
    while (mvard >> eilute && motVardSkaicius < MAX_VARDU) {
        motVard[motVardSkaicius++] = eilute;
    }
    while (mpav >> eilute && motPavSkaicius < MAX_VARDU) {
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
        if (grupesDydis >= MAX_STUDENTU) {
            cout << "Pasiektas maksimalus studentu skaicius!" << endl;
            return;
        }

        Studentas& A = grupe[grupesDydis];

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

        // Klausimas kiek pazymiu sugeneruoti
        cout << "Iveskite semestro pazymiu ivertinimu kieki: " << endl;
        int n, sum = 0;
        while (!(cin >> n) || n < 0 || n > MAX_PAZYMIU) {
            cout << "Klaida! Iveskite teigiama skaiciu (max " << MAX_PAZYMIU << "): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "---------------------------------------------------" << endl;

        // Automatiskai sugeneruojami pazymiai
        cout << "Pazymiu ivertinimai: ";
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
        A.rez = sum * 1.0 / (n * 1.0) * 0.4 + A.egz * 0.6;

        // Medianos skaiciavimas
        A.med = mediana(A.paz, A.pazSkaicius) * 0.4 + A.egz * 0.6;

        grupesDydis++;
    }
}

void outputas(const Studentas grupe[], int grupesDydis) {
    for (int i = 0; i < grupesDydis; i++) {
        const Studentas& A = grupe[i];
        cout << left << setw(10) << "Vardas " << left << setw(20) << "Pavarde "
            << left << setw(30) << "Galutinis (Vid.) " << left << setw(40) << "Galutinis (Med.) " << endl;
        cout << left << setw(10) << A.vardas << left << setw(20) << A.pavarde;
        cout << left << setw(30) << fixed << setprecision(2) << A.rez
            << left << setw(40) << fixed << setprecision(2) << A.med << endl;
    }
}
