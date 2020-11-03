//
// Created by cst on 10/31/20.
//

#include "rol.h"
#include "cpu.h"

void rolzpg()
{}

void rola()
{}

void rolabs()
{
    uint8_t memory;
    uint8_t low = get_arg(1);
    uint8_t high = get_arg(2);
    memory = mem.ram[high][low];
    mem.ram[high][low] = (memory << 1)|(memory >> (8 - 1));//8bits-1bit

    if(getsr(7))
        setsr(0);
    else
        unsetsr(0);

    if(!cpu.a)//Analizamos el 0 flag
        setsr(1);
    else
        unsetsr(1);

    if(cpu.a & 0b10000000)//Analizamos el negative flag
        setsr(7);
    else
        unsetsr(7);
}

void rolzpgx()
{}

void rolabsx()
{
    uint16_t offset, memory;
    uint8_t low = get_arg(1);
    uint8_t high = get_arg(2);
    offset = high*256+low+cpu.x;
    high=offset/256;
    low=offset%256;
    memory = mem.ram[high][low];
    mem.ram[high][low] = (memory << 1)|(memory >> (8 - 1));//8bits-1bit

    if(getsr(7))
        setsr(0);
    else
        unsetsr(0);

    if(!cpu.a)//Analizamos el 0 flag
        setsr(1);
    else
        unsetsr(1);

    if(cpu.a & 0b10000000)//Analizamos el negative flag
        setsr(7);
    else
        unsetsr(7);
}
