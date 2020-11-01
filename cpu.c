#include "cpu.h"

#include <stdio.h>

void print_ram()
{
    printf("\n");
    for (int j = 0; j < 256; ++j) {
        printf("%02x ", mem.ram[0][j]);
        if ((j+1) % 16 == 0) printf("\n");
    }
    printf("\n");
}

void print_cpu()
{
    printf("A = %02x\t\tC Z I D B V N\nX = %02x\t\t%d %d %d %d %d %d %d\nY = %02x\n",
           cpu.a, cpu.x,
           getsr(0), getsr(1), getsr(2), getsr(3), getsr(4), getsr(6), getsr(7),
           cpu.y);
    print_ram();
}

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
    cpu.sp += 1;
    mem.ram[1][cpu.sp] = cpu.sp;
}

uint8_t pop()
{
    uint8_t value = mem.ram[1][cpu.sp-1];
    cpu.sp -= 1;
    mem.ram[1][cpu.sp] = cpu.sp;
    return value;
}