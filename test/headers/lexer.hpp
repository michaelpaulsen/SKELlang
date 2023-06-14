#pragma once
#include "./Types.hpp"
#include <regex>

Command_t Lex(std::string line, int ln) {
    static bool init = false;
    FOPEN(lexer, "lexer.log");
    if (!init) {
        lexer << fmt("--lexer--");
        init = true;
    }
    static std::regex rgex = std::regex("^([A-z]+)\\s*([A-z1-9]*)\\s*([=])*\\s*([\\d ]*)\\s*([+-:]*)\\s*", std::regex_constants::ECMAScript);
    std::smatch res;
    std::string remaining = line;
    std::regex_search(remaining, res, rgex);
    Command_t ret;
    auto c = res.str(1);
    ret.command = c;

    if (c == "var") {
        ret.name = res.str(2);
        ret.param = res.str(4);
        return ret;
    }
    if (res.str(5) == "++" || res.str(5) == "--") {
        ret.command = res.str(5);
        ret.name = c;
        return ret;
    }
    if (c == "for") {
        lexer << "for loop reached\n";
        lexer << fmt("1 {} 2 {} 3 {} ", res.str(1), res.str(2), res.str(3));
        lexer << fmt("4 {} 5 {} 6 {}\n", res.str(4), res.str(5), res.str(6));
        lexer << fmt("line : {}\n", line);

        ret.op = res.str(4);
        ret.param = res.str(2);
        return ret;
    }
    if (c == "while") {
        lexer << "while loop reached\n";
        lexer << fmt("1 {} 2 {} 3 {} 4 {} 5 {} 6 {}\n", res.str(1), res.str(2), res.str(3), res.str(4), res.str(5), res.str(6));
        lexer << fmt("line : {}\n", line);
        ret.op = res.str(2);
        return ret;
    }
    if (c == "end")    return ret;

    if (c == "free") {
        lexer << fmt("NOTICE FREE IS INGOREd {}\n", ln);
        return {};
    }
    if (true) {}

    lexer << fmt("1 {} 2 {} 3 {} 4 {} 5 {} 6 {}\n", res.str(1), res.str(2), res.str(3), res.str(4), res.str(5), res.str(6));
    lexer << fmt("faild to lex {} \n error on line line {}", c, ln);
    FCLOSE(lexer);
    return {};
}
