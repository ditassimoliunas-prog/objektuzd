v0.4 veikimo principas

Programos v0.4 versijoje realizuotas darbas su dideliais studentų duomenų failais ir atlikta programos spartos analizė. Buvo sukurta failų generavimo funkcija, kuri sugeneruoja penkis skirtingo dydžio studentų sąrašų failus: 1000, 10000, 100000, 1000000 ir 10000000 įrašų. Sugeneruoti duomenys naudojami programos veikimo testavimui. Nuskaityti studentai yra suskirstomi į dvi kategorijas pagal galutinį balą: studentai, kurių galutinis balas mažesnis nei 5.0, ir studentai, kurių galutinis balas yra didesnis arba lygus 5.0. Šios grupės išsaugomos į atskirus failus.

Programoje taip pat atlikta spartos analizė, matuojant kiek laiko užtrunka skirtingi programos etapai: duomenų nuskaitymas iš failo, studentų rūšiavimas, studentų padalinimas į dvi grupes bei rezultatų įrašymas į naujus failus. Testavimas atliktas naudojant skirtingo dydžio sugeneruotus duomenų failus, kad būtų galima įvertinti programos veikimą su dideliais duomenų kiekiais. Deja, mano atveju vykdant spartos analizę su 10000000 studentų failu, atsirada allocation eroras, su kuriuo nepavyko susitvarkyti.

Testavimo rezultatų nuotraukos yra pridėtos atskirame kataloge, kuris vadinasi 'nuotraukos'.
