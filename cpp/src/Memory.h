//
// Created by Pedro Pinheiro on 16/02/2016.
//

#ifndef BRAINFUCK_MEMORU_H
#define BRAINFUCK_MEMORU_H


#include <vector>

class Memory {
private:
    std::vector<int> forward;
    std::vector<int> back;
    long cursor;
public:
    Memory();
    void Seek(int pos);
    void Add(int val);
    void Write(int val);
    int Read();
};

#endif //BRAINFUCK_MEMORU_H
