#include <iostream>
#include <random>
#include <stdexcept>
#include <string>
#include <cstdlib>
#include <ctime>
#include <list>
template <typename T>
struct Node {
private:
    T data;
    Node* next;
    Node* prev;
public:
    Node() : data(0), next(nullptr), prev(nullptr) {}
    T get_data() const;
    T& get_data();
    Node* get_next() const;
    Node* get_prev() const;
    void set_next(Node* nextNode);
    void set_prev(Node* prevNode);
    Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
};

template <typename T>
class LinkedList {
private:
    Node<T>* head;
public:
    LinkedList();
    LinkedList(const LinkedList<T>& list);
    LinkedList(int size);
    ~LinkedList();
    LinkedList<T>& operator=(const LinkedList<T>& list);
    void swap(LinkedList<T>& list);
    void push_tail(const Node<T>& element);
    void push_tail(const LinkedList<T>& list);
    void push_head(const Node<T>& element);
    void push_head(const LinkedList<T>& list);
    void pop_head();
    void pop_tail();
    void delete_node(const T& value);
    template<typename U>
    friend std::ostream& operator<<(std::ostream& stream, const LinkedList<U>& list);
    T operator[](int index) const;
    T& operator[](int index);
};

template <typename T>
T Node<T>::get_data() const {
    return data;
}

template <typename T>
T& Node<T>::get_data() {
    return data;
}

template <typename T>
Node<T>* Node<T>::get_next() const {
    return next;
}

template <typename T>
Node<T>* Node<T>::get_prev() const {
    return prev;
}

template <typename T>
void Node<T>::set_next(Node* nextNode) {
    next = nextNode;
}

template <typename T>
void Node<T>::set_prev(Node* prevNode) {
    prev = prevNode;
}

template <typename T>
LinkedList<T>::LinkedList() : head(nullptr) {}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list) {
    Node<T>* tmp1 = list.head;
    Node<T>* tmp2 = nullptr;
    head = nullptr;
    while (tmp1) {
        Node<T>* newNode = new Node<T>(tmp1->get_data());
        if (!head) {
            head = newNode;
            tmp2 = head;
        }
        else {
            tmp2->set_next(newNode);
            newNode->set_prev(tmp2);
            tmp2 = tmp2->get_next();
        }
        tmp1 = tmp1->get_next();
    }
}

template <typename T>
LinkedList<T>::LinkedList(int size) {
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_real_distribution<double> distribution(0, 100);
    head = nullptr;
    for (int i = 0; i < size; ++i) {
        T randomValue = static_cast<T>(distribution(generator));
        Node<T>* newNode = new Node<T>(randomValue);
        if (!head) {
            head = newNode;
        }
        else {
            newNode->set_next(head);
            head->set_prev(newNode);
            head = newNode;
        }
    }
}

template <typename T>
LinkedList<T>::~LinkedList() {
    Node<T>* tmp = head;
    Node<T>* next;
    while (tmp) {
        next = tmp->get_next();
        delete tmp;
        tmp = next;
    }
    head = nullptr;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& list) {
    if (*this != list) {
        LinkedList<T> copy(list);
        copy.swap(*this);
    }
    return *this;
}

template <typename T>
void LinkedList<T>::swap(LinkedList<T>& list) {
    std::swap(head, list.head);
}

template <typename T>
void LinkedList<T>::push_tail(const Node<T>& element) {
    Node<T>* newNode = new Node<T>(element.get_data());
    if (!head) {
        head = newNode;
    }
    else {
        Node<T>* tmp = head;
        while (tmp->get_next()) {
            tmp = tmp->get_next();
        }
        tmp->set_next(newNode);
        newNode->set_prev(tmp);
    }
}

template <typename T>
void LinkedList<T>::push_tail(const LinkedList<T>& list) {
    Node<T>* newListHead = list.head;
    if (!newListHead) {
        throw std::invalid_argument("Empty list!");
    }
    Node<T>* tmp = newListHead;
    while (tmp) {
        Node<T>* newEl = new Node<T>(tmp->get_data());
        if (!head) {
            head = newEl;
        }
        else {
            Node<T>* lastNode = head;
            while (lastNode->get_next()) {
                lastNode = lastNode->get_next();
            }
            lastNode->set_next(newEl);
            newEl->set_prev(lastNode);
        }
        tmp = tmp->get_next();
    }
}

template <typename T>
void LinkedList<T>::push_head(const Node<T>& element) {
    Node<T>* tmp = new Node<T>(element.get_data());
    tmp->set_next(head);
    if (head) {
        head->set_prev(tmp);
    }
    head = tmp;
}

template <typename T>
void LinkedList<T>::push_head(const LinkedList<T>& list) {
    Node<T>* ListHead = list.head;
    if (!ListHead) {
        throw std::invalid_argument("Empty list!");
    }
    while (ListHead) {
        Node<T>* newNode = new Node<T>(ListHead->get_data());
        newNode->set_next(head);
        if (head) {
            head->set_prev(newNode);
        }
        head = newNode;
        ListHead = ListHead->get_next();
    }
}

template <typename T>
void LinkedList<T>::pop_head() {
    if (!head) {
        throw std::out_of_range("List is empty!");
    }
    Node<T>* tmp = head;
    head = head->get_next();
    if (head) {
        head->set_prev(nullptr);
    }
    delete tmp;
}

template <typename T>
void LinkedList<T>::pop_tail() {
    if (!head) {
        throw std::out_of_range("List is empty!");
    }
    if (!head->get_next()) {
        delete head;
        head = nullptr;
    }
    else {
        Node<T>* tmp = head;
        while (tmp->get_next()->get_next()) {
            tmp = tmp->get_next();
        }
        delete tmp->get_next();
        tmp->set_next(nullptr);
    }
}

template <typename T>
void LinkedList<T>::delete_node(const T& value) {
    Node<T>* current = head;
    Node<T>* previous = nullptr;
    while (current) {
        if (current->get_data() == value) {
            if (previous) {
                previous->set_next(current->get_next());
                if (current->get_next()) {
                    current->get_next()->set_prev(previous);
                }
                delete current;
                current = previous->get_next();
            }
            else {
                head = current->get_next();
                if (head) {
                    head->set_prev(nullptr);
                }
                delete current;
                current = head;
            }
        }
        else {
            previous = current;
            current = current->get_next();
        }
    }
}

template <typename T>
std::ostream& operator<<(std::ostream& stream, const LinkedList<T>& list) {
    stream << "[";
    Node<T>* tmp = list.head;
    while (tmp) {
        stream << "(" << tmp->get_data() << ")";
        tmp = tmp->get_next();
        if (tmp) {
            stream << " <-> ";
        }
    }
    stream << "]";
    return stream;
}

template <typename T>
T LinkedList<T>::operator[](int index) const {
    if (index < 0) {
        throw std::out_of_range("Index is negative");
    }
    Node<T>* current = head;
    for (int i = 0; i < index; ++i) {
        current = current->get_next();
    }
    if (!current) {
        throw std::out_of_range("Index is out of bounds");
    }
    return current->get_data();
}

template <typename T>
T& LinkedList<T>::operator[](int index) {
    if (index < 0) {
        throw std::out_of_range("Index is negative");
    }
    Node<T>* current = head;
    for (int i = 0; i < index; ++i) {
        current = current->get_next();
    }
    if (!current) {
        throw std::out_of_range("Index is out of bounds");
    }
    return current->get_data();
}


const int MAX_RESIDENTS = 5;
const int MAX_APARTMENTS = 5;

class AddressBook {
private:
    std::list<std::string> apartments[MAX_APARTMENTS];
public:
    AddressBook();
    void fill_AddressBook();
    void print_AddressBook() const;
};

AddressBook::AddressBook() {
    for (int i = 0; i < MAX_APARTMENTS; ++i) {
        apartments[i] = std::list<std::string>();
    }
}

void AddressBook::fill_AddressBook() {
    std::srand(std::time(0));
    for (int i = 0; i < MAX_APARTMENTS; ++i) {
        int numResidents = std::rand() % MAX_RESIDENTS + 1;

        for (int j = 0; j < numResidents; ++j) {
            std::string name = "Resident" + std::to_string(j + 1);
            apartments[i].push_back(name);
        }
    }
}

void AddressBook::print_AddressBook() const {
    for (int i = 0; i < MAX_APARTMENTS; ++i) {
        std::cout << "Apartment " << i + 1 << ": ";
        for (const auto& resident : apartments[i]) {
            std::cout << resident << " ";
        }
        std::cout << std::endl;
    }
}

