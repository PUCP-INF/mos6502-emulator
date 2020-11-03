//
// Created by cst on 10/31/20.
//

#include "stx.h"
#include "cpu.h"

void stxzpg()
{
    uint8_t offset = get_arg(1);
    mem.ram[0][offset] = cpu.x;
}

void stxzpgy()
{
    uint8_t offset = get_arg(1) + cpu.y;
    mem.ram[0][offset] = cpu.x;
}

void stxabs()
{
    // little endian
    mem.ram[get_arg(2)][get_arg(1)] = cpu.x;
}
