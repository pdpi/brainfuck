//
// Created by Pedro Pinheiro on 15/02/2016.
//

#include <iostream>
#include "Interpreter.h"

using namespace std;

Instruction::Instruction(instructions opcode, int operand):
    opcode_(opcode),
    operand_(operand)
{ }
Interpreter::Interpreter(std::vector<Instruction> program):
    memory(Memory()),
    program(program),
    pc(0)
{}

void Interpreter::step() {
    Instruction inst = program[pc];
    switch(inst.opcode()) {
        case instructions::INST_ADD:
            memory.Add(inst.operand());
            pc += 1;
            break;
        case instructions::INST_JPNZ:
            if(memory.Read() != 0) {
                pc = inst.operand();
            } else {
                pc += 1;
            }
            break;
        case instructions::INST_JMPZ:
            if(memory.Read() == 0) {
                pc = inst.operand();
            } else {
                pc += 1;
            }
            break;
        case instructions::INST_SEEK:
            memory.Seek(inst.operand());
            pc += 1;
            break;
        case instructions::INST_READ:
            int val;
            cin >> val;
            memory.Write(val);
            pc += 1;
            break;
        case instructions::INST_WRITE:
            cout << (char) memory.Read();
            pc += 1;
            break;
        default:
            break;
    }
}

void Interpreter::eval() {
    while(pc < program.size()) step();
}
Parser::Parser():
  open(true),
  pc(0),
  stack(vector<int>()),
  program(vector<Instruction>())
{ }

void Parser::parse(std::string code) {
    if (!open) { return; }
    string::iterator it;
    for (it = code.begin(); it < code.end(); it++) {
        instructions op;
        int val;
        switch(*it) {
            case '[':
                stack.push_back(pc);
                // We'll set it to NOOP but will fix it when the matching ']' is found
                val = 0;
                op = instructions::INST_NOOP;
                break;
            case ']':
                val = stack.back();
                stack.pop_back();
                program[val] = Instruction(instructions::INST_JMPZ, pc + 1);
                op = instructions::INST_JPNZ;
                break;
            case '>':
                val = 1;
                op = instructions::INST_SEEK;
                break;
            case '<':
                val = -1;
                op = instructions::INST_SEEK;
                break;
            case '+':
                val = 1;
                op = instructions::INST_ADD;
                break;
            case '-':
                val = -1;
                op = instructions::INST_ADD;
                break;
            case ',':
                val = 0;
                op = instructions::INST_READ;
                break;
            case '.':
                val = 0;
                op = instructions::INST_WRITE;
                break;
            default:
                continue;
        }
        pc += 1;
        program.push_back(Instruction(op, val));
    }
}

std::vector<Instruction> Parser::end() {
    open = false;
    return program;
}
