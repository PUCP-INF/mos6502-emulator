//
// Created by cst on 10/31/20.
//

#include "asl.h"
#include "cpu.h"

void aslzpg()
{
    uint8_t offset = get_arg(1);
    uint8_t elem=mem.ram[0][offset];
    if(elem & 0b10000000)
        setsr(0);
    else
        unsetsr(0);

    if(elem & 0b010000000)
        setsr(7);
    else
        unsetsr(7);

    elem<<=1UL;
    if(!elem)
        setsr(1);
    else
        unsetsr(1);

    mem.ram[0][offset]=elem;

}

void asla()
{

}

void aslabs()
{}

void aslzpgx()
{
    uint8_t offset = get_arg(1)+cpu.x;
    uint8_t elem =mem.ram[0][offset];
    if(elem & 0b10000000)
        setsr(0);
    else
        unsetsr(0);

    if(elem & 0b010000000)
        setsr(7);
    else
        unsetsr(7);

    elem<<=1UL;
    if(!elem)
        setsr(1);
    else
        unsetsr(1);


    mem.ram[0][offset]=elem;
}

void aslabsx()
{}