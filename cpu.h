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
};

struct MEM6502 {
    uint8_t **ram;
};

extern struct CPU6502 cpu;
extern struct MEM6502 mem;

void setsr(int bit);
void unsetsr(int bit);
int getsr(int bit);

#endif
