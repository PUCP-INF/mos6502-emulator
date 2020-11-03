//
// Created by cst on 10/31/20.
//

#include "eor.h"
#include "cpu.h"

void eorxind()
{
    uint8_t dm=get_arg(1)+cpu.x;
    uint16_t high=mem.ram[0][dm+1];
    uint16_t low=mem.ram[0][dm];
    cpu.a ^=mem.ram[high][low];

    if(!cpu.a)
        setsr(1);
    else
        unsetsr(1);

    if(cpu.a &0b10000000)
        setsr(7);
    else
        unsetsr(7);
}

void eorzpg()
{
    uint8_t offset = get_arg(1);
    cpu.a ^=mem.ram[0][offset];

    if(!cpu.a)
        setsr(1);
    else
        unsetsr(1);

    if(cpu.a &0b10000000)
        setsr(7);
    else
        unsetsr(7);

}

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
{
    uint8_t dm = get_arg(1);
    uint8_t high=mem.ram[0][dm+1];
    uint8_t low=mem.ram[0][dm];
    uint16_t offset =(high<<8)+low+cpu.y;
    cpu.a ^=mem.ram[offset>>8][offset & 0XFF];

    if(!cpu.a)
        setsr(1);
    else
        unsetsr(1);

    if(cpu.a &0b10000000)
        setsr(7);
    else
        unsetsr(7);

}

void eorzpgx()
{
    uint8_t offset = get_arg(1)+cpu.x;
    cpu.a ^=mem.ram[0][offset];

    if(!cpu.a)
        setsr(1);
    else
        unsetsr(1);

    if(cpu.a &0b10000000)
        setsr(7);
    else
        unsetsr(7);

}

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