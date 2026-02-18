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
using std::left;
using std::right;
using std::setw;
using std::endl;
using std::setprecision;
using std::sort;
using std::fixed;


struct Studentas {
    string vardas = "A", pavarde = "BB";
    //int  *paz jei dinaminis masyvas
    vector <int> paz;
    int egz;
    double rez;
    double med;
};

//Funkcija patikrinti ar vardas/pavarde turi tik raides
bool arTikRaides(const string& str) {
    if (str.empty()) return false;
    for (char c : str) {
        if (!std::isalpha(c)) {
            return false;
        }
    }
    return true;
}

//Medianos funkcija
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
void menu();
int main() {
    menu();
    return 0;
}

void menu() {
    vector<Studentas>grupe;
    int pas; //pasirinkimas
    bool testi = true;

    while (testi) {
        cout << "---------------------------------------------------" << endl;
        cout << "Studentu Rezultatu skaiciavimo aplikacija " << endl;
        cout << "---------------------------------------------------" << endl;
        cout << "1. Ivesti duomenis ranka " << endl;
        cout << "2. Generuoti tik pazymius " << endl;
        cout << "3. Generuoti studentu vardus, pavardes ir pazymius " << endl;
        cout << "4. Baigti darba " << endl;
        cin >> pas;

        //pasirinkimo isvestys
        switch (pas) {
        case 1:
            cout << "1. Ivesti duomenis ranka " << endl;
            inputas(grupe);
            outputas(grupe);
            break;
        case 2:
            cout << "2. Generuoti tik pazymius " << endl;
			generuotiPaz(grupe);
			outputas(grupe);
            break;
        case 3:
            cout << "3. Generuoti studentu vardus, pavardes ir pazymius " << endl;
            cout << "Funkcija dar nesukurta " << endl;
            break;
        case 4:
            cout << "Programa uzdaroma " << endl;
            testi = false;
            break;

        //Isvestus ivedus netinkama pasirinkima
        default:
            cout << "Klaida! Pasirinkite skaiciu nuo 1 iki 4 " << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            break;
        }
    }
}
void inputas(vector<Studentas>& grupe) {
    for (int ii = 0; ii < 2; ii++) {
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
        int n, sum = 0;
        while (!(cin >> n) || n < 0) {
            cout << "Klaida! Iveskite teigiama skaiciu: ";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                else if (temp < 0 || temp > 10) {
                    cout << "Klaida! Pazymys turi buti nuo 0 iki 10!" << endl;
                }
                else {
                    pazymisTeisingas = true;
                }
            }
            A.paz.push_back(temp);
            sum += temp;
        }

        bool egzaminasTeisingas = false;
        while (!egzaminasTeisingas) {
            cout << "Iveskite egzamina (0-10): ";
            if (!(cin >> A.egz)) {
                cout << "Klaida! Iveskite skaiciu!" << endl;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
        A.med = mediana(A.paz) * 0.4 + A.egz * 0.6;

        grupe.push_back(A);
        A.paz.clear();

    }// galima priskirti grupej, kai turime A.rez; pushbackinam studento varda
}

// Atsitiktiniiu skaiciu generavimas
void generuotiPaz(vector <Studentas>& grupe) {
    srand(time(0)); //Inicializuoja atsitiktine seed pagal laika

    for (int ii = 0; ii < 2; ii++ ) {
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
        cout << "Iveskite semestro pazymiu ivertinmu kieki: " << endl;
        int n, sum = 0;
        while (!(cin >> n) || n < 0) {
            cout << "Klaida! Iveskite teigiama skaiciu: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "---------------------------------------------------" << endl;

        // Automatiskai generuojami pazymiai
        // cout << "Pazymiu ivertinmai: ";
        for (int i = 0; i < n; i++) {
            int temp = rand() % 11; //Sugeneruoja skaiciu nuo 0 iki 10
            A.paz.push_back(temp);
            sum += temp;
            // cout << temp << " ";
        }

        // cout << endl;

        // Automatiskai generuojamas egzaminas
        A.egz = rand() % 11;
        // cout << "Egzamino ivertinimas: " << A.egz << endl;
        // cout << "---------------------------------------------------" << endl;

        // Vidurkio skaiciavimas
        A.rez = sum * 1.0 / (n * 1.0) * 0.4 + A.egz * 0.6;

        // Medianos skaiciavimas
        A.med = mediana(A.paz) * 0.4 + A.egz * 0.6;

        grupe.push_back(A);
        A.paz.clear();
    }  
}



void outputas(const vector <Studentas> &grupe) {
    for (auto A : grupe) {
        cout << left << setw(10) << "Vardas " << left << setw(20) << "Pavarde " << left << setw(30) << "Galutinis (Vid.) " << left << setw(40) << "Galutinis (Med.) " << endl;
        cout << left << setw(10) << A.vardas << left << setw(20) << A.pavarde;
        //for (auto k : A.paz) cout << setw(3) << k;
        //cout << setw(5) << A.egz;
        cout << left << setw(30) << fixed << setprecision(2) << A.rez << left << setw(40) << fixed << setprecision(2) << A.med << endl;
    }
}