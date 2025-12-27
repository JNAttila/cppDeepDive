#include <iostream>

using namespace std;

class A {
    int data;

public:
    A(const int d) : data(d) {
    }

    int getData() const {
        return data;
    }

    void setData(const int d) {
        data = d;
    }

    void operator>>(A &obj) {
        const int tmp = obj.getData();
        obj.setData(this->data);
        this->data = tmp;
    }
};

void printAll(const A &obj1, const A &obj2) {
    cout << "OBJ1: " << obj1.getData() << endl;
    cout << "OBJ2: " << obj2.getData() << endl;
}

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main() {
    A a1(8);
    A a2(10);

    printAll(a1, a2);

    cout << "Operator >>" << endl;
    a1 >> a2;

    printAll(a1, a2);

    return 0;
}
