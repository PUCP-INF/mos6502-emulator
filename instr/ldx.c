//
// Created by cst on 10/31/20.
//

#include "ldx.h"
#include "cpu.h"

void ldximm()
{
    cpu.x = get_arg(1);
}

void ldxzpg()
{
    uint8_t offset = get_arg(1);
    cpu.x = mem.ram[0][offset];
}

void ldxzpgy()
{
    uint8_t offset = get_arg(1);
    cpu.x = mem.ram[0][offset] + cpu.y;
}

void ldxabs()
{
    cpu.x = mem.ram[get_arg(2)][get_arg(1)];
}

void ldxabsy()
{
    cpu.x=mem.ram[get_arg(2)][get_arg(1)]+cpu.y;
    if(!cpu.x)//Analizamos el 0 flag
        setsr(1);
    else
        unsetsr(1);

    if(cpu.x & 0b10000000)//Analizamos el negative flag
        setsr(7);
    else
        unsetsr(7);

}