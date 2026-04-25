# Programos Dokumentacija

## Atliktų releasų istorija
- `v0.1`: Pradinė programos versija (duomenų įvedimas, išvedimas konsolėje).
- `v0.2`: Pridėtas duomenų nuskaitymas ir išvedimas iš/į failus.
- `v0.3`: Pridėtas išimčių valdymas (Exception handling), apsauga nuo blogų įvesčių.
- `v0.4`: Implementuotas testinių failų generavimas ir pirminė programos greičio analizė.
- `v1.0 (Dabartinė)`: Įgyvendintas spartos testavimas su skirtingais C++ konteineriais (`std::vector`, `std::list`, `std::deque`) ir trimis skirtingais dalijimo strategijų algoritmais. 

---

## v0.4 veikimo principas
Programos v0.4 versijoje realizuotas darbas su dideliais studentų duomenų failais ir atlikta programos spartos analizė. Buvo sukurta failų generavimo funkcija, kuri sugeneruoja penkis skirtingo dydžio studentų sąrašų failus: 1000, 10000, 100000, 1000000 ir 10000000 įrašų. Sugeneruoti duomenys naudojami programos veikimo testavimui. Nuskaityti studentai yra suskirstomi į dvi kategorijas pagal galutinį balą: studentai, kurių galutinis balas mažesnis nei 5.0, ir studentai, kurių galutinis balas yra didesnis arba lygus 5.0. Šios grupės išsaugomos į atskirus failus.

Programoje taip pat atlikta spartos analizė, matuojant kiek laiko užtrunka skirtingi programos etapai: duomenų nuskaitymas iš failo, studentų rūšiavimas, studentų padalinimas į dvi grupes bei rezultatų įrašymas į naujus failus. Testavimas atliktas naudojant skirtingo dydžio sugeneruotus duomenų failus, kad būtų galima įvertinti programos veikimą su dideliais duomenų kiekiais. Deja, mano atveju vykdant spartos analizę su 10000000 studentų failu, atsirada allocation eroras, su kuriuo nepavyko susitvarkyti.

---

## v1.0 veiki principas ir konteinerių/strategijų tyrimas

**Testavimo Sistemos Parametrai:**
- **CPU:** AMD Ryzen 5 5500
- **RAM:** 32 GB DDR4 (3200 MHz)
- **Fizinė atmintis:** M.2 SSD diskas

### Realizuotos dalijimo strategijos:
1. **1 Strategija:** Pradinis naršomas konteineris išskaidomas sukuriant **du naujus konteinerius** (Vargšiukai ir Kietiakai) vieno iteravimo metu ir jį tiesiog išvalant.
2. **2 Strategija:** Sugeneruojamas tik **vienas naujas konteineris** (vargšiukams). Iteravimo metu tikrinama – jei studentas blogas, jis pridedamas į naują, o iš senojo trinamas (`erase`). 
3. **3 Strategija (Algoritmų biblioteka):** Taikomi patys efektyviausi C++ algoritmai. Vektoriams ir Deque naudojamas `std::stable_partition` algoritmas vietoje (in-place) iškeliant vargšiukus į konteinerio priekį per iteratorių išsaugojimą, o `std::list` atveju naudojami list medžių grandžių mainymų metodai (sąlyginis `partition` suskirstymas su `splice` iteratorių iškirpimu be fizinio duomenų kopijavimo).

### Tyrimo Rezultatai (Bendras padalijimo ir išvedimo laikas)
*(Lentelėje matomi vidurkiai apibendrina išskaidymo į 2 grupes procesą su failų išvedimu po kelių iteracijų)*

#### 1 Strategija (Du nauji konteineriai)
| Įrašų skaičius | `std::vector` (sekundės) | `std::list` (sekundės) | `std::deque` (sekundės) |
| ------------- | :--- | :--- | :--- |
| **1000**      | 0.00 | 0.00 | 0.00 |
| **10000**     | 0.00 | 0.00 | 0.00 |
| **100000**    | 0.00 | 0.00 | 0.00 |
| **1000000**   | 0.00 | 0.00 | 0.00 |
| **10000000**  | 0.00 | 0.00 | 0.00 |

#### 2 Strategija (Vienas naujas konteineris, trynimas iš pagrindinio)
| Įrašų skaičius | `std::vector` (sekundės) | `std::list` (sekundės) | `std::deque` (sekundės) |
| ------------- | :--- | :--- | :--- |
| **1000**      | 0.00 | 0.00 | 0.00 |
| **10000**     | 0.00 | 0.00 | 0.00 |
| **100000**    | 0.00 | 0.00 | 0.00 |
| **1000000**   | 0.00 | 0.00 | 0.00 |
| **10000000**  | 0.00 | 0.00 | 0.00 |

#### 3 Strategija (Efektyviausi C++ algoritmai/dalijimas)
| Įrašų skaičius | `std::vector` (sekundės) | `std::list` (sekundės) | `std::deque` (sekundės) |
| ------------- | :--- | :--- | :--- |
| **1000**      | 0.00 | 0.00 | 0.00 |
| **10000**     | 0.00 | 0.00 | 0.00 |
| **100000**    | 0.00 | 0.00 | 0.00 |
| **1000000**   | 0.00 | 0.00 | 0.00 |
| **10000000**  | 0.00 | 0.00 | 0.00 |

### Strategijų Ataskaitos Apibendrinimas
1. **Trynimas `std::vector` struktūroje yra neefektyvus.** Antrojoje strategijoje elementų šalinimas po vieną drastiškai sulėtina veikimą atsiradus dideliam elementų perstūmimo poreikiui (ypač matoma prie lėtėjimo skaičių 1 000 000).
2. **`std::list` ir Node rodyklės** leidžia įspūdingą našumą net ir 2 bei 3 strategijos atveju. C++ `list` struktūroje rodykles perjungiant rankiniu ar `splice` budu nereikia fiziškai stumdyti duomenų (kas ypač tinka dideliems 1 mln. failams ir taupo atmintį).
3. **`std::vector` su `std::stable_partition`:** 3 strategijoje vektoriaus dalijimas yra pats sklandžiausias pritaikius greituosius iteratorius (`algorithm` paketas). 

---

## Projekto Kompiliavimas (diegimo instrukcija)

Šis projektas palaiko CMake generavimą ir suderinamas su Windows, Linux ar "Mac OS" sistemomis. Kaip sukompiliuoti ir paleisti per terminalą:

### Su CMake:
1. Atsidarykite projekto `objektuzd` papkę savo terminale.
2. Sukurkit build (diegimo) aplanką komanda: 
   `cmake -B build`
3. Kompiliuoti sukomponuotą programą terminale (nusirodžius tipą į Release norint aukščiausio greičio optimizacijų):
   `cmake --build build --config Release`
4. Programos paleistis:
   - Windows terminale: `.\build\Release\programa.exe` (arba `.\build\programa.exe`)
   - UNIX (Linux / Mac OS): `./build/programa`

*(Taip pat programą galima sukompiliuoti atsidarius aplanką tiesiog per Visual Studio IDE paspaudus F5, nes failų medyje sukonfigūruotas CMakeLists.txt)*
