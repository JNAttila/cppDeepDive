#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

void demoFunc1() {
    vector<int> v = {1, 3, 5, 8, 9, 6};

    auto it = find_if(v.begin(), v.end(),
                      [](int x) { return x % 2 == 0; });

    if (it != v.end()) {
        cout << "Demo_1 - the first even number is: " << *it << endl;
    }
}

bool size_bigger_then_5(const string &s) {
    return s.size() > 5;
}

void demoFunc2() {
    vector<string> words = {"apple", "lemon", "strawberry", "banana"};

    auto it = find_if(words.begin(), words.end(), size_bigger_then_5);

    cout << "Demo_2 - the first possible word is: " << *it << endl;
}

void demoFunc3() {
    int arr[] = {2, 4, 7, 10};

    auto it = find_if(std::begin(arr), std::end(arr),
                      [](int x) { return x > 5; });

    cout << "Demo_3 - the result is: " << *it << endl;
}

void demoFunc4(int param) {
    int arr[] = {1, 4, 6, 9, 7};

    auto it = find_if(std::begin(arr), std::end(arr),
                      [param](int x) { return x > param; });

    cout << "Demo_4 - the result is: " << *it << endl;
}

int main() {
    demoFunc1();

    demoFunc2();

    demoFunc3();

    demoFunc4(6);

    return 0;
}
