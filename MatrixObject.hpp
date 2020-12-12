//
// Created by vadim on 28.11.2020.
//

#ifndef ITERPRETLINELANG_LINE_H
#define ITERPRETLINELANG_LINE_H
//редис
#include <utility>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

class Object {
    std::string value{};
    bool is_root{};
    std::vector<Object> objects;
    std::vector<unsigned> sizes;

    Object _create_matrix(int iter, std::vector<unsigned> in_sizes);
    void _calc_indices_array(std::vector<unsigned> & indarr, unsigned index);
    Object &_get_link_root(Object & obj, std::vector<unsigned> ind, int iter);
public:
    Object();
    explicit Object(std::string val);
    explicit Object(std::size_t size);
    explicit Object(const std::vector<unsigned int> & sizes);
    ~Object();

    std::size_t size() { return this->objects.size(); };
    std::size_t global_size(const Object * obj);
    Object &get_root(unsigned number);

    Object &operator[](unsigned idx);
    Object operator+(Object & obj);

    friend std::ostream &operator<<(std::ostream &out, const Object & obj);
};

#endif //ITERPRETLINELANG_LINE_H
