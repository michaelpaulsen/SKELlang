#pragma once
#include <string>
bool isReg(std::string name) {
    return (name == "A" || name == "X" || name == "Y") || (name == "a" || name == "x" || name == "y");
}
