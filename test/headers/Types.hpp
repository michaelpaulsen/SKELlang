#pragma once
#include <string> 
#include "./defines.hpp" 
enum context_t {
    FOR,
    WHILE
};
struct LoopContext_t {
    std::string label;
    std::string loop_val;
    context_t type;
};
struct Var_t {
    std::string name;
    std::string value;
};
struct Command_t {
    std::string command;
    std::string name;
    std::string op;
    std::string param;
    void Print() {
        coutf("command {} var {} op {} param {}\n", command, name, op, param);
    }
};
