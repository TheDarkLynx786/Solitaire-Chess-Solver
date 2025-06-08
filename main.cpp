#include <iostream>
#include "Solver.h"

int main() {

    int size;

    cout << "Enter board size: ";
    cin >> size;
    cout << endl;

    Solver solver = Solver(size);

    solver.solve();


    return 0;
}