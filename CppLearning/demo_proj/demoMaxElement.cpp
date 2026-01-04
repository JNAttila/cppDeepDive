#include <algorithm>
#include <vector>
#include <iostream>

int main() {
    std::vector<int> v = {3, 7, 2, 9, 5};

    auto it = max_element(
        v.begin(),
        v.end(),
        [](int a, int b) {
            return a < b;   // "a kisebb mint b"
        }
    );

    if (it != v.end()) {
        std::cout << *it << "\n";  // 9
    }

    return 0;
}
