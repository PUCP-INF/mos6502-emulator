//
// Created by cst on 10/31/20.
//

#include "ldx.h"
#include "cpu.h"

void ldximm()
{
    cpu.x = mem.ram[cpu.pch][cpu.pcl+1];
}

void ldxzpg()
{}

void ldxzpgy()
{}

void ldxabs()
{}

void ldxabsy()
{}
