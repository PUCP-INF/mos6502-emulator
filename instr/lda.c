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
    uint8_t low = cpu.pcl, high = cpu.pch;
    if (low + 1 > 0xff) {
        low = 0;
        high += 1;
    } else {
        low += 1;
    }
    uint8_t offset = mem.ram[high][low];
    cpu.a = mem.ram[0][offset];
}

void ldazpgx()
{}

void ldaimm()
{
    cpu.a = mem.ram[cpu.pch][cpu.pcl + 1];
}

void ldaabsy()
{}

void ldaabs()
{}

void ldaabsx()
{}
