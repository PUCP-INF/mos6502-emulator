//
// Created by cst on 10/31/20.
//

#include "and.h"
#include "cpu.h"

void andxind()
{}

void andzpg()
{}

void andimm()
{}

void andabs()
{
    uint8_t low = get_arg(1);
    uint8_t high = get_arg(2);
    cpu.a &= mem.ram[high][low];

    if(!cpu.a)//Analizamos el 0 flag
        setsr(1);
    else
        unsetsr(1);

    if(cpu.a & 0b10000000)//Analizamos el negative flag
        setsr(7);
    else
        unsetsr(7);
}

void andindy()
{}

void andzpgx()
{}

void andabsy()
{}

void andabsx()
{
    uint16_t offset;
    uint8_t low = get_arg(1);
    uint8_t high = get_arg(2);
    offset = high*256+low+cpu.x;

    high=offset/256;
    low=offset%256;

    cpu.a &=mem.ram[high][low];

    if(!cpu.a)
        setsr(1);
    else
        unsetsr(1);

    if(cpu.a & 0b10000000)
        setsr(7);
    else
        unsetsr(7);
}