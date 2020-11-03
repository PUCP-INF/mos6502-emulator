//
// Created by cst on 10/31/20.
//

#include "dec.h"
#include "cpu.h"

void deczpg()
{
    uint8_t offset = get_arg(1);
    mem.ram[0][offset] -= 1;
}

void deczpgx()
{
    uint8_t offset = get_arg(1) ;
    cpu.x +=1;
    mem.ram[0][offset] -= 1;
    //modify N flag
    if(mem.ram[0][offset]>127)setsr(7);
    //modify z flag
    if(mem.ram[0][offset]==0)setsr(1);
}

void decabs()
{}

void decabsx()
{}