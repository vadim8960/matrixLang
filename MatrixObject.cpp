//
// Created by vadim on 11.12.2020.
//

#include "MatrixObject.hpp"

#include <utility>

Object Object::_create_matrix(int iter, std::vector<unsigned> in_sizes) {
    if (iter == 1) {
        Object obj((std::size_t(in_sizes[in_sizes.size() - 1])));
        obj.sizes.resize(iter);
        std::copy(in_sizes.end() - 1, in_sizes.end(), obj.sizes.begin());
        return obj;
    }

    Object tmp((std::size_t(in_sizes[in_sizes.size() - iter])));
    tmp.sizes.resize(iter);
    std::copy(in_sizes.end() - iter, in_sizes.end(), tmp.sizes.begin());
    for (int i = 0; i < in_sizes[in_sizes.size() - iter]; ++i) {
        tmp[i] = _create_matrix(iter - 1, in_sizes);
    }
    return tmp;
}

void Object::_calc_indices_array(std::vector<unsigned int> & indarr, unsigned index) {
    unsigned val = 0;
    for (int i = sizes.size() - 1; i >= 0; --i) {
        val = index % sizes[i];
        indarr.push_back(val);
        index = (index - val) / sizes[i];
    }
    std::reverse(indarr.begin(), indarr.end());
}

Object &Object::_get_link_root(Object &obj, std::vector<unsigned> ind, int iter) {
    if (obj.is_root)
        return obj;
    return _get_link_root(obj[ind[iter]], ind, iter + 1);
}

Object::Object() : is_root(true) {}

Object::Object(std::string val) : value(std::move(val)), is_root(true) {}

Object::Object(std::size_t size) : is_root(false) {
    this->objects.resize(size);
}

Object::Object(const std::vector<unsigned int> & sizes) {
    *this = _create_matrix(sizes.size(), sizes);
}

std::size_t Object::global_size(const Object * obj = nullptr) {
    int retv = 1;
    for (const auto & i : (obj == nullptr) ? sizes : obj->sizes) {
        retv *= i;
    }
    return std::size_t(retv);
}

Object &Object::get_root(unsigned number) {
    std::vector<unsigned> indices;
    _calc_indices_array(indices, number);
    return _get_link_root(*this, indices, 0);
}

Object &Object::operator[](unsigned int idx) {
    return this->objects.at(idx);
}

Object Object::operator+(Object &obj) {
    Object retv(*this);
    Object tmp(obj);
    int all_elem_this = static_cast<int>(global_size());
    int all_elem_obj = static_cast<int>(global_size(&obj));
    for (int i = 0; i < all_elem_this; ++i) {
        for (int j = 0; j < all_elem_obj; ++j)
            tmp.get_root(j).value = retv.get_root(i).value + obj.get_root(j).value;
        retv.get_root(i) = tmp;
    }
    return retv;
}

Object::~Object() {
    this->objects.clear();
}

std::ostream &operator<<(std::ostream &out, const Object & obj) {
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

