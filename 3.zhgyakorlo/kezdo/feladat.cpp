#if defined(NDEBUG)
#undef NDEBUG
#endif // defined(NDEBUG)

#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <numeric>
#include <string>
#include <sstream>
#include <vector>
#include <memory>

//===================== DO NOT TOUCH THE TEST NAMESPACE ============
//==================================================================
#ifndef TEST_BIRO
/**
 * Test namespace which should be used during the task implementations.
 * It contains jumper methods for making the testing possible.
 */
namespace test {

  /**
   * Reference implementation of accumulate(2)
   * It must be used during the test otherwise no point is given.
   * Usage: test::accumulate( ... ). All parameters are the same and behaves as the std one.
   *        ^^^^^^ this part is important. If it is missing, there is going to be an error.
   */
  template< class InputIt, class T, class BinaryOp >
  T accumulate( InputIt first, InputIt last, T init, BinaryOp op ) {
    return std::accumulate( first, last, init, op );
  }

  /**
   * Reference implementation of count_if(3)
   * It must be used during the test otherwise no point is given.
   * Usage: test::count_if( ... ). All parameters are the same and behaves as the std one.
   *        ^^^^^^ this part is important. If it is missing, there is going to be an error.
   */
  template< class InputIt, class UnaryPred >
  typename std::iterator_traits<InputIt>::difference_type
  count_if( InputIt first, InputIt last, UnaryPred p ) {
    return std::count_if(first, last, p);
  }

};
#endif

// ----- algorithm -----

#ifndef MY_CAT
class Cat {
  std::string color;
  unsigned weight;
public:
  Cat(const std::string& color, unsigned weight) : color(color), weight(weight) { }
  const std::string& getColor() const { return color; }
  unsigned getWeight() const { return weight; }
};
#endif

#if defined(MY_CAT) || !defined(TEST_BIRO)

// -----   algorithm  -----
// ----- Ide dolgozz! -----



#endif



// ----- smart pointers -----

class TVProgram {
protected:
  std::string title;
public:
  TVProgram(const std::string& title) : title(title) { }

  virtual ~TVProgram() { }

  void setTitle(const std::string& t) {
    title = t;
  }

  virtual std::string info() const {
    return "TVProgram: " + title;
  }
};

class Movie : public TVProgram {
protected:
  unsigned year;
public:
  Movie(const std::string& title, unsigned year) : TVProgram(title), year(year) { }

  std::string info() const override {
    return "Movie: " + title + " (year: " + std::to_string(year) + ")";
  }
};

class Series : public Movie {
  unsigned episodes;
public:
  Series(const std::string& title, unsigned year, unsigned episodes) : Movie(title, year), episodes(episodes) { }
  std::string info() const override {
    return "Series: " + title + " (year: " + std::to_string(year) + ", episodes: " + std::to_string(episodes) + ")";
  }
};

// ----- smart pointers -----
// -----  Ide dolgozz!  -----

// Ez alatt ne legyen mar feladat implementacio!
#ifndef TEST_BIRO

int main() {

  {
    std::cout << "countCats" << std::endl;
    std::vector<Cat> cats = { {"black", 5}, {"white", 8}, {"black", 12} };
    unsigned res = countCats(cats, "black");
    std::cout << res << std::endl;
    assert(res == 1);
    cats.push_back({ "black", 12 });
    cats.push_back({ "black", 9 });
    cats.push_back({ "black", 8 });
    cats.push_back({ "Black", 8 });
    res = countCats(cats, "black");
    std::cout << res << std::endl;
    assert(res == 3);
  }

  {
    std::cout << std::endl << "accumulateCats" << std::endl;
    std::vector<Cat> cats = { {"black", 5}, {"white", 8}, {"grey", 12} };
    std::string res = accumulateCats(cats);
    std::cout << res << std::endl;
    assert(res == "black,white,grey,");
    cats.push_back({ "WHITE", 12 });
    res = accumulateCats(cats);
    std::cout << res << std::endl;
    assert(res == "black,white,grey,WHITE,");
  }

  {
    std::cout << std::endl << "DailyPrograms: add, get #1" << std::endl;

    DailyPrograms program;
    std::shared_ptr<Movie> series = std::make_shared<Series>("CSI", 2012, 123);
    program.add(series);
    TVProgram* tvProgram = program.get(0);
    assert(tvProgram != nullptr);
    if (tvProgram) {
      std::string info = tvProgram->info();
      std::cout << info << std::endl;
      assert(info == "Series: CSI (year: 2012, episodes: 123)");
    }
    assert(program.get(1) == nullptr);
  }

  {
    std::cout << std::endl << "DailyPrograms: add, get #2" << std::endl;

    DailyPrograms program;
    std::shared_ptr<Movie> series = std::make_shared<Series>("CSI", 2012, 123);
    program.add(series);
    TVProgram* tvProgram = program.get(0);
    assert(tvProgram != nullptr);
    if (tvProgram) {
      std::string info = tvProgram->info();
      std::cout << info << std::endl;
      assert(info == "Series: CSI (year: 2012, episodes: 123)");
      tvProgram->setTitle("CSI Miami");
      info = tvProgram->info();
      std::cout << info << std::endl;
      assert(info == "Series: CSI Miami (year: 2012, episodes: 123)");
    }
  }

  {
    std::cout << std::endl << "DailyPrograms: add, get, Programs: add, get #1" << std::endl;

    std::unique_ptr<DailyPrograms> dp1 = std::make_unique<DailyPrograms>();
    std::shared_ptr<Movie> series = std::make_shared<Series>("CSI", 2012, 123);
    dp1->add(series);
    Programs pr;
    pr.add(2, std::move(dp1));

    DailyPrograms* dpp = pr.get(2);
    assert(dpp != nullptr);

    if (dpp) {
      TVProgram* tvProgram = dpp->get(0);
      assert(tvProgram != nullptr);
      if (tvProgram) {
        std::string info = tvProgram->info();
        std::cout << info << std::endl;
        assert(info == "Series: CSI (year: 2012, episodes: 123)");
      }
    }
  }

  {
    std::cout << std::endl << "DailyPrograms: add, get, Programs: add, get #2" << std::endl;

    std::unique_ptr<DailyPrograms> dp1 = std::make_unique<DailyPrograms>();
    std::shared_ptr<Movie> series = std::make_shared<Series>("CSI", 2012, 123);
    dp1->add(series);
    Programs pr;
    pr.add(2, std::move(dp1));

    DailyPrograms* dpp = pr.get(2);
    assert(dpp != nullptr);

    if (dpp) {
      TVProgram* tvProgram = dpp->get(0);
      assert(tvProgram != nullptr);
      if (tvProgram) {
        std::string info = tvProgram->info();
        std::cout << info << std::endl;
        assert(info == "Series: CSI (year: 2012, episodes: 123)");
      }
    }
  }

  {
    std::cout << std::endl << "DailyPrograms: add, get, copy, Programs: add, get" << std::endl;

    std::unique_ptr<DailyPrograms> dp1 = std::make_unique<DailyPrograms>();
    std::shared_ptr<Movie> batman = std::make_shared<Movie>("Batman", 2000);
    dp1->add(batman);
    dp1->add(std::make_shared<Series>("CSI", 2012, 123));
    dp1->add(batman);
    std::unique_ptr<DailyPrograms> dp2 = std::make_unique<DailyPrograms>(*dp1);

    Programs pr;
    pr.add(2, std::move(dp1));
    pr.add(4, std::move(dp2));

    DailyPrograms* dpp2 = pr.get(2);
    assert(dpp2 != nullptr);

    DailyPrograms* dpp4 = pr.get(4);
    assert(dpp4 != nullptr);

    if (dpp2 && dpp4) {
      dpp2->add(std::make_shared<Movie>("Robin", 2001));
      std::string str2;
      for (unsigned i = 0; dpp2->get(i); i++)
        str2 = dpp2->get(i)->info();
      std::cout << str2 << std::endl;
      assert(str2 == "Movie: Robin (year: 2001)");

      std::string str4;
      for (unsigned i = 0; dpp4->get(i); i++)
        str4 = dpp4->get(i)->info();
      std::cout << str4 << std::endl;
      assert(str4 == "Movie: Batman (year: 2000)");
    }
  }

  {
    std::cout << std::endl << "DailyPrograms: add, get, Programs: add, get(,)" << std::endl;

    std::unique_ptr<DailyPrograms> dp1 = std::make_unique<DailyPrograms>();
    std::shared_ptr<Movie> batman = std::make_shared<Movie>("Batman", 2000);
    dp1->add(batman);
    dp1->add(std::make_shared<Series>("CSI", 2012, 123));
    dp1->add(batman);

    Programs pr;
    pr.add(2, std::move(dp1));

    TVProgram* dpp2_0 = pr.get(2,0);
    assert(dpp2_0 != nullptr);

    TVProgram* dpp2_2 = pr.get(2,2);
    assert(dpp2_2 != nullptr);

    if (dpp2_0 && dpp2_2) {
      dpp2_0->setTitle("Garfield");
      std::string str2_2 = dpp2_2->info();
      std::cout << str2_2 << std::endl;
      assert(str2_2 == "Movie: Garfield (year: 2000)");
    }
  }

  {
    std::cout << std::endl << "DailyPrograms: add, get, Programs: add, get, copy constructor" << std::endl;

    std::unique_ptr<DailyPrograms> dp1 = std::make_unique<DailyPrograms>();
    std::shared_ptr<Movie> batman = std::make_shared<Movie>("Batman", 2000);
    dp1->add(batman);
    dp1->add(std::make_shared<Series>("CSI", 2012, 123));
    dp1->add(batman);

    Programs pr;
    pr.add(5, std::move(dp1));
    Programs pr2 =pr;

    DailyPrograms* dp = pr.get(5);
    assert(dp != nullptr);

    if (dp) {
      TVProgram* tvProgram = dp->get(0);
      assert(tvProgram != nullptr);
      if (tvProgram) {
        tvProgram->setTitle("Garfield");
        DailyPrograms* dp2 = pr2.get(5);
        assert(dp2 != nullptr);
        if (dp2) {
          TVProgram* tvProgram2 = dp->get(2);
          assert(tvProgram2 != nullptr);
          if (tvProgram2) {
            std::string info = tvProgram2->info();
            std::cout << info << std::endl;
            assert(info == "Movie: Garfield (year: 2000)");
          }
        }
      }
    }
  }

  {
    std::cout << std::endl << "DailyPrograms: add, get, Programs: add, get, copy constructor, memory" << std::endl;

    std::unique_ptr<DailyPrograms> dp1 = std::make_unique<DailyPrograms>();
    std::shared_ptr<Movie> batman = std::make_shared<Movie>("Batman", 2000);
    dp1->add(batman);
    dp1->add(std::make_shared<Series>("CSI", 2012, 123));
    dp1->add(batman);

    Programs pr;
    pr.add(5, std::move(dp1));
    Programs pr2 =pr;

    DailyPrograms* dp = pr.get(5);
    assert(dp != nullptr);

    if (dp) {
      TVProgram* tvProgram = dp->get(0);
      assert(tvProgram != nullptr);
      if (tvProgram) {
        tvProgram->setTitle("Garfield");
        DailyPrograms* dp2 = pr2.get(5);
        assert(dp2 != nullptr);
        if (dp2) {
          TVProgram* tvProgram2 = dp->get(2);
          assert(tvProgram2 != nullptr);

          std::string info = tvProgram2->info();
          std::cout << info << std::endl;
          assert(info == "Movie: Garfield (year: 2000)");

          batman->setTitle("Ubul");
          info = tvProgram2->info();
          std::cout << info << std::endl;
          assert(info == "Movie: Ubul (year: 2000)");
        }
      }
    }
  }

}
#endif
