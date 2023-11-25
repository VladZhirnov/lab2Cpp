#include <functions/header.h>
#include <iostream>
#include <complex>

int main() {
    LinkedList<int> randomList1(5);
    std::cout << randomList1 << std::endl;
    LinkedList<int> randomList2 = randomList1;
    std::cout << randomList2 << std::endl;
}