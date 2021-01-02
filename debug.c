#include "debug.h"
#include "cpu.h"

#ifdef __MINGW64__
#   include <ncurses/ncurses.h>
#else
#   include <ncurses.h>
#endif

void print_ram()
{
    printw("\n");
    for (int j = 0; j < 256; ++j) {
        printw("%02x ", mem.ram[0][j]);
        if ((j+1) % 16 == 0) printw("\n");
    }
    printw("\n");
}

void print_stack()
{
    printw("\nSTACK: ");
    for (int i = 255; i != cpu.sp; --i) {
        printw("%02x ", mem.ram[1][i]);
    }
    printw("\n");
}

void print_cpu()
{
    printw("\nA = %02x\t\tC Z I D B V N\nX = %02x\t\t%d %d %d %d %d %d %d\nY = %02x\n",
           cpu.a, cpu.x,
           getsr(0), getsr(1), getsr(2), getsr(3), getsr(4), getsr(6), getsr(7),
           cpu.y);
    printw("\n");
}

void info_cpu()
{
    move(0, 0);
    print_cpu();
    print_stack();
    print_ram();
    refresh();
}