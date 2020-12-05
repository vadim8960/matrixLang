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
    T value{};
    bool is_root{};
    std::vector<Object<T>> objects;
public:
    Object();
    explicit Object(const T & val);
    explicit Object(std::size_t size);
    Object(char) = delete;
    ~Object();

    std::size_t size() { return this->objects.size(); };

    Object<T> &operator[](unsigned idx);

    friend std::ostream &operator<<(std::ostream &out, const Object<T> & obj) {
        if (obj.is_root) {
            out << obj.value;
        } else {
            out << "{ ";
            for (int i = 0; i < obj.objects.size() - 1; ++i)
                out << obj.objects[i] << ", ";
            out << obj.objects[obj.objects.size() - 1];
            out << " }";
        }
        return out;
    }
};

template<typename T>
Object<T>::Object() : is_root(true) {}

template<typename T>
Object<T>::Object(const T &val) : value(val), is_root(true) {}

template<typename T>
Object<T>::Object(std::size_t size) : is_root(false) {
    this->objects.resize(size);
}

template<typename T>
Object<T> &Object<T>::operator[](unsigned int idx) {
    return this->objects.at(idx);
}
template<typename T>
Object<T>::~Object() {
    this->objects.clear();
}

template<typename T>
Object<T> create_matrix(int iter, std::vector<unsigned> sizes) {
    if (iter == 1) {
        return Object<T>(std::size_t(sizes[sizes.size() - 1]));
    }
    Object<T> tmp((std::size_t(sizes[sizes.size() - iter])));
    for (int i = 0; i < sizes[sizes.size() - iter]; ++i) {
        tmp[i] = create_matrix<T>(iter - 1, sizes);
    }
    return tmp;
}

#endif //ITERPRETLINELANG_LINE_H
