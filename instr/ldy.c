//
// Created by cst on 10/31/20.
//

#include "ldy.h"
#include "cpu.h"
void ldyimm()
{}

void ldyzpg()
{
    uint8_t offset = get_arg(1);
    cpu.y = mem.ram[0][offset];
}

void ldyzpgx()
{
    uint8_t offset = get_arg(1) + cpu.x;
    cpu.y=mem.ram[0][offset];
}

void ldyabs()
{}

void ldyabsx()
{}
