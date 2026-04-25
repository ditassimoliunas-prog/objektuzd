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
- **CPU:** 12th Gen Intel(R) Core(TM) i7-1255U
- **RAM:** 16 GB DDR4 (3200 MHz)
- **Fizinė atmintis:** M.2 SSD diskas NVMe INTEL SSDPEKNU512GZ 512 GB, 3,500 MB/s nuoseklaus įrašymo greitis, 2,700 MB/s rašymo greitis

### Realizuotos dalijimo strategijos:
1. **1 Strategija:** Pradinis naršomas konteineris išskaidomas sukuriant **du naujus konteinerius** (Vargšiukai ir Kietiakai) vieno iteravimo metu ir jį tiesiog išvalant.
2. **2 Strategija:** Sugeneruojamas tik **vienas naujas konteineris** (vargšiukams). Iteravimo metu tikrinama – jei studentas blogas, jis pridedamas į naują, o iš senojo trinamas (`erase`). 
3. **3 Strategija (Algoritmų biblioteka):** Taikomi patys efektyviausi C++ algoritmai. Vektoriams ir Deque naudojamas `std::stable_partition` algoritmas vietoje (in-place) iškeliant vargšiukus į konteinerio priekį per iteratorių išsaugojimą, o `std::list` atveju naudojami list medžių grandžių mainymų metodai (sąlyginis `partition` suskirstymas su `splice` iteratorių iškirpimu be fizinio duomenų kopijavimo).

### Tyrimo Rezultatai (Bendras padalijimo ir išvedimo laikas)
*(Lentelėje matomi vidurkiai apibendrina išskaidymo į 2 grupes procesą su failų išvedimu po 3 iteracijų)*

#### 1 Strategija (Du nauji konteineriai)
| Įrašų skaičius | `std::vector` (sekundės) | `std::list` (sekundės) | `std::deque` (sekundės) |
| ------------- | :---       | :---       | :---       |
| **1000**      | 0.03144 s  | 0.02811 s  | 0.02933 s  |
| **10000**     | 0.05953 s  | 0.06255 s  | 0.07063 s  |
| **100000**    | 0.43069 s  | 0.50891 s  | 0.46287 s  |
| **1000000**   | 5.26029 s  | 6.91305 s  | 4.72546 s  |
| **10000000**  | 58.02285 s | 76.11192 s | 62.73043 s |

#### 2 Strategija (Vienas naujas konteineris, trynimas iš pagrindinio)
| Įrašų skaičius | `std::vector` (sekundės) | `std::list` (sekundės) | `std::deque` (sekundės) |
| ------------- | :---       | :---       | :---       |
| **1000**      | 0.02731 s  | 0.03697 s  | 0.02841 s  |
| **10000**     | 0.06106 s  | 0.06681 s  | 0.06397 s  |
| **100000**    | 0.43070 s  | 0.50856 s  | 0.96902 s  |
| **1000000**   | 5.35292 s  | 7.47363 s  | 5.09114 s  |
| **10000000**  | 47.09721 s | 65.26825 s | 51.76803 s |

#### 3 Strategija (Efektyviausi C++ algoritmai/dalijimas)
| Įrašų skaičius | `std::vector` (sekundės) | `std::list` (sekundės) | `std::deque` (sekundės) |
| ------------- | :---       | :---       | :---       |
| **1000**      | 0.02968 s  | 0.02713 s  | 0.02722 s  |
| **10000**     | 0.06208 s  | 0.06446 s  | 0.05305 s  |
| **100000**    | 0.55363 s  | 0.51351 s  | 0.35506 s  |
| **1000000**   | 4.78121 s  | 7.34005 s  | 3.34892 s  |
| **10000000**  | 47.28121 s | 70.32786 s | 43.79530 s |

### Strategijų Ataskaitos Apibendrinimas
Šio projekto vystymo metu programa buvo nuosekliai tobulinama nuo bazinio funkcionalumo iki pilnai išvystyto įrankio, gebančio efektyviai apdoroti didelius studentų duomenų kiekius. Įgyvendintos pagrindinės funkcijos: duomenų nuskaitymas ir išvedimas (tiek konsolėje, tiek failuose), išimčių valdymas, testinių duomenų generavimas bei išsami spartos analizė.

Galutinėje (v1.0) versijoje pagrindinis dėmesys skirtas skirtingų C++ konteinerių (std::vector, std::list, std::deque) ir duomenų skaidymo strategijų efektyvumo palyginimui. Tyrimas parodė, kad našumas stipriai priklauso ne tik nuo pasirinkto konteinerio, bet ir nuo taikomo algoritmo.

Rezultatai atskleidė, kad:

std::vector pasižymi geriausiu bendru našumu, kai vengiama dažnų trynimo operacijų ir naudojami efektyvūs algoritmai.
std::list leidžia efektyviai manipuliuoti elementais be papildomo kopijavimo, tačiau dažniausiai nusileidžia dėl prastesnio atminties panaudojimo.
std::deque veikia kaip kompromisinis variantas, tačiau ne visais atvejais lenkia kitas struktūras.

Iš testuotų strategijų efektyviausia pasirodė 3 strategija, paremta standartinės algoritmų bibliotekos sprendimais (pvz., std::stable_partition), kuri užtikrina geriausią veikimo spartą ir mastelio keitimą dirbant su dideliais duomenų kiekiais. Tuo tarpu strategijos, paremtos aktyviu elementų trynimu, ypač su std::vector, ženkliai lėtina programos veikimą.

Taip pat nustatyta, kad dirbant su itin dideliais duomenų kiekiais (pvz., 10 mln. įrašų), gali pasireikšti atminties paskirstymo problemos, todėl svarbu atsižvelgti į sistemos resursus ir optimizuoti atminties naudojimą.

Apibendrinant, optimaliausias sprendimas šiame projekte yra std::vector naudojimas kartu su 3 strategija, leidžiantis pasiekti geriausią našumo ir efektyvumo balansą.

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
