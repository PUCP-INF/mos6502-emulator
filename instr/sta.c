//
// Created by cst on 10/31/20.
//

#include "sta.h"
#include "cpu.h"
#include <inttypes.h>

void staxind()
{}

void stazpg()
{
    uint8_t offset = get_arg(1);
    mem.ram[0][offset] = cpu.a;
}

void staabs()
{}

void staindy()
{}

void stazpgx()
{
    uint8_t offset = get_arg(1);
    mem.ram[0][offset] = cpu.a +  cpu.x;
}

void staabsy()
{
    mem.ram[get_arg(2)][get_arg(1)]+=cpu.y;
}

void staabsx()
{}