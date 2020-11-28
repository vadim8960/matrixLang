//
// Created by vadim on 28.11.2020.
//

#ifndef ITERPRETLINELANG_LINE_H
#define ITERPRETLINELANG_LINE_H

#include <string>
#include <vector>
#include <fstream>

using std::string;
using std::ifstream;
using std::ofstream;

#define CELL_VALUE  0
#define CELL_MATRIX 1

struct Cell_t {
    string val;
    int type;
};

class Line {
    string path;

public:
    Line();
    Line(const string& path);

    void Add(const string& val);
    void Add(const Cell_t& val);
    Line Copy(const string& new_path);

    Cell_t operator[](int idx);
    void operator+=(const Line & l);
    void operator-=(const Line & l);

    string GetPath() {return path;};

    friend std::ostream & operator << (std::ostream & out, const Line & l);
};

#endif //ITERPRETLINELANG_LINE_H
