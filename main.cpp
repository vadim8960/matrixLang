
#include <iostream>
#include "Line.h"

int find_by_name(std::vector<Line> data_vector, const string& name) {
    for (int i = 0; i < data_vector.size(); ++i) {
        if (data_vector[i].GetPath() == name)
            return i;
    }
    return -1;
}

std::vector<string> split_string(string str) {
    string del = " ";
    size_t pos = 0;
    std::string token;
    std::vector<string> retv;
    while ((pos = str.find(del)) != std::string::npos) {
        token = str.substr(0, pos);
        retv.push_back(token);
        str.erase(0, pos + del.length());
    }
    retv.push_back(str);
    return retv;
}

int main() {
    std::vector<Line> data_vector;
    bool end_flag = true;
    string cmd;
    while (end_flag) {
        std::cout << ">>> ";
        std::getline(std::cin, cmd);
        auto parsed_cmd = split_string(cmd);
        if (parsed_cmd[0] == "print") {
            int idx = find_by_name(data_vector, parsed_cmd[1]);
            if (idx == -1) {
                std::cout << "Variable" << parsed_cmd[1] << " not found!\n";
                continue;
            }
            std::cout << data_vector[idx] << std::endl;
            continue;
        }
        if (parsed_cmd[0] == "exit") {
            end_flag = false;
            continue;
        }
        if (parsed_cmd.size() == 1) {
            data_vector.push_back(Line(parsed_cmd[0]));
            continue;
        }
        if (parsed_cmd[1] == "add") {
            int idx1 = find_by_name(data_vector, parsed_cmd[0]);
            int idx2 = find_by_name(data_vector, parsed_cmd[2]);
            if (idx1 == -1) {
                std::cout << "Variable \"" << parsed_cmd[0] << "\" not found!\n";
                continue;
            }
            if (idx2 == -1) {
                data_vector[idx1].Add(parsed_cmd[2]);
            } else {
                Cell_t tmp_cell = {
                        .val = data_vector[idx2].GetPath(),
                        .type = CELL_MATRIX
                };
                data_vector[idx1].Add(tmp_cell);
            }
            continue;
        }
        if (parsed_cmd[1] == "+=") {
            int idx1 = find_by_name(data_vector, parsed_cmd[0]);
            int idx2 = find_by_name(data_vector, parsed_cmd[2]);
            if (idx1 == -1) {
                std::cout << "Variable \"" << parsed_cmd[0] << "\" not found!\n";
                continue;
            }
            if (idx2 == -1) {
                std::cout << "Variable \"" << parsed_cmd[2] << "\" not found!\n";
                continue;
            }
            data_vector[idx1] += data_vector[idx2];
            continue;
        }
        if (parsed_cmd[1] == "-=") {
            int idx1 = find_by_name(data_vector, parsed_cmd[0]);
            int idx2 = find_by_name(data_vector, parsed_cmd[2]);
            if (idx1 == -1) {
                std::cout << "Variable \"" << parsed_cmd[0] << "\" not found!\n";
                continue;
            }
            if (idx2 == -1) {
                std::cout << "Variable \"" << parsed_cmd[2] << "\" not found!\n";
                continue;
            }
            data_vector[idx1] -= data_vector[idx2];
            continue;
        }
        if (parsed_cmd[1] == "=") {
            int idx1 = find_by_name(data_vector, parsed_cmd[0]);
            int idx2 = find_by_name(data_vector, parsed_cmd[2]);
            if (idx1 == -1) {
                std::cout << "Variable \"" << parsed_cmd[0] << "\" not found!\n";
                continue;
            }
            if (idx2 == -1) {
                std::cout << "Variable \"" << parsed_cmd[2] << "\" not found!\n";
                continue;
            }
            data_vector[idx1] = data_vector[idx2].Copy(parsed_cmd[0]);
            continue;
        }
        std::cout << "Unknown command!\n";
    }
    return 0;
}
