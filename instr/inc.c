//
// Created by cst on 10/31/20.
//

#include "inc.h"
#include "cpu.h"

void inczpg()
{
    uint8_t low = cpu.pcl, high = cpu.pch;
    if (low + 1 > 0xff) {
        high += 1;
        low = 0;
    } else {
        low += 1;
    }
    uint8_t offset = mem.ram[high][low];
    mem.ram[0][offset] += 1;
}

void inczpgx()
{}

void incabs()
{}

void incabsx()
{}