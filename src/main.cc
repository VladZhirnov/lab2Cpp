﻿#include <functions/header.h>
#include <iostream>

int main() {
    LinkedList<int> randomList1(5);
    std::cout << randomList1 << std::endl;
    LinkedList<int> abcd(randomList1);
    std::cout << abcd << std::endl;
    LinkedList<int> randomList2 = randomList1;
    Node<int> a(1);
    randomList2.push_tail(a);
    randomList2.push_tail(randomList1);
    randomList2.push_head(a);
    std::cout << randomList2 << std::endl;
    LinkedList<int> randomList3(1);
    randomList2.push_head(randomList3);
    randomList2.pop_head();
    randomList2.pop_tail();
    randomList2.delete_node(8);
    std::cout << randomList2 << std::endl;
    randomList2[1] = 10;
    std::cout << randomList2 << std::endl;


    srand(time(0)); // Инициализация случайного зерна
    int numApartments;
    std::cout << "Enter the number of apartments: ";
    std::cin >> numApartments;
    AddressBook<std::string> addressBook(numApartments); // Создаем книгу адресов с 5 квартирами (с использованием строк)
    addressBook.fill_AddressBook();               // Заполняем книгу адресов случайными жителями
    addressBook.print_AddressBook();
}