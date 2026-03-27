cmake_minimum_required(VERSION 3.10)

# Projekto pavadinimas
project(ObjektinisUzdavinys)

# Nustatome C++ versiją
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Nustatome perspėjimus, kad matytumėte galimas klaidas kompiliavimo metu
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -O3")

# Nurodome kur ieškoti header failų (.h)
include_directories(header_files)

# Visi išeitiniai (source) .cpp failai išskyrus patį main
set(SOURCES 
    objekt1uzd.cpp 
    extra_cpp/duomenu_valdymas.cpp 
    extra_cpp/input.cpp 
    extra_cpp/mat_funkcijos.cpp 
    extra_cpp/menu.cpp 
    extra_cpp/output.cpp 
    extra_cpp/testavimas.cpp
)

# Sukuriame ezkekutuojamąjį (executable) failą
add_executable(programa ${SOURCES})
