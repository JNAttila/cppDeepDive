#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>

#ifndef TRACK_INFO
#define TRACK_INFO
#endif

using namespace std;

// Lehet kell modositani az osztalyt!
class Sikidom {
    const string tipus;
public:
    Sikidom(const string& tipus) : tipus(tipus){}
    virtual unsigned kerulet() const = 0;

    string keruletToString() const {
        return "A " + tipus + " kerulete " + to_string(kerulet()) + " egyseg.";
    }
};

// IDE DOLGOZZ!!!

// Ez alatt ne legyen mar feladat implementacio!
#ifndef TEST_BIRO

int main() {
  {
    Teglalap teglalap(3, 4);
    const std::string out = teglalap.keruletToString();
    std::cout << "Teglalap: " << out << std::endl;
    assert(out == "A teglalap kerulete 14 egyseg.");
  }

  {
    Negyzet negyzet(5);
    const std::string out = negyzet.keruletToString();
    std::cout << "Negyzet: " << out << std::endl;
    assert(out == "A negyzet kerulete 20 egyseg.");
  }
  {
    Haromszog haromszog(3, 4, 5);
    const std::string out = haromszog.keruletToString();
    std::cout << "Haromszog: " << out << std::endl;
    assert(out == "A haromszog kerulete 12 egyseg.");
  }

  Rajz rajz;
  {
    const shared_ptr<Teglalap> teglalap = make_shared<Teglalap>(3, 4);
    const shared_ptr<Negyzet> negyzet = make_shared<Negyzet>(5);
    const shared_ptr<Haromszog> haromszog = make_shared<Haromszog>(3, 4, 5);

    rajz.add(*teglalap);
    rajz.add(*negyzet).add(*haromszog);
  }

  {
    std::stringstream outstream;
    rajz.dump(outstream);
    const std::string out = outstream.str();
    std::cout << "Rajz.dump(): " << std::endl << out << std::endl;
    assert(out == "A teglalap kerulete 14 egyseg.\nA negyzet kerulete 20 egyseg.\nA haromszog kerulete 12 egyseg.\n");
  }

  rajz.increase();

  {
    std::stringstream outstream;
    rajz.dump(outstream);
    const std::string out = outstream.str();
    std::cout << "Rajz.dump() after increase(): " << std::endl
              << out << std::endl;
    assert(out == "A teglalap kerulete 18 egyseg.\nA negyzet kerulete 24 egyseg.\nA haromszog kerulete 15 egyseg.\n");
  }

  {
    std::cout << "Rajz copy" << std::endl;
    std::stringstream outstream;

    Rajz copiedRajz(rajz);
    copiedRajz.dump(outstream);

    const std::string out = outstream.str();
    std::cout << "copiedRajz.dump(): " << std::endl
              << out << std::endl;
    assert(out == "A teglalap kerulete 18 egyseg.\nA negyzet kerulete 24 egyseg.\nA haromszog kerulete 15 egyseg.\n");
  }

  {
    std::cout << "Rajz assignment" << std::endl;
    std::stringstream outstream;

    Rajz assignedRajz;
    assignedRajz = rajz;
    assignedRajz.dump(outstream);

    const std::string out = outstream.str();
    std::cout << "assignedRajz.dump(): " << std::endl
              << out << std::endl;
    assert(out == "A teglalap kerulete 18 egyseg.\nA negyzet kerulete 24 egyseg.\n");

    assignedRajz.increase();

    outstream.str("");
    assignedRajz.dump(outstream);
    const std::string out2 = outstream.str();
    std::cout << "assignedRajz.dump(): " << std::endl
              << out2 << std::endl;
    assert(out2 == "A teglalap kerulete 22 egyseg.\nA negyzet kerulete 28 egyseg.\n");


    outstream.str("");
    rajz.dump(outstream);
    const std::string out3 = outstream.str();
    std::cout << "rajz.dump(): " << std::endl
              << out3 << std::endl;
    assert(out3 == "A teglalap kerulete 22 egyseg.\nA negyzet kerulete 28 egyseg.\nA haromszog kerulete 15 egyseg.\n");

  }

  return 0;
}

#endif
