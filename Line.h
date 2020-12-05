//
// Created by vadim on 28.11.2020.
//

#ifndef ITERPRETLINELANG_LINE_H
#define ITERPRETLINELANG_LINE_H
//редис
#include <vector>
#include <string>
#include <iostream>

template<typename T>
class Object {
    T value;
    bool is_root;
    std::vector<Object<T>> objects;
public:
    Object();
    explicit Object(const T & val);
    explicit Object(int size);
    Object(char) = delete;
    ~Object();
};

template<typename T>
Object<T>::Object() : value(0), is_root(true) {}

template<>
Object<std::string>::Object() : is_root(true) {}

template<typename T>
Object<T>::Object(const T &val) : value(val), is_root(true) {}

template<typename T>
Object<T>::Object(int size) : is_root(false) {
    this->objects.resize(size);
}

template<typename T>
Object<T>::~Object() {
    this->objects.clear();
}


#endif //ITERPRETLINELANG_LINE_H
