cmake_minimum_required(VERSION 4.1)
project(CppLearning)

set(CMAKE_CXX_STANDARD 26)

add_executable(CppLearning main.cpp)
add_executable(2zh1 2.zh1/kezdo/feladat_2zh_1.cpp)
add_executable(2zh2 2.zh2/kezdo/feladat_2zh_2.cpp)
add_executable(2zh3 2.zh3/kezdo/feladat_2zh_3.cpp)
add_executable(Cukortarto Cukortaro/Cukortarto.cpp)
add_executable(3zhGy 3.zhgyakorlo/kezdo/feladat_3zh_gy.cpp)
add_executable(demoProj demo_proj/operatorSwap.cpp
        demo_proj/demoFindIf.cpp)
add_executable(Konyv Konyv/feladat.cpp
        Konyv/konyvesBolt_AJN.cpp)
