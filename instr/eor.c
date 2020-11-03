//
// Created by cst on 10/31/20.
//

#include "eor.h"
#include "cpu.h"

void eorxind()
{}

void eorzpg()
{}

void eorimm()
{}

void eorabs()
{
    uint8_t low = get_arg(1);
    uint8_t high = get_arg(2);
    cpu.a ^= mem.ram[high][low];

    if(!cpu.a)//Analizamos el 0 flag
        setsr(1);
    else
        unsetsr(1);

    if(cpu.a & 0b10000000)//Analizamos el negative flag
        setsr(7);
    else
        unsetsr(7);
}

void eorindy()
{}

void eorzpgx()
{}

void eorabsy()
{}

void eorabsx()
{
    uint16_t offset;
    uint8_t low = get_arg(1);
    uint8_t high = get_arg(2);
    offset = high*256+low+cpu.x;

    high=offset/256;
    low=offset%256;

    cpu.a ^=mem.ram[high][low];

    if(!cpu.a)//Analizamos el 0 flag
        setsr(1);
    else
        unsetsr(1);

    if(cpu.a & 0b10000000)//Analizamos el negative flag
        setsr(7);
    else
        unsetsr(7);
}