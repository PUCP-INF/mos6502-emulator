//
// Created by cst on 10/31/20.
//

#include "sty.h"
#include "cpu.h"
#include <inttypes.h>

void styzpg()
{
    uint8_t offset = get_arg(1);
    mem.ram[0][offset] = cpu.y;
}

void styabs()
{
    mem.ram[get_arg(2)][get_arg(1)]=cpu.y;
}

void styzpgx()
{
    uint8_t offset = get_arg(1) + cpu.x;
    mem.ram[0][offset] = cpu.y;
}
