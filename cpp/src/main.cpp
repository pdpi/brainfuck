#include <iostream>
#include "Interpreter.h"

using namespace std;


int main() {
    Parser parser;
    std::string line;
    while (std::getline(std::cin, line)) {
        parser.parse(line);
    }
    std::vector<Instruction> program = parser.end();
    Interpreter interpreter(program);
    interpreter.eval();
    return 0;
}
