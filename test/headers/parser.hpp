#pragma once
#include "./Types.hpp" 
#include <string>
#include <vector>
#include "defines.hpp"
#include "lexer.hpp"
#include "Functions.hpp"
void parse(std::string line, std::vector<Var_t>& vars, std::string& cmpl, std::vector<LoopContext_t>& cnxt, int ln) {
    static int for_count = 0;
    static int while_count = 0;
    auto command = Lex(line, ln);
    FOPEN(parseDB, "parse.log");
    if (command.command == "var") {
        if (isReg(command.name)) {
            cmpl += (fmt("ld{} ${}\n", command.name, command.param));
        }
        else {
            if (isReg(command.param)) {
            }
            else {
                bool isVar = false;
                for (const auto& t : vars) {
                    isVar = (t.name == command.name);
                }
                if(!isVar){ 
                    vars.push_back({ command.name, command.param });
                }
                cmpl += (fmt("pha\n"));

                cmpl += (fmt("lda ${}\n", command.param));

                cmpl += fmt("sta .{}\n",command.name);
                cmpl += "pla\n";
            }
        }
        return;
    }
    if (isReg(command.command)) {
        if (command.op == "++") {
            cmpl += (fmt("in{}\n", command.command));
        }
        if (command.op == "--") {
            cmpl += (fmt("de{}\n", command.command));
        }
        return;

    }
        if (command.command == "for") {
        auto loopName = fmt("for_{}", ++for_count);
        cmpl += fmt("#start of header for for loop : {}\n", loopName);
        cmpl += "pha\n";
        cmpl += "txa\n";
        cmpl += fmt("ldx ${}\n", command.param);
        cmpl += fmt(":{}", loopName);
        cmpl += fmt("#end of header for for loop : ${}", loopName);
        cnxt.push_back({ loopName, command.op, FOR });
    }
    if (command.command == "while") {
        auto loopName = fmt("while_{}", ++while_count);
        cmpl += (fmt("#start of header for while loop : {}\n", loopName));
        cmpl += ("pha\n");
        cmpl += ("txa\n");
        cmpl += (fmt("ldx ${}\n", command.param));
        cmpl += (fmt(":{}\n", loopName));
        cmpl += (fmt("#end of header for for loop : ${}\n", loopName));
        cnxt.push_back({ loopName, command.op, WHILE });
    }
    if (command.command == "end") {
        if (cnxt.empty()) {
            parseDB << fmt("ERROR END WITH NO LOOP (around line {})", ln);
            std::cout << "parse failed see parse.log for more info\n";
            exit(-1);
            return;
        }
        LoopContext_t context = cnxt.back();
        unsigned long startline = __LINE__;
        cmpl += fmt("#start of footer for for loop : {}\n", context.label);
        cmpl += fmt("cmx ${}\n", context.loop_val);
        if (context.type == FOR) {
            cmpl += ("inx\n");
        }
        cmpl += fmt("jne :{}\n", context.label);
        cmpl += fmt("tax\n", context.loop_val, context.label);
        cmpl += fmt("pla\n", context.loop_val, context.label);
        cnxt.pop_back();
        return;
    }
    parseDB << fmt("parsing line {} ({}) as a raw line\n", line, ln);
    cmpl += fmt("{}\n", line);
    //command.Print();
}