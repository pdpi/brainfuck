//
// Created by Pedro Pinheiro on 15/02/2016.
//

#ifndef BRAINFUCK_INTERPRETER_H
#define BRAINFUCK_INTERPRETER_H

#include <utility>
#include <vector>
#include <string>
#include "Memory.h"

enum instructions {
    INST_NOOP = 0,
    INST_SEEK = 1,
    INST_ADD  = 2,
    INST_JMPZ = 3,
    INST_JPNZ = 4,
    INST_READ = 5,
    INST_WRITE = 6
};

class Instruction {
private:
    instructions opcode_;
    int operand_;
public:
    Instruction(instructions opcode, int operand);
    inline instructions opcode() { return opcode_; }
    inline int operand() { return operand_; }
};

class Interpreter {
private:
    Memory memory;
    std::vector<Instruction> program;
    unsigned long pc;

public:
    Interpreter(std::vector<Instruction> program);
    void step();
    void eval();
};

class Parser {
private:
    bool open;
    int pc;
    std::vector<int> stack;
    std::vector<Instruction> program;

public:
    Parser();
    void parse(std::string code);
    std::vector<Instruction> end();
};


#endif //BRAINFUCK_INTERPRETER_H
