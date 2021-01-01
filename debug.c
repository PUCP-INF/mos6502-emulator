#include "debug.h"
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
    return;
}

void print_stack()
{
    printf("\nSTACK: ");
    for (int i = 255; i != cpu.sp; --i) {
        printf("%02x ", mem.ram[1][i]);
    }
    printf("\n");
}

void print_cpu()
{
//    printf("\nOP = %02x\n", mem.ram[cpu.pch][cpu.pcl]);
    printf("\nA = %02x\t\tC Z I D B V N\nX = %02x\t\t%d %d %d %d %d %d %d\nY = %02x\n",
           cpu.a, cpu.x,
           getsr(0), getsr(1), getsr(2), getsr(3), getsr(4), getsr(6), getsr(7),
           cpu.y);
}

void info_cpu()
{
    print_cpu();
    print_stack();
    print_ram();
    fflush(stdout);
    for (int i = 0; i < 2; ++i) i += 1;
}