//
// Created by cst on 10/31/20.
//

#include "dec.h"
#include "cpu.h"
#include <stdio.h>

void deczpg()
{
    uint8_t offset = get_arg(1);
    mem.ram[0][offset] -= 1;
}

void deczpgx()
{}

void decabs()
{
    uint8_t low, high;
    low=get_arg(1);
    high=get_arg(2);
    mem.ram[high][low]-=1;
    if(!mem.ram[high][low])//Analizamos el 0 flag
        setsr(1);
    else
        unsetsr(1);

    if(mem.ram[high][low] & 0b10000000)//Analizamos el negative flag
        setsr(7);
    else
        unsetsr(7);

}

void decabsx()
{
    uint16_t offset;
    uint8_t low = get_arg(1);
    uint8_t high = get_arg(2);
    offset = (high*256)+low+cpu.x;
    high= offset/256;
    low= offset%256;
    mem.ram[high][low]-=1;
    if(!mem.ram[high][low])//Analizamos el 0 flag
        setsr(1);
    else
        unsetsr(1);

    if(mem.ram[high][low] & 0b10000000)//Analizamos el negative flag
        setsr(7);
    else
        unsetsr(7);

}