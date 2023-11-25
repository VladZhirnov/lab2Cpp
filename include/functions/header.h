#include <iostream>
#include <random>

template <typename T>
struct Node {
    T data;
    Node* next;

    Node(const T& value) : data(value), next(nullptr) {}
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
    template<typename U>
    friend std::ostream& operator<<(std::ostream& stream, const LinkedList<U>& list);
};

template <typename T>
LinkedList<T>::LinkedList() : head(nullptr) {}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list) {
    Node<T>* tmp1 = list.head;
    Node<T>* tmp2 = nullptr;
    head = nullptr;
    while (tmp1) {
        Node<T>* newNode = new Node<T>(tmp1->data);
        if (!head) {
            head = newNode;
            tmp2 = head;
        }
        else {
            tmp2->next = newNode;
            tmp2 = tmp2->next;
        }
        tmp1 = tmp1->next;
    }
}

template <typename T>
LinkedList<T>::LinkedList(int size) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<T> dis(0, 9);

    head = nullptr;

    for (int i = 0; i < size; ++i) {
        T randomValue = dis(gen);
        Node<T>* newNode = new Node<T>(randomValue);

        if (!head) {
            head = newNode;
        }
        else {
            newNode->next = head;
            head = newNode;
        }
    }
}

template <typename T>
LinkedList<T>::~LinkedList() {
    Node<T>* tmp = head;
    Node<T>* next;
    while (tmp) {
        next = tmp->next;
        delete tmp;
        tmp = next;
    }
    head = nullptr;
}
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& list) {
    if (!*this == list) {
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
std::ostream& operator<<(std::ostream& stream, const LinkedList<T>& list) {
    stream << "[";
    Node<T>* tmp = list.head;
    while (tmp) {
        stream << "(" << tmp->data << ")";
        tmp = tmp->next;
    }
    stream << "]";
    return stream;
}