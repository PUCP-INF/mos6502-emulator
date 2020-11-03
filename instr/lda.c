//
// Created by cst on 10/31/20.
//

#include "lda.h"
#include "cpu.h"
#include <stdio.h>

void ldaxind()
{}

void ldaindy()
{}

void ldazpg()
{
    uint8_t offset = get_arg(1);
    cpu.a = mem.ram[0][offset];
}

void ldazpgx()
{
    uint8_t offset = get_arg(1);
    cpu.a = mem.ram[0][offset] + cpu.x;

    //modify N flag
    if(cpu.a>127)setsr(7);
    //modify z flag
    if(cpu.a==0)setsr(1);
}

void ldaimm()
{
    cpu.a = get_arg(1);
}

void ldaabsy()
{
    uint8_t low = get_arg(1), high = get_arg(2);
    if(low+cpu.y>255){
        high++;
        cpu.x=mem.ram[high][low+cpu.y-255];
    }else {
        cpu.x = mem.ram[high][low + cpu.y];
    }
}

void ldaabs()
{}

void ldaabsx()
{}
