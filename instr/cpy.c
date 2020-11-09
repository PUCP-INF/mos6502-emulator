//
// Created by cst on 10/31/20.
//

#include "cpy.h"
#include "cpu.h"

void cpyimm()
{
    uint8_t value_mem = get_arg(1);
    if(value_mem >= cpu.y)//Seteamos el carry flag
        setsr(0);

    if(value_mem == cpu.y)//Seteamos el zero flag
        setsr(1);

    if((value_mem >> 7) & 0x01)
        setsr(7);
}

void cpyzpg()
{
    uint8_t offset = get_arg(1);
    uint8_t memory;
    memory = mem.ram[0][offset];
    if(memory >= cpu.y)//Seteamos el carry flag
        setsr(0);

    if(memory == cpu.y)//Seteamos el zero flag
        setsr(1);

    if((memory >> 7) & 0x01)
        setsr(7);
}

void cpyabs()
{}