//
// Created by cst on 10/31/20.
//

#include "ldy.h"
#include "cpu.h"

void ldyimm()
{
    uint8_t value_mem = get_arg(1);
    cpu.y=value_mem;

    if(cpu.y==0)
        setsr(1);

    if(cpu.y & 0b10000000)
        setsr(7);
}

void ldyzpg()
{}

void ldyzpgx()
{}

void ldyabs()
{}

void ldyabsx()
{}
