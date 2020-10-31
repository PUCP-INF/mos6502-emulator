//
// Created by cst on 10/31/20.
//

#include "inc.h"
#include "cpu.h"

void inczpg()
{
    uint8_t low, high;
    uint8_t offset = mem.ram[cpu.pch][cpu.pcl+1];
    mem.ram[0][offset] += 1;
}

void inczpgx()
{}

void incabs()
{}

void incabsx()
{}