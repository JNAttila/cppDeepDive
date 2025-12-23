#include <cassert>
#include <iostream>
#include <ostream>
#include <sstream>
#include <vector>

#ifndef TRACK_INFO
#define TRACK_INFO
#endif

using namespace std;

// Lehet kell modositani az osztalyt!

class Part {
  std::string id;
  bool active = false;
public:
  Part( const std::string& id ) : id( id ) {}
  bool isActive() const { return active; }

  bool operator!() { return active = !active; }
  std::string identify() const { return std::string("(") + id + ")"; };
  
  Part& degrade() {}
  ~Part() = default;
};
//=============================

// Ez alatt ne legyen mar feladat implementacio!
#ifndef TEST_BIRO

int main() {
  { // identify
    Engine engine( 100, "E100PR5" );
    std::string engineID = engine.identify();
    assert( engineID == "Engine: 100 (E100PR5)");
  }

  { // identify
    LifeSupport ls( 1500, 4 );
    std::string lsID = ls.identify();
    assert( lsID == "LifeSupport: [4@1500]" );
  }

  { // degrade
    LifeSupport ls( 1500, 4 );
    
    ls.degrade();
    ls.degrade();

    std::string lsID = ls.identify();
    assert( lsID == "LifeSupport: [2@1500]" );
  }
  
  { // LifeSupport CTR logic
    LifeSupport ls( 1500, 4 );
    assert( true == ls.isActive() );
  }
  
  { // checklist
    Airplane ap( 4 );
    LifeSupport ls( 1500, 4 );

    ap.addPart( ls );

    std::string inv = ap.checklist();
    std::cout << inv << std::endl;
    assert( inv == "Airplane:\n0 out of 4\nLifeSupport: [4@1500]\n" );
  }

  { // operator!
    Airplane ap( 4 );
    LifeSupport ls( 1500, 4 );
    Engine e( 1500, "E11A" );
    !e;

    ap.addPart( ls );
    ap.addPart( e );

    !ap;

    std::string inv = ap.checklist();
    std::cout << inv << std::endl;
    assert( inv == "Airplane:\n1 out of 4\nLifeSupport: [4@1500]\n" );
  }
  
  { //inventory
    Airplane ap( 4 );
    LifeSupport ls( 1500, 4 );
    std::vector<std::string> requiredParts = { "LifeSupport: [6@6000]", "Sugarhajtasu szupermotor" };

    ap.addPart( ls );

    auto result = ap.inventory( requiredParts );

    assert( result.size() == 2 );
    assert( result[0] == "LifeSupport: [6@6000]" );
    assert( result[1] == "Sugarhajtasu szupermotor" );
  }

  { // copy
    Airplane ap( 4 );
    LifeSupport ls( 1500, 4 );
    Engine e( 1500, "E11A" );
    !e;

    ap.addPart( ls );
    ap.addPart( e );

    !ap;
    std::string inv;
    {
      Airplane ap2 = ap;
      inv = ap2.checklist();
    }
    std::cout << inv << std::endl;
    assert( inv == "Airplane:\n1 out of 4\nLifeSupport: [4@1500]\n" );
    inv = ap.checklist();
    assert( inv == "Airplane:\n1 out of 4\nLifeSupport: [4@1500]\n" );
  }

  { // ertekadas
    Airplane ap( 4 );
    Airplane ap2(1);
    LifeSupport ls( 1500, 4 );
    Engine e( 1500, "E11A" );
    !e;

    ap.addPart( ls );
    ap.addPart( e );

    ap2.addPart(e);

    !ap;
    std::string inv;
    {
      ap2 = ap;
      inv = ap2.checklist();
    }
    std::cout << inv << std::endl;
    assert( inv == "Airplane:\n1 out of 4\nLifeSupport: [4@1500]\n" );
    inv = ap.checklist();
    assert( inv == "Airplane:\n1 out of 4\nLifeSupport: [4@1500]\n" );
  }

  return 0;
}

#endif
