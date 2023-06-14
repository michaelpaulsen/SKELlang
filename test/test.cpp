#include <iostream>
#include <utility> 
#include "./headers/parser.hpp"

int main(int argc, char* argv[]) {
    std::vector<LoopContext_t> cntexts = {};
    std::vector<std::string> CompLines = {};
    std::vector<Var_t> vars = {};
    std::string out;
    if (argc < 2) {
        coutf("enter a file to compile");
        exit(-1);
    }
    std::string line;
    std::ifstream myfile(argv[1]);
    int ln =0; 
    while (getline(myfile, line))
    {
        parse(line, vars, out, cntexts, ++ln);
    }
    myfile.close();
    int addr = 0x01; 
    std::ofstream outfile; 
    outfile.open("o.out"); 
    for (const auto& t : vars) {
        outfile << fmt(".{} ${}\n", t.name, addr);
        addr += 8; 
    }
    outfile <<  out; 
    outfile.close(); 
    return 0;
}

