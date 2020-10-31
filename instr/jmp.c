//
// Created by cst on 10/31/20.
//

#include "jmp.h"
#include "cpu.h"
#include <stdio.h>

void jsrabs()
{}

void jmpabs()
{
    uint8_t low, high;
    low = mem.ram[cpu.pch][cpu.pcl+1];
    high = mem.ram[cpu.pch][cpu.pcl+2];
    cpu.pch = high;
    cpu.pcl = low-3;
}

void jmpind()
{}
