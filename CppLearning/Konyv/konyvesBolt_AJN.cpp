#if defined(NDEBUG)
#undef NDEBUG
#endif // defined(NDEBUG)


#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

using namespace std;


//===================== DO NOT TOUCH THE TEST NAMESPACE ============
//==================================================================
#ifndef TEST_BIRO

#define ASSERT_EQ(actual, expected, message) do {\
  if ((actual) != (expected)) {                  \
    std::cout <<  "-> " << message << std::endl; \
    std::cout << __FILE_NAME__ << ":" << __LINE__ << ": FAIL: returned: " << actual << std::endl;\
    std::cout << __FILE_NAME__ << ":" << __LINE__ << ":       expected: " << expected << std::endl; \
    assert(actual == expected);                   \
  } else { \
    std::cout << __FILE_NAME__ << ":" << __LINE__ << ": OK: " << message << std::endl; \
  } \
} while(0)

#define ASSERT_NEQ(actual, expected, message) do {\
  if ((actual) == (expected)) {                  \
    std::cout <<  "-> " << message << std::endl; \
    std::cout << __FILE_NAME__ << ":" << __LINE__ << ": FAIL: returned: " << actual << std::endl;\
    std::cout << __FILE_NAME__ << ":" << __LINE__ << ":  should not be: " << expected << std::endl; \
    assert(actual != expected);                   \
  } else { \
    std::cout << __FILE_NAME__ << ":" << __LINE__ << ": OK: " << message << std::endl; \
  } \
} while(0)


/**
 * Test namespace which should be used during the task implementations.
 * It contains jumper methods for making the testing possible.
 */
namespace test {

    /**
     * Reference implementation of max_element(2)
     * It must be used during the test otherwise no point is given.
     * Usage: test::max_element( ... ). All parameters are the same and behaves as the std one.
     *        ^^^^^^ this part is important. If it is missing, there is going to be an error.
     */
    template<class ForwardIt, class Compare>
    constexpr ForwardIt
    max_element(ForwardIt first, ForwardIt last, Compare comp) {
        return std::max_element(first, last, comp);
    }

    /**
     * Reference implementation of find_if(3)
     * It must be used during the test otherwise no point is given.
     * Usage: test::find_if( ... ). All parameters are the same and behaves as the std one.
     *        ^^^^^^ this part is important. If it is missing, there is going to be an error.
     */
    template<class InputIt, class UnaryPred>
    constexpr InputIt
    find_if(InputIt first, InputIt last, UnaryPred p) {
        return std::find_if(first, last, p);
    }

};

#endif

// ----- algorithm -----

#ifndef MY_LIBRARY

class Library {
    std::string id;
    std::vector<std::string> books;
public:
    Library(const std::string &id) : id(id) {}

    void addBook(const std::string &b) { books.push_back(b); }

    const std::string &getId() const { return id; }

    const std::vector<std::string> &getBooks() const { return books; }
};

#endif

#if defined(MY_LIBRARY) || !defined(TEST_BIRO)

bool findLibrary(const vector<Library> &lv, const string &s) {
    auto it =
        test::find_if(lv.begin(), lv.end(),
        [&s](const Library &l) { return l.getId() == s; });

    return it != lv.end();
}


#endif


class Konyv {
protected:
    string cim;
    string szerzo;
    unsigned int ev;
    unsigned int like;

public:
    [[nodiscard]] unsigned int getLike() const {
        return like;
    }

    void setLike(unsigned int l) {
        like = l;
    }

    Konyv(string cim, string szerzo, const unsigned int ev) : cim(std::move(cim)), szerzo(std::move(szerzo)), ev(ev),
                                                              like(0) {
    }

    Konyv(const Konyv &obj) : cim(obj.cim), szerzo(obj.szerzo), ev(obj.ev), like(obj.like) {
    }

    [[nodiscard]] const string &getCim() const {
        return cim;
    }

    [[nodiscard]] const string &getSzerzo() const {
        return szerzo;
    }

    [[nodiscard]] unsigned int getEv() const {
        return ev;
    }

    virtual Konyv &operator++() {
        like++;
        return *this;
    }

    explicit virtual operator string() const {
        return szerzo + ": " + cim + " (" + to_string(ev) + "), lajk: " + to_string(like);
    }

    virtual ~Konyv() = default;
};

class GyerekKonyv : public Konyv {
protected:
    unsigned int korhatar;

public:
    GyerekKonyv(const string &cim, const string &szerzo, unsigned int ev,
                unsigned int korhatar) : Konyv(cim, szerzo, ev), korhatar(korhatar) {
    }

    GyerekKonyv(const GyerekKonyv &obj) : Konyv(obj.getCim(), obj.getSzerzo(), obj.getEv()), korhatar(obj.korhatar) {
        like = obj.like;
    }

    explicit operator string() const override {
        return szerzo + ": " + cim + " (" + to_string(ev) + ", korhatar: " + to_string(korhatar) + "), lajk: " +
               to_string(like);
    }
};

class TudomanyosKonyv : public Konyv {
protected:
    string tudomanyt;

public:
    TudomanyosKonyv(const string &cim, const string &szerzo, unsigned int ev, string tudomanyt)
        : Konyv(cim, szerzo, ev), tudomanyt(std::move(tudomanyt)) {
    }

    TudomanyosKonyv(const TudomanyosKonyv &obj) : Konyv(obj.getCim(), obj.getSzerzo(), obj.getEv()),
                                                  tudomanyt(obj.tudomanyt) {
        like = obj.like;
    }

    Konyv &operator++() override {
        like += 2;
        return *this;
    }

    explicit operator std::string() const override {
        return szerzo + ": " + cim + " (" + to_string(ev) + ", " + tudomanyt + "), lajk: " + to_string(like);
    }
};

class Ekonyv : public Konyv {
protected:
    Konyv *p = nullptr;

public:
    Ekonyv() : Konyv("", "", 0) {
    }

    Ekonyv(Konyv *k) : Konyv(*k) {
        if (dynamic_cast<GyerekKonyv *>(k)) {
            p = new GyerekKonyv(*dynamic_cast<GyerekKonyv *>(k));
        } else if (dynamic_cast<TudomanyosKonyv *>(k)) {
            p = new TudomanyosKonyv(*dynamic_cast<TudomanyosKonyv *>(k));
        } else {
            p = new Konyv(*k);
        }
    }

    Ekonyv(const Ekonyv &obj) : Konyv(obj.getCim(), obj.getSzerzo(), obj.getEv()) {
        if (obj.p) {
            if (dynamic_cast<GyerekKonyv *>(obj.p)) {
                p = new GyerekKonyv(*dynamic_cast<GyerekKonyv *>(obj.p));
            } else if (dynamic_cast<TudomanyosKonyv *>(obj.p)) {
                p = new TudomanyosKonyv(*dynamic_cast<TudomanyosKonyv *>(obj.p));
            } else {
                p = new Konyv(*(obj.p));
            }
        } else {
            p = nullptr;
        }
    }

    Ekonyv &operator=(const Ekonyv &obj) {
        if (this == &obj) // Guard self assignment
            return *this;

        this->cim = obj.getCim();
        this->szerzo = obj.getSzerzo();
        this->ev = obj.getEv();

        if (obj.p) {
            if (dynamic_cast<GyerekKonyv *>(obj.p)) {
                p = new GyerekKonyv(*dynamic_cast<GyerekKonyv *>(obj.p));
            } else if (dynamic_cast<TudomanyosKonyv *>(obj.p)) {
                p = new TudomanyosKonyv(*dynamic_cast<TudomanyosKonyv *>(obj.p));
            } else {
                p = new Konyv(*(obj.p));
            }
        } else {
            p = nullptr;
        }

        return *this;
    }

    explicit operator std::string() const override {
        if (!p) {
            return "Az ekonyv ures";
        }
        return p->operator string();
    }

    Ekonyv &operator++()
    override {
        if (nullptr != p) {
            p->setLike(p->getLike() + 3);
        }
        return *this;
    }

    ~Ekonyv() override {
        delete p;
        p = nullptr;
    }
};

class Konyvespolc {
    vector<Konyv *> polc;

public:
    Konyvespolc() = default;

    Konyvespolc(const Konyvespolc &obj) {
        for (Konyv *k: obj.polc) {
            if (const auto *gyk = dynamic_cast<GyerekKonyv *>(k)) {
                polc.push_back(new GyerekKonyv(*gyk));
            } else if (const auto *tk = dynamic_cast<TudomanyosKonyv *>(k)) {
                polc.push_back(new TudomanyosKonyv(*tk));
            } else if (const auto *ek = dynamic_cast<Ekonyv *>(k)) {
                polc.push_back(new Ekonyv(*ek));
            } else {
                polc.push_back(new Konyv(*k));
            }
        }
    }

    Konyvespolc &operator<<(Konyv *obj) {
        if (obj) {
            if (const auto *gyk = dynamic_cast<GyerekKonyv *>(obj)) {
                polc.push_back(new GyerekKonyv(*gyk));
            } else if (const auto *tk = dynamic_cast<TudomanyosKonyv *>(obj)) {
                polc.push_back(new TudomanyosKonyv(*tk));
            } else if (const auto *ek = dynamic_cast<Ekonyv *>(obj)) {
                polc.push_back(new Ekonyv(*ek));
            } else {
                polc.push_back(new Konyv(*obj));
            }
        }
        return *this;
    }

    Konyvespolc &operator=(const Konyvespolc &obj) {
        if (this == &obj) // Guard self assignment
            return *this;

        for (const Konyv *k: this->polc) {
            delete k;
            k = nullptr;
        }
        this->polc.clear();

        for (Konyv *k: obj.polc) {
            if (auto *gyk = dynamic_cast<GyerekKonyv *>(k)) {
                this->polc.push_back(new GyerekKonyv(*gyk));
            } else if (auto *tk = dynamic_cast<TudomanyosKonyv *>(k)) {
                this->polc.push_back(new TudomanyosKonyv(*tk));
            } else {
                this->polc.push_back(new Konyv(*k));
            }
        }

        return *this;
    }

    Konyv *operator!() {
        if (!polc.empty()) {
            Konyv *p = polc.back();
            polc.pop_back();
            return p;
        }

        return nullptr;
    }

    Konyv * &operator[](const size_t ind) {
        if (ind >= polc.size()) {
            throw out_of_range("The given index is invalid!");
        }

        return polc[ind];
    }

    Konyvespolc &operator||(Konyvespolc &obj) {
        Konyvespolc *target, *source;

        if (obj.polc.size() > polc.size()) {
            target = &obj;
            source = this;
        } else {
            target = this;
            source = &obj;
        }

        for (Konyv *k: source->polc) {
            target->polc.push_back(k);
        }
        source->polc.clear();

        return *target;
    }

    [[nodiscard]] string getKonyvek() const {
        string result;
        for (const Konyv *p: polc) {
            result.append(p->operator std::string());
            result.append("\n");
        }
        return result;
    }

    ~Konyvespolc() {
        for (const Konyv *p: polc) {
            delete p;
            p = nullptr;
        }
        polc.clear();
    }
};

// "<szerzo>: <cim> (<kiadasi ev>), lajk: <like>"
// "<szerzo>: <cim> (<kiadasi ev>, korhatar: <korhatar>), lajk: <like>"
// "<szerzo>: <cim> (<kiadasi ev>, <tudomanyterulet>), lajk: <like>"
// "Az ekonyv ures"


#ifndef TEST_BIRO

int main() {
    // 1
    { // Konyv konstruktor, operator std::string
        std::cout << std::endl << "Konyv konstruktor, operator std::string" << std::endl;

        Konyv k("Konyv", "Iro", 2022);
        std::string result = k.operator std::string();
        ASSERT_EQ(result, "Iro: Konyv (2022), lajk: 0", "Konyv konstruktor es string konverzio");

        const Konyv k2("Konyv 3", "Iro 3", 333);
        result = k2.operator std::string();
        ASSERT_EQ(result, "Iro 3: Konyv 3 (333), lajk: 0", "Konyv konstruktor es string konverzio");
    }


    // 2
    { // Konyv konstruktor, operator std::string, operator++
        std::cout << std::endl << "Konyv konstruktor, operator std::string, operator++" << std::endl;

        Konyv k("Konyv", "Iro", 2022);
        std::string result = k.operator std::string();
        ASSERT_EQ(result, "Iro: Konyv (2022), lajk: 0", "Konyv konstruktor es string konverzio");

        ++k;
        result = k.operator std::string();
        ASSERT_EQ(result, "Iro: Konyv (2022), lajk: 1", "Konyv ++");

        ++ ++ ++k;
        result = k.operator std::string();
        ASSERT_EQ(result, "Iro: Konyv (2022), lajk: 4", "Konyv ++");
    }


    // 3
    { // GyerekKonyv oroklodes, konstruktor, operator std::string
        std::cout << std::endl << "GyerekKonyv oroklodes, konstruktor, operator std::string" << std::endl;

        GyerekKonyv gy("B&B", "Valaki", 2022, 6);
        std::string result = gy.operator std::string();
        ASSERT_EQ(result, "Valaki: B&B (2022, korhatar: 6), lajk: 0", "GyerekKonyv konstruktor es string konverzio");

        result = (++gy).operator std::string();
        ASSERT_EQ(result, "Valaki: B&B (2022, korhatar: 6), lajk: 1", "GyerekKonyv konstruktor es string konverzio");

        size_t konyvSize = sizeof(Konyv);
        size_t gyKonyvSize = sizeof(GyerekKonyv);
        ASSERT_NEQ(konyvSize, gyKonyvSize, "GyerekKonyv oroklodes");
    }


    // 4
    { // TudomanyosKonyv oroklodes, konstruktor, operator std::string, operator++
        std::cout << std::endl << "TudomanyosKonyv oroklodes, konstruktor, operator std::string" << std::endl;

        TudomanyosKonyv t("C++ alapok", "BS", 2001, "IT");
        std::string result = t.operator std::string();
        ASSERT_EQ(result, "BS: C++ alapok (2001, IT), lajk: 0", "TudomanyosKonyv konstruktor es string konverzio");

        result = (++t).operator std::string();
        ASSERT_EQ(result, "BS: C++ alapok (2001, IT), lajk: 2", "TudomanyosKonyv konstruktor es string konverzio");

        size_t konyvSize = sizeof(Konyv);
        size_t tKonyvSize = sizeof(TudomanyosKonyv);
        ASSERT_NEQ(konyvSize, tKonyvSize, "TudomanyosKonyv oroklodes");
    }


    // 5
    { // Ekonyv oroklodes, konstruktor, operator std::string
        std::cout << std::endl << "Ekonyv oroklodes, konstruktor, operator std::string" << std::endl;

        Ekonyv ures;
        std::string result = ures.operator std::string();
        ASSERT_EQ(result, "Az ekonyv ures", "Ekonyv konstruktor, operator std::string - ures");

        Konyv *k = new Konyv("Konyv", "Iro", 2022);
        Ekonyv ek(k);
        ek.operator std::string();
        result = ek.operator std::string();
        ASSERT_EQ(result, "Iro: Konyv (2022), lajk: 0", "Ekonyv konstruktor, operator std::string");

        GyerekKonyv *gy = new GyerekKonyv("B&B", "Valaki", 2022, 6);
        Ekonyv egy(gy);
        result = egy.operator std::string();
        ASSERT_EQ(result, "Valaki: B&B (2022, korhatar: 6), lajk: 0",
                  "Ekonyv konstruktor, operator std::string - GyerekKonyv");

        TudomanyosKonyv *t = new TudomanyosKonyv("C++ felso fokon", "BS", 2021, "IT");
        Ekonyv et(t);
        result = et.operator std::string();
        ASSERT_EQ(result, "BS: C++ felso fokon (2021, IT), lajk: 0",
                  "Ekonyv konstruktor, operator std::string - TudomanyosKonyv");
    }


    // 6
    { // Ekonyv oroklodes, konstruktor, operator std::string, operator++
        std::cout << std::endl << "Ekonyv oroklodes, konstruktor, operator std::string, operator++" << std::endl;

        Ekonyv ures;
        std::string result = (++ures).operator std::string();
        ASSERT_EQ(result, "Az ekonyv ures", "Ekonyv operator ++ - ures");

        Konyv *k = new Konyv("Konyv2", "Iro", 2022);
        Ekonyv ek(k);
        result = (++ek).operator std::string();
        ASSERT_EQ(result, "Iro: Konyv2 (2022), lajk: 3", "Ekonyv operator ++");

        GyerekKonyv *gy = new GyerekKonyv("B&B", "Valaki ...", 2022, 6);
        Ekonyv egy(gy);
        ++ ++egy;
        result = egy.operator std::string();
        ASSERT_EQ(result, "Valaki ...: B&B (2022, korhatar: 6), lajk: 6",
                  "Ekonyv konstruktor, operator std::string - GyerekKonyv");

        TudomanyosKonyv *t = new TudomanyosKonyv("C++ felso fokon", "B.S.", 2021, "IT");
        Ekonyv et(t);
        ++et; // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        result = (++et).operator std::string();
        ASSERT_EQ(result, "B.S.: C++ felso fokon (2021, IT), lajk: 6",
                  "Ekonyv konstruktor, operator std::string - TudomanyosKonyv");
    }

    // 7
    { // Ekonyv oroklodes, konstruktor, operator std::string, operator++, masolas (cc, ao)
        std::cout << std::endl << "Ekonyv oroklodes, konstruktor, operator std::string, operator++, masolas (cc, ao)"
                  << std::endl;
        std::string result;

        Ekonyv ures;
        {
            Ekonyv ures2(ures);
            result = (++ures2).operator std::string();
            ASSERT_EQ(result, "Az ekonyv ures", "Ekonyv masolas - ures");
        }

        Konyv *k = new Konyv("Konyv", "Iro", 2022);
        Ekonyv ek(k);
        {
            Ekonyv ek2(ek);
            result = (++ek2).operator std::string();
            ASSERT_EQ(result, "Iro: Konyv (2022), lajk: 3", "Ekonyv masolas (cc)");
        }
        result = ek.operator std::string();
        ASSERT_EQ(result, "Iro: Konyv (2022), lajk: 0", "Ekonyv masolas (cc)");

        GyerekKonyv *gy = new GyerekKonyv("B & B", "Valaki", 2022, 6);
        Ekonyv egy(gy);
        {
            Ekonyv egy2;
            egy2 = egy;
            ++egy2;
            result = (++egy2).operator std::string();
            ASSERT_EQ(result, "Valaki: B & B (2022, korhatar: 6), lajk: 6", "Ekonyv masolas (ao) - GyerekKonyv");
        }
        result = egy.operator std::string();
        ASSERT_EQ(result, "Valaki: B & B (2022, korhatar: 6), lajk: 0", "Ekonyv masolas (ao) - GyerekKonyv");

        TudomanyosKonyv *t = new TudomanyosKonyv("C++ felso fokon ...", "B.S.", 2021, "IT");
        const Ekonyv et(t);
        result = et.operator std::string();
        ASSERT_EQ(result, "B.S.: C++ felso fokon ... (2021, IT), lajk: 0", "Ekonyv masolas (ao) - TudomanyosKonyv");
        {
            Ekonyv et2;
            et2 = et;
            ++et2;
            ++et2; // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            result = et2.operator std::string();
            ASSERT_EQ(result, "B.S.: C++ felso fokon ... (2021, IT), lajk: 6", "Ekonyv masolas (ao) - TudomanyosKonyv");
        }
        result = et.operator std::string();
        ASSERT_EQ(result, "B.S.: C++ felso fokon ... (2021, IT), lajk: 0", "Ekonyv masolas (ao) - TudomanyosKonyv");
    }


    // 8
    { // Ekonyv oroklodes, konstruktor, operator std::string, operator++, masolas, Memoriaszivargas
        // lasd 7. teszt
    }


    // 9
    { // Konyvespolc, konstruktor, operator<<, getKonyvek
        std::cout << std::endl << "Konyvespolc, konstruktor, operator<<, getKonyvek" << std::endl;

        Konyv *k = new Konyv("Konyv", "Iro", 2022);
        GyerekKonyv *gy = new GyerekKonyv("B&B", "Valaki", 2022, 6);
        TudomanyosKonyv *t = new TudomanyosKonyv("C++ felso fokon", "BS", 2021, "IT");
        Ekonyv *ek = new Ekonyv(new TudomanyosKonyv("Szamitogep ...", "John von Neumann", 1933, "IT"));

        Konyvespolc p;
        p << k;
        std::string result = p.getKonyvek();
        ASSERT_EQ(result, "Iro: Konyv (2022), lajk: 0\n", "Konyvespolc, konstruktor, operator<<, getKonyvek - Konyv");

        p << gy << t << ek;
        ([](const Konyvespolc &pp) {
            std::string result = pp.getKonyvek();
            ASSERT_EQ(result,
                      "Iro: Konyv (2022), lajk: 0\nValaki: B&B (2022, korhatar: 6), lajk: 0\nBS: C++ felso fokon (2021, IT), lajk: 0\nJohn von Neumann: Szamitogep ... (1933, IT), lajk: 0\n",
                      "Konyvespolc, konstruktor, operator<<, getKonyvek");
        })(p);
    }


    // 10
    { // Konyvespolc, konstruktor, operator<<, getKonyvek, operator[]
        std::cout << std::endl << "Konyvespolc, konstruktor, operator<<, getKonyvek, operator[]" << std::endl;

        try {
            Konyv *k = new Konyv("Konyv", "Iro", 2022);
            GyerekKonyv *gy = new GyerekKonyv("B&B", "Valaki", 2022, 6);
            TudomanyosKonyv *t = new TudomanyosKonyv("C++ felso fokon", "BS", 2021, "IT");

            Konyvespolc p;
            p << k << gy << t;
            std::string result = p.getKonyvek();
            ASSERT_EQ(result,
                      "Iro: Konyv (2022), lajk: 0\nValaki: B&B (2022, korhatar: 6), lajk: 0\nBS: C++ felso fokon (2021, IT), lajk: 0\n",
                      "Konyvespolc, konstruktor, operator<<, getKonyvek");

            struct P2Test {
                void test(Konyv *&k) const {
                    delete k;
                    k = new TudomanyosKonyv("AAA", "AAA", 2021, "AAA");
                }

                void test(Konyv **k) const {
                    delete *k;
                    *k = new TudomanyosKonyv("AAA", "AAA", 2021, "AAA");
                }
            };

            P2Test p2Test;
            ASSERT_NEQ(p[0], nullptr, "Konyvespolc, operator[] - not nullptr");
            p2Test.test(p[0]);
            result = p.getKonyvek();
            ASSERT_EQ(result,
                      "AAA: AAA (2021, AAA), lajk: 0\nValaki: B&B (2022, korhatar: 6), lajk: 0\nBS: C++ felso fokon (2021, IT), lajk: 0\n",
                      "Konyvespolc, konstruktor, operator<<, getKonyvek");

            try {
                p[3];
                ASSERT_EQ(std::string("no throw"), std::string("throw"), "Konyvespolc, operator[] - tulindexeles");
            } catch (const std::out_of_range &e) {
                ASSERT_EQ(1, 1, "Konyvespolc, operator[] - tulindexeles");
            } catch (...) {
                ASSERT_EQ(std::string("no throw"), std::string("throw"), "Konyvespolc, operator[] - tulindexeles");
            }

        } catch (...) {
            ASSERT_EQ(std::string("no throw"), std::string("throw"), "Konyvespolc, operator[] - tulindexeles");
        }
    }


    // 11
    { // Konyvespolc, konstruktor, operator<<, getKonyvek, operator[], Memoriaszivargas
        // lasd 10. teszt
    }


    // 12
    { // Konyvespolc, konstruktor, operator<<, getKonyvek, operator!
        std::cout << std::endl << "Konyvespolc, konstruktor, operator<<, getKonyvek, operator!" << std::endl;

        Konyv *k = new Konyv("Konyv", "Iro", 2022);
        GyerekKonyv *gy = new GyerekKonyv("B&B", "Valaki", 2022, 6);
        TudomanyosKonyv *t = new TudomanyosKonyv("C++ felso fokon", "BS", 2021, "IT");
        Ekonyv *ek = new Ekonyv(new TudomanyosKonyv("Szamitogep ...", "John von Neumann", 1933, "IT"));

        Konyv *utolso;

        {
            Konyvespolc p;
            p << k << gy << t << ek;
            std::string result = p.getKonyvek();
            ASSERT_EQ(result,
                      "Iro: Konyv (2022), lajk: 0\nValaki: B&B (2022, korhatar: 6), lajk: 0\nBS: C++ felso fokon (2021, IT), lajk: 0\nJohn von Neumann: Szamitogep ... (1933, IT), lajk: 0\n",
                      "Konyvespolc, konstruktor, operator<<, getKonyvek, operator!");

            utolso = !p;
            result = p.getKonyvek();
            ASSERT_EQ(result,
                      "Iro: Konyv (2022), lajk: 0\nValaki: B&B (2022, korhatar: 6), lajk: 0\nBS: C++ felso fokon (2021, IT), lajk: 0\n",
                      "Konyvespolc, konstruktor, operator<<, getKonyvek, operator!");
        }
        std::string result = utolso->operator std::string();
        ASSERT_EQ(result, "John von Neumann: Szamitogep ... (1933, IT), lajk: 0",
                  "Konyvespolc, konstruktor, operator<<, getKonyvek, operator!");
        delete utolso;
    }


    // 13
    { // Konyvespolc, konstruktor, operator<<, getKonyvek, operator!

        std::cout << std::endl << "Konyvespolc, konstruktor, operator<<, getKonyvek, operator!" << std::endl;

        Konyv *k = new Konyv("Konyv", "Iro", 2022);
        GyerekKonyv *gy = new GyerekKonyv("B&B", "Valaki", 2022, 6);
        TudomanyosKonyv *t = new TudomanyosKonyv("C++ felso fokon", "BS", 2021, "IT");
        Ekonyv *ek = new Ekonyv(new TudomanyosKonyv("Szamitogep ...", "John von Neumann", 1933, "IT"));

        Konyvespolc p;
        Konyv *konyv = !p;
        ASSERT_EQ(konyv, nullptr, "Konyvespolc, operator!");

        p << k << gy << t << ek;
        std::string result = p.getKonyvek();
        ASSERT_EQ(result,
                  "Iro: Konyv (2022), lajk: 0\nValaki: B&B (2022, korhatar: 6), lajk: 0\nBS: C++ felso fokon (2021, IT), lajk: 0\nJohn von Neumann: Szamitogep ... (1933, IT), lajk: 0\n",
                  "Konyvespolc, konstruktor, operator<<, getKonyvek, operator!");

        konyv = !p;
        ASSERT_NEQ(konyv, nullptr, "Konyvespolc, konstruktor, operator<<, operator!");
        result = konyv->operator std::string();
        ASSERT_EQ(result, "John von Neumann: Szamitogep ... (1933, IT), lajk: 0",
                  "Konyvespolc, konstruktor, operator<<, operator!");
        delete konyv;

        konyv = !p;
        ASSERT_NEQ(konyv, nullptr, "Konyvespolc, konstruktor, operator<<, operator!");
        result = konyv->operator std::string();
        ASSERT_EQ(result, "BS: C++ felso fokon (2021, IT), lajk: 0", "Konyvespolc, konstruktor, operator<<, operator!");
        delete konyv;

        konyv = !p;
        ASSERT_NEQ(konyv, nullptr, "Konyvespolc, konstruktor, operator<<, operator!");
        result = konyv->operator std::string();
        ASSERT_EQ(result, "Valaki: B&B (2022, korhatar: 6), lajk: 0",
                  "Konyvespolc, konstruktor, operator<<, operator!");
        delete konyv;

        konyv = !p;
        ASSERT_NEQ(konyv, nullptr, "Konyvespolc, konstruktor, operator<<, operator!");
        result = konyv->operator std::string();
        ASSERT_EQ(result, "Iro: Konyv (2022), lajk: 0", "Konyvespolc, konstruktor, operator<<, operator!");
        delete konyv;

        konyv = !p;
        ASSERT_EQ(konyv, nullptr, "Konyvespolc, konstruktor, operator<<, operator!");
    }

    // 14
    { // Konyvespolc, konstruktor, operator<<, getKonyvek, operator||
        std::cout << std::endl << "Konyvespolc, konstruktor, operator<<, getKonyvek, operator||" << std::endl;

        Konyvespolc polc;
        Konyv *k = new Konyv("Konyv", "Iro", 2022);
        GyerekKonyv *gy = new GyerekKonyv("B&B", "Valaki", 2022, 6);
        TudomanyosKonyv *t = new TudomanyosKonyv("C++ felso fokon", "BS", 2021, "IT");

        polc << k << gy << t;

        Konyvespolc polc2;
        Konyv *k2 = new Konyv("Konyv 2", "Iro", 2022);
        GyerekKonyv *gy2 = new GyerekKonyv("B&B 14", "Valaki", 2022, 6);
        TudomanyosKonyv *t2 = new TudomanyosKonyv("C++ felso fokon", "BS", 2021, "IT");
        TudomanyosKonyv *t2b = new TudomanyosKonyv("C++ felso fokon v2", "BS", 2023, "IT");

        polc2 << k2 << gy2 << t2 << t2b;

        std::string result = (polc || polc2).getKonyvek();
        ASSERT_EQ(result,
                  "Iro: Konyv 2 (2022), lajk: 0\nValaki: B&B 14 (2022, korhatar: 6), lajk: 0\nBS: C++ felso fokon (2021, IT), lajk: 0\nBS: C++ felso fokon v2 (2023, IT), lajk: 0\nIro: Konyv (2022), lajk: 0\nValaki: B&B (2022, korhatar: 6), lajk: 0\nBS: C++ felso fokon (2021, IT), lajk: 0\n",
                  "Konyvespolc, konstruktor, operator<<, getKonyvek, operator||");

        result = polc2.getKonyvek();
        ASSERT_EQ(result,
                  "Iro: Konyv 2 (2022), lajk: 0\nValaki: B&B 14 (2022, korhatar: 6), lajk: 0\nBS: C++ felso fokon (2021, IT), lajk: 0\nBS: C++ felso fokon v2 (2023, IT), lajk: 0\nIro: Konyv (2022), lajk: 0\nValaki: B&B (2022, korhatar: 6), lajk: 0\nBS: C++ felso fokon (2021, IT), lajk: 0\n",
                  "Konyvespolc, konstruktor, operator<<, getKonyvek, operator||");

        result = polc.getKonyvek();
        ASSERT_EQ(result, "", "Konyvespolc, konstruktor, operator<<, getKonyvek, operator||");
    }


    // 15
    { // Konyvespolc, konstruktor, operator<<, getKonyvek, operator||
        std::cout << std::endl << "Konyvespolc, konstruktor, operator<<, getKonyvek, operator||" << std::endl;

        Konyvespolc polc;
        Konyv *k = new Konyv("Konyv", "Iro", 2022);
        GyerekKonyv *gy = new GyerekKonyv("B&B", "Valaki", 2022, 6);
        TudomanyosKonyv *t = new TudomanyosKonyv("C++ felso fokon", "BS", 2021, "IT");

        polc << k << gy << t;

        Konyvespolc polc2;
        Konyv *k2 = new Konyv("Konyv 2", "Iro", 2022);
        GyerekKonyv *gy2 = new GyerekKonyv("B&B 14", "Valaki", 2022, 6);
        TudomanyosKonyv *t2 = new TudomanyosKonyv("C++ felso fokon", "BS", 2021, "IT");
        TudomanyosKonyv *t2b = new TudomanyosKonyv("C++ felso fokon v2", "BS", 2023, "IT");

        polc2 << k2 << gy2 << t2 << t2b;

        std::string result = (polc || polc2).getKonyvek();
        ASSERT_EQ(result,
                  "Iro: Konyv 2 (2022), lajk: 0\nValaki: B&B 14 (2022, korhatar: 6), lajk: 0\nBS: C++ felso fokon (2021, IT), lajk: 0\nBS: C++ felso fokon v2 (2023, IT), lajk: 0\nIro: Konyv (2022), lajk: 0\nValaki: B&B (2022, korhatar: 6), lajk: 0\nBS: C++ felso fokon (2021, IT), lajk: 0\n",
                  "Konyvespolc, konstruktor, operator<<, getKonyvek, operator||");

        result = polc2.getKonyvek();
        ASSERT_EQ(result,
                  "Iro: Konyv 2 (2022), lajk: 0\nValaki: B&B 14 (2022, korhatar: 6), lajk: 0\nBS: C++ felso fokon (2021, IT), lajk: 0\nBS: C++ felso fokon v2 (2023, IT), lajk: 0\nIro: Konyv (2022), lajk: 0\nValaki: B&B (2022, korhatar: 6), lajk: 0\nBS: C++ felso fokon (2021, IT), lajk: 0\n",
                  "Konyvespolc, konstruktor, operator<<, getKonyvek, operator||");

        result = polc.getKonyvek();
        ASSERT_EQ(result, "", "Konyvespolc, konstruktor, operator<<, getKonyvek, operator||");

        Konyvespolc polc3;
        polc3 << new TudomanyosKonyv("a", "b", 1, "c");
        result = polc3.getKonyvek();
        ASSERT_EQ(result, "b: a (1, c), lajk: 0\n", "Konyvespolc, konstruktor, operator<<, getKonyvek, operator||");

        result = (polc2 || polc3).getKonyvek();
        ASSERT_EQ(result,
                  "Iro: Konyv 2 (2022), lajk: 0\nValaki: B&B 14 (2022, korhatar: 6), lajk: 0\nBS: C++ felso fokon (2021, IT), lajk: 0\nBS: C++ felso fokon v2 (2023, IT), lajk: 0\nIro: Konyv (2022), lajk: 0\nValaki: B&B (2022, korhatar: 6), lajk: 0\nBS: C++ felso fokon (2021, IT), lajk: 0\nb: a (1, c), lajk: 0\n",
                  "Konyvespolc, konstruktor, operator<<, getKonyvek, operator||");

        result = polc2.getKonyvek();
        ASSERT_EQ(result,
                  "Iro: Konyv 2 (2022), lajk: 0\nValaki: B&B 14 (2022, korhatar: 6), lajk: 0\nBS: C++ felso fokon (2021, IT), lajk: 0\nBS: C++ felso fokon v2 (2023, IT), lajk: 0\nIro: Konyv (2022), lajk: 0\nValaki: B&B (2022, korhatar: 6), lajk: 0\nBS: C++ felso fokon (2021, IT), lajk: 0\nb: a (1, c), lajk: 0\n",
                  "Konyvespolc, konstruktor, operator<<, getKonyvek, operator||");

        result = polc3.getKonyvek();
        ASSERT_EQ(result, "", "Konyvespolc, konstruktor, operator<<, getKonyvek, operator||");
    }


    // 16
    { // Konyvespolc, konstruktor, operator<<, getKonyvek, operator||, Memoriaszivargas
        // lasd 15. teszt
    }


    // 17
    { // Konyvespolc, konstruktor, operator<<, getKonyvek, masolo konstruktor
        std::cout << std::endl << "Konyvespolc, konstruktor, operator<<, getKonyvek, masolo konstruktor" << std::endl;

        Konyvespolc polc;
        Konyv *k = new Konyv("Konyv", "Iro", 2022);
        GyerekKonyv *gy = new GyerekKonyv("BBBB", "Valaki", 2022, 6);
        TudomanyosKonyv *t = new TudomanyosKonyv("C++ felso fokon", "BS", 2021, "IT");

        polc << k << gy << t;
        std::string result = polc.getKonyvek();
        ASSERT_EQ(result,
                  "Iro: Konyv (2022), lajk: 0\nValaki: BBBB (2022, korhatar: 6), lajk: 0\nBS: C++ felso fokon (2021, IT), lajk: 0\n",
                  "Konyvespolc, konstruktor, operator<<, getKonyvek");
        {
            Konyvespolc polc2(polc);
            result = polc2.getKonyvek();
            ASSERT_EQ(result,
                      "Iro: Konyv (2022), lajk: 0\nValaki: BBBB (2022, korhatar: 6), lajk: 0\nBS: C++ felso fokon (2021, IT), lajk: 0\n",
                      "Konyvespolc, konstruktor, operator<<, getKonyvek, masolo konstruktor");
        }
        result = polc.getKonyvek();
        ASSERT_EQ(result,
                  "Iro: Konyv (2022), lajk: 0\nValaki: BBBB (2022, korhatar: 6), lajk: 0\nBS: C++ felso fokon (2021, IT), lajk: 0\n",
                  "Konyvespolc, konstruktor, operator<<, getKonyvek, masolo konstruktor");
    }


    // 18
    { // Konyvespolc, konstruktor, operator<<, getKonyvek, masolo konstruktor, Memoriaszivargas
        // lasd 17. teszt
    }


    // 19
    { // Konyvespolc, konstruktor, operator<<, getKonyvek, ertekado operator
        std::cout << std::endl << "Konyvespolc, konstruktor, operator<<, getKonyvek, ertekado operator" << std::endl;

        Konyvespolc polc;
        Konyv *k = new Konyv("Konyv", "Iro", 2022);
        GyerekKonyv *gy = new GyerekKonyv("CC", "Valaki", 2022, 6);
        TudomanyosKonyv *t = new TudomanyosKonyv("C++ felso fokon", "BS", 2021, "IT");

        polc << k << gy << t;
        std::string result = polc.getKonyvek();
        ASSERT_EQ(result,
                  "Iro: Konyv (2022), lajk: 0\nValaki: CC (2022, korhatar: 6), lajk: 0\nBS: C++ felso fokon (2021, IT), lajk: 0\n",
                  "Konyvespolc, konstruktor, operator<<, getKonyvek");
        {
            Konyvespolc polc2;
            polc2 = polc;
            result = polc2.getKonyvek();
            ASSERT_EQ(result,
                      "Iro: Konyv (2022), lajk: 0\nValaki: CC (2022, korhatar: 6), lajk: 0\nBS: C++ felso fokon (2021, IT), lajk: 0\n",
                      "Konyvespolc, konstruktor, operator<<, getKonyvek, ertekado operator");
        }
        result = polc.getKonyvek();
        ASSERT_EQ(result,
                  "Iro: Konyv (2022), lajk: 0\nValaki: CC (2022, korhatar: 6), lajk: 0\nBS: C++ felso fokon (2021, IT), lajk: 0\n",
                  "Konyvespolc, konstruktor, operator<<, getKonyvek, ertekado operator");

        Konyvespolc polc3;
        ([&polc3](const Konyvespolc &k) { polc3 = k; })(polc);
        result = polc3.getKonyvek();
        ASSERT_EQ(result,
                  "Iro: Konyv (2022), lajk: 0\nValaki: CC (2022, korhatar: 6), lajk: 0\nBS: C++ felso fokon (2021, IT), lajk: 0\n",
                  "Konyvespolc, konstruktor, operator<<, getKonyvek, ertekado operator");
    }


    // 20
    { // Konyvespolc, konstruktor, getKonyvek, operator<<, ertekado operator, Memoriaszivargas
        // lasd 19. teszt
    }


    // 21
    { //findLibrary
        std::vector<Library> libs = {{"Somogyi01"},
                                     {"StefaniaKids"},
                                     {"OdesszaKvt"},
                                     {"XYZ"}};
        bool result = findLibrary({}, "no libraries at all");
        std::cout << "Kereses ures vektorban:" << result << std::endl;
        ASSERT_EQ(result, false, "Kereses ures vektorban:");
        result = findLibrary(libs, "non existent library");
        std::cout << "Kereses nem letezo konyvtarra:" << result << std::endl;
        ASSERT_EQ(result, false, "Kereses nem letezo konyvtarra:");
        result = findLibrary(libs, "OdesszaKvt");
        std::cout << "Kereses letezo konyvtarra:" << result << std::endl;
        ASSERT_EQ(result, true, "Kereses letezo konyvtarra:");

    }
/*
    // 22
    { // biggestLibrary
        std::vector<Library> libs = {{"Somogyi01"},
                                     {"StefaniaKids"},
                                     {"OdesszaKvt"},
                                     {"XYZ"}};

        unsigned result = biggestLibrary(libs);
        std::cout << "Kereses ures konyvtarakban:" << result << std::endl;
        ASSERT_EQ(result, 0, "Kereses ures konyvtarakban:");

        libs[0].addBook("b1");
        libs[0].addBook("b2");
        libs[0].addBook("b3");

        result = biggestLibrary(libs);
        std::cout << "Csak egy konyvtarban vannak konyvek (3):" << result << std::endl;
        ASSERT_EQ(result, 3, "Csak egy konyvtarban vannak konyvek (3):");

        libs[1].addBook("b1");

        result = biggestLibrary(libs);
        std::cout << "Ket konyvarban vannak konyvek (3,1):" << result << std::endl;
        ASSERT_EQ(result, 3, "Ket konyvarban vannak konyvek (3,1):");

        libs[1].addBook("b2");
        libs[1].addBook("b3");

        result = biggestLibrary(libs);
        std::cout << "Ket konyvarban vannak konyvek (3,3):" << result << std::endl;
        ASSERT_EQ(result, 3, "Ket konyvarban vannak konyvek (3,3):");

        libs[2].addBook("b1");
        libs[2].addBook("b2");
        libs[2].addBook("b3");
        libs[2].addBook("b4");

        libs[3].addBook("b1");

        result = biggestLibrary(libs);
        std::cout << "Minden konyvarban vannak konyvek (3,3,4,1):" << result << std::endl;
        ASSERT_EQ(result, 4, "Minden konyvarban vannak konyvek (3,3,4,1):");
    }
    */
}

#endif