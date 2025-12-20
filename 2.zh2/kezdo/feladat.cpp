#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>

#ifndef TRACK_INFO
#define TRACK_INFO
#endif

using namespace std;

// Lehet kell modositani az osztalyt!
class Sikidom
{
protected:
  string tipus;

public:
  Sikidom(const string &tipus) : tipus(tipus)
  {
  }
  virtual ~Sikidom() = default;
  virtual unsigned kerulet() const = 0;
  virtual void increase() = 0;
  virtual Sikidom *copy() = 0;
  string keruletToString() const
  {
    return "A " + tipus + " kerulete " + to_string(kerulet()) + " egyseg.";
  }
};

// IDE DOLGOZZ!!!
class Teglalap : public Sikidom
{
protected:
  unsigned a, b;

public:
  Teglalap(unsigned a, unsigned b) : Sikidom("teglalap"), a(a), b(b) {}

  unsigned kerulet() const override
  {
    return 2 * a + 2 * b;
  }

  void increase() override
  {
    a++;
    b++;
  }

  Sikidom *copy() override
  {
    return new TRACK_INFO Teglalap(*this);
  }
};

class Negyzet : public Teglalap
{
public:
  Negyzet(unsigned a) : Teglalap(a, a)
  {
    tipus = "negyzet";
  }

  unsigned kerulet() const override
  {
    return 4 * a;
  }

  Sikidom *copy() override
  {
    return new TRACK_INFO Negyzet(*this);
  }
};

class Haromszog : public Sikidom
{
protected:
  unsigned a, b, c;

public:
  Haromszog(unsigned a, unsigned b, unsigned c) : Sikidom("haromszog"), a(a), b(b), c(c) {}

  unsigned kerulet() const override
  {
    return a + b + c;
  }

  // Inherited via Sikidom
  void increase() override
  {
    a++;
    b++;
    c++;
  }

  Sikidom *copy() override
  {
    return new TRACK_INFO Haromszog(*this);
  }
};
class Rajz
{
  vector<Sikidom *> elemek;

public:
  Rajz() = default;

  ~Rajz()
  {
    for (Sikidom *s : elemek)
    {
      delete s;
    }
    // for (int i = 0; i < elemek.size(); i++) {
    //     delete &elemek[i];
    // }
    elemek.clear();
  }
};
// Ez alatt ne legyen mar feladat implementacio!
#ifndef TEST_BIRO

int main()
{
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
    const Sikidom *teglalap = new Teglalap(3, 4);
    const Sikidom *negyzet = new Negyzet(5);
    const Sikidom *haromszog = new Haromszog(3, 4, 5);

    rajz.add(teglalap);
    rajz.add(negyzet).add(haromszog);

    delete teglalap;
    delete negyzet;
    delete haromszog;
  }

  {
    std::stringstream outstream;
    rajz.dump(outstream);
    const std::string out = outstream.str();
    std::cout << "Rajz.dump(): " << std::endl
              << out << std::endl;
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
  }

  return 0;
}

#endif
