#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

void demoFunc1() {
    vector<int> v = {1, 3, 5, 8, 9, 6};

    auto it = find_if(v.begin(), v.end(),
                      [](int x) { return x % 2 == 0; });

    if (it != v.end()) {
        cout << "The first even number is: " << *it << endl;
    }
}

bool size_bigger_then_5(const string& s) {
    return s.size() > 5;
}

void demoFunc2() {
    vector<string> words = {"apple", "lemon", "strawberry", "banana"};

    auto it = find_if(words.begin(), words.end(), size_bigger_then_5);

    cout << "The first possible word is: " << *it << endl;
}

int main() {
    demoFunc1();

    demoFunc2();

    return 0;
}
