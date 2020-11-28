
#include "Line.h"

Line::Line() = default;

Line::Line(const string& path) {
    this->path = path;
    ofstream out(path);
    out << "";
    out.close();
}

Line Line::Copy(const string& new_path) {
    Line retv;
    retv.path = new_path;
    string output;
    ifstream in(path);
    while (!in.eof()) {
        string tmp;
        std::getline(in, tmp);
        output += (tmp + '\n');
    }
    ofstream out(new_path);
    out << output;
    in.close();
    out.close();
    return retv;
}

void Line::Add(const string& val) {
    ofstream out(path, std::ios::app);
    out << CELL_VALUE << " " << val << '\n';
    out.close();
}

void Line::Add(const Cell_t& val) {
    ofstream out(path, std::ios::app);
    out << val.type << " " << val.val << '\n';
    out.close();
}

Cell_t Line::operator[](int idx) {
    std::vector<Cell_t> vec;
    ifstream in(path);
    while (!in.eof()) {
        Cell_t c;
        in >> c.type >> c.val;
        vec.push_back(c);
    }
    return vec.at(idx);
}

void Line::operator+=(const Line &l) {
    string output;
    ifstream in(l.path);
    while (!in.eof()) {
        string tmp;
        std::getline(in, tmp);
        output += (tmp + '\n');
    }
    ofstream out(path, std::ios::app);
    out << output;
    in.close();
    out.close();
}

void Line::operator-=(const Line &l) {
    std::vector<string> out1;
    std::vector<string> out2;
    ifstream in1(path);
    ifstream in2(l.path);
    while (!in1.eof()) {
        string tmp;
        std::getline(in1, tmp);
        out1.push_back(tmp);
    }
    while (!in2.eof()) {
        string tmp;
        std::getline(in2, tmp);
        out2.push_back(tmp);
    }
    in1.close();
    in2.close();

    std::vector<string> dest;
    for (int i = 0, j = 0; j < std::min<int>(out1.size(), out2.size()); ++i) {
        if (i % 2) {
            dest.push_back(out2[j]);
            ++j;
        } else {
            dest.push_back(out1[j]);
        }
    }

    ofstream out(path);
    for (const auto & elem : dest) {
        out << elem << '\n';
    }
    out.close();
}

std::ostream &operator<<(std::ostream &out, const Line &l) {
    std::vector<std::vector<string>> vec;
    ifstream in(l.path);
    while (!in.eof()) {
        std::vector<string> v(2);
        in >> v[0] >> v[1];
        if (v[0].empty())
            continue;
        vec.push_back(v);
    }
    if (vec.empty()) {
        out << "();";
    } else {
        out << "(";
        for (int i = 0; i < vec.size() - 1; ++i) {
            if (vec[i][0] == "0")
                out << "\"" << vec[i][1] << "\", ";
            else
                out << vec[i][1] << ", ";
        }
        if (vec[vec.size() - 1][0] == "0")
            out << "\"" << vec[vec.size() - 1][1] << "\");";
        else
            out << vec[vec.size() - 1][1] << ");";
    }
    return out;
}s