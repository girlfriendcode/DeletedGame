//
// Created by valeria on 19.12.2020.
//

#ifndef DELETEDGAME_MYCONTAINER_H
#define DELETEDGAME_MYCONTAINER_H

#include <iostream>
#include <iterator>

template<class T>
class MyContainer {
private:
    int size;
    T *elem;
public:
    MyContainer() : size(0), elem(nullptr) {};

    MyContainer(const MyContainer &other);

    MyContainer(const std::vector<T> &other);

    MyContainer(const std::initializer_list<T> &other);

    ~MyContainer() { delete[] elem; }

    T &operator[](int n);

    const T &operator[](int n) const;

    bool operator==(const MyContainer &vec);

    bool operator!=(const MyContainer &vec) { return (*this == vec); };

    bool empty() { return (this->elem == nullptr); };

    int findElement(T &element);

    void push_back(const T &it);

    void replace(T &element, const T &other);//заменяем один предмет на другой
    void pop_back();

    void erase(int index);

    void clear();

    int getSize() const { return size; };

    T *getElem() const { return elem; };

    void resize(int new_size);
};

template<class T>
MyContainer<T>::MyContainer(const MyContainer<T> &other) {
    this->size = 0;
    if (this->elem != nullptr)
        this->elem = nullptr;
    for (int i = 0; i < other.size; i++) {
        this->push_back(other.elem[i]);
    }
}

template<class T>
MyContainer<T>::MyContainer(const std::vector<T> &other) {
    this->size = 0;
    if (this->elem != nullptr)
        this->elem = nullptr;
    for (int i = 0; i < other.size(); i++) {
        this->push_back(other[i]);
    }
}

template<class T>
MyContainer<T>::MyContainer(const std::initializer_list<T> &other) {
    this->size_ = 0;
    if (this->elem != nullptr)
        this->elem = nullptr;
    this->size = other.size();
    this->elem = new T[other.size()];
    std::copy(other.begin(), other.end(), this->elem);
}

template<class T>
void MyContainer<T>::resize(int new_size) {
    T *p = new T[new_size];
    if (this->elem != nullptr) {
        if (new_size >= size) {
            for (int i = 0, j = 0; i < this->size; i++, j++) {
                p[j] = this->elem[i];
            }
        } else {
            for (int i = 0, j = 0; j < new_size; i++, j++) {
                p[j] = this->elem[i];
            }
        }
        delete[] this->elem;
    }
    this->elem = p;
    this->size = new_size;
}

template<class T>
void MyContainer<T>::push_back(const T &it) {
    this->resize(size + 1);
    elem[size - 1] = it;
}

template<class T>
T &MyContainer<T>::operator[](int n) {
    if (n < 0 || n > size) {
        throw std::exception();
    } else
        return this->elem[n];
}

template<class T>
const T &MyContainer<T>::operator[](int n) const {
    if (n < 0 || n > size) {
        throw std::exception();
    } else
        return this->elem[n];
}

template<class T>
bool MyContainer<T>::operator==(const MyContainer &vec) {
    if (this->size == vec.size) {
        for (int i = 0; i < this->size; i++) {
            if (this->elem[i] != vec.elem[i])
                return false;
        }
        return true;
    } else return false;
}

template<class T>
int MyContainer<T>::findElement(T &element) {
    for (int i = 0; i < this->size; i++) {
        if (this->elem[i] == element) return i;
    }
    return -1;
}

template<class T>
void MyContainer<T>::clear() {
    if (this->elem != nullptr)
        delete[] this->elem;
    this->size = 0;
}

template<class T>
void MyContainer<T>::replace(T &element, const T &other) {
    if (findElement(element)) {
        this->elem[findElement(element)] = other;
    }
}

template<class T>
void MyContainer<T>::pop_back() {
    if (this->size > 0)
        resize(size - 1);
    else
        throw std::exception();
}

template<class T>
void MyContainer<T>::erase(int index) {
    if (this->size > 0 && (index < this->size && index >= 0)) {
        T *p = new T[size - 1];
        for (int i = 0, j = 0; i < this->size; i++, j++) {
            if (index == i)
                j--;
            else
                p[i] = this->elem[i];
        }
        delete[]this->elem;

        this->elem = p;
        this->size = size - 1;
    }
}


#endif //DELETEDGAME_MYCONTAINER_H
