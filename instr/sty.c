//
// Created by cst on 10/31/20.
//

#include "sty.h"
#include "cpu.h"

void styzpg()
{
    uint8_t offset = get_arg(1);
    mem.ram[0][offset] = cpu.y;
}

void styabs()
{
    //guardamos el el valor del registro y en la memoria ram
    mem.ram[get_arg(1)][get_arg(2)]=cpu.y;
}

void styzpgx()
{
    uint8_t offset = get_arg(1) + cpu.x;
    mem.ram[0][offset] = cpu.y;
}
