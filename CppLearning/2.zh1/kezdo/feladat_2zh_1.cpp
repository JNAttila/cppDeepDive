#include <iostream>
#include <string>

#ifndef TRACK_INFO
#define TRACK_INFO
#endif

using namespace std;

class Konyvtar;

class FRElem {
protected:
  string nev;
  Konyvtar *szulo;

  FRElem(const string& nev, Konyvtar* szulo) :
    nev(nev), szulo(szulo) { }

public:
  const string& getNev() const {
    return nev;
  }

  const Konyvtar* getSzulo() const noexcept {
    return szulo;
  }

  string getTeljesUtvonal() const;
};

//IDE DOLGOZZ!!!

#ifndef TEST_BIRO

int main() {
    Konyvtar& gyoker = Konyvtar::getGyoker();
    Konyvtar& k2 = gyoker / "elso" / "masodik";
    Konyvtar& k4 = k2 / "harmadik" / "negyedik";
    gyoker / "elso 2";
    gyoker / "elso 3";

    k2 % "readme.txt";
    k4 % "feladat_2zh_1.cpp";
    k4 / "otodik";

    std::cout << "Teljes utvonal" << std::endl;
    std::cout << k2.getTeljesUtvonal() << std::endl;
    std::cout << gyoker.getTeljesUtvonal() << std::endl;

    std::cout << std::endl << "ls I." << std::endl;
    k2.ls(std::cout);

    std::cout << std::endl << "ls I." << std::endl;
    gyoker.ls(std::cout);

    std::cout << std::endl << "operator >>" << std::endl;
    Konyvtar& masodik = gyoker >> "elso" >> "masodik";
    std::cout << masodik.getNev() << std::endl;

    std::cout << std::endl << "cp" << std::endl;
    gyoker.cp(k2);
    gyoker.ls(std::cout);

    std::cout << endl << "rm I." << std::endl;
    (gyoker >> "masodik").rm();
    gyoker.ls(std::cout);

    std::cout << endl << "rm II." << std::endl;
    gyoker.rm();
    gyoker.ls(std::cout);

    return 0;
}
#endif
