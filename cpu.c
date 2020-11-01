#include "cpu.h"

void setsr(int bit)
{
    cpu.sr |= 1UL << bit;
}

void unsetsr(int bit)
{
    cpu.sr &= ~(1UL << bit);
}

int getsr(int bit)
{
    uint8_t sr = cpu.sr;
    return (sr >> bit) & 0x01;
}

uint8_t get_arg(int n)
{
    uint8_t low = cpu.pcl, high = cpu.pch;
    if ((int)low + n > 0xff) high += 1;
    low += n;
    return mem.ram[high][low];
}

void push(uint8_t value)
{
    mem.ram[1][cpu.sp] = value;
    cpu.sp -= 1;
}

uint8_t pop()
{
    uint8_t value = mem.ram[1][cpu.sp+1];
    cpu.sp += 1;
    return value;
}