#ifndef MOS6502_CPU_H
#define MOS6502_CPU_H

#include <inttypes.h>

struct CPU6502 {
    uint8_t a;
    uint8_t x;
    uint8_t y;

    uint8_t pch;
    uint8_t pcl;

    uint8_t sp;
    uint8_t sr;

    uint8_t pcu;
};

struct MEM6502 {
    uint8_t **ram;
};

extern struct CPU6502 cpu;
extern struct MEM6502 mem;

void setsr(int bit);
void unsetsr(int bit);
int getsr(int bit);
uint8_t get_arg(int n);

void push(uint8_t value);
uint8_t pop();

#endif
