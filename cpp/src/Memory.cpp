//
// Created by Pedro Pinheiro on 16/02/2016.
//

#include "Memory.h"

Memory::Memory():
    forward(std::vector<int>(1)),
    back(std::vector<int>(1)),
    cursor(0)
{}

void Memory::Seek(int pos) {
    cursor += pos;
    if (cursor >= 0) {
        if (cursor >= forward.size()) {
            forward.push_back(0);
        }
    } else {
        int pos = -cursor - 1;
        if (pos >= back.size()) {
            back.push_back(0);
        }
    }
}

void Memory::Write(int val) {
    if (cursor >= 0) {
        forward[cursor] = val;
    } else {
        int pos = -cursor - 1;
        back[pos] = val;
    }
}

void Memory::Add(int n) {
    if (cursor >= 0) {
        forward[cursor] += n;
        forward[cursor] %= 256;
    } else {
        int pos = -cursor - 1;
        back[pos] += n;
        back[pos] %= 256;
    }
}

int Memory::Read() {
    if (cursor >= 0) {
        return forward[cursor];
    } else {
        int pos = -cursor - 1;
        return back[pos];
    }
}