#include <iomanip>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

using std::cin;
using std::cout;
using std::string;
using std::vector;
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
        cout << "----------------------------------------------" << endl;
        cout << " Studentu Rezultatu skaiciavimo aplikacija " << endl;
        cout << "----------------------------------------------" << endl;
        cout << "1. Ivesti duomenis ranka " << endl;
        cout << "2. Generuoti tik pazymius " << endl;
        cout << "3. Generuoti studentu vardus, pavardes ir pazymius " << endl;
        cout << "4. Baigti darba " << endl;
        cin >> pas;

        switch (pas) {
        case 1:
            cout << "1. Ivesti duomenis ranka " << endl;
            inputas(grupe);
            break;
        case 2:
            cout << "2. Generuoti tik pazymius " << endl;
            cout << "Funkcija dar nesukurta " << endl;
            break;
        case 3:
            cout << "3. Generuoti studentu vardus, pavardes ir pazymius " << endl;
            cout << "Funkcija dar nesukurta " << endl;
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
void inputas(vector<Studentas>& grupe) {
    for (int ii = 0; ii < 2; ii++) {
        Studentas A;

        cout << "Iveskite varda ir pavarde: ";
        cin >> A.vardas >> A.pavarde;
        cout << "----------------------------------------------" << endl;
        cout << "Iveskite semestro ivertinimus. Kiek ju bus? " << endl;
        int n, sum = 0;
        cin >> n;
        cout << "----------------------------------------------" << endl;
        for (int i = 0; i < n; i++) {
            int temp;
            cout << "Iveskite " << i + 1 << " pazymi is " << n << ": ";
            cin >> temp;
            A.paz.push_back(temp);
            sum += temp;
        }
        cout << "Iveskite egzamina: ";
        cin >> A.egz;
        cout << "----------------------------------------------" << endl;

        // Vidurkio skaiciavimas
        A.rez = sum * 1.0 / (n * 1.0) * 0.4 + A.egz * 0.6;

        // Medianos skaiciavimas
        A.med = mediana(A.paz) * 0.4 + A.egz * 0.6;

        grupe.push_back(A);
        A.paz.clear();

    }// galima priskirti grupej, kai turime A.rez; pushbackinam studento pavadinima
}



void outputas(const vector <Studentas>& grupe) {
    for (auto A : grupe) {
        cout << left << setw(10) << "Vardas " << left << setw(20) << "Pavarde " << left << setw(30) << "Galutinis (Vid.) " << left << setw(40) << "Galutinis (Med.) " << endl;
        cout << left << setw(10) << A.vardas << left << setw(20) << A.pavarde;
        //for (auto k : A.paz) cout << setw(3) << k;
        //cout << setw(5) << A.egz;
        cout << left << setw(30) << fixed << setprecision(2) << A.rez << left << setw(40) << fixed << setprecision(2) << A.med << endl;
    }
}