//
// Created by cst on 10/31/20.
//

#include "cmp.h"
#include "cpu.h"

void cmpxind()
{}

void cmpindy()
{}

void cmpzpg()
{
    uint8_t low = cpu.pcl, high = cpu.pch;
    if (low + 1 > 0xff) {
        low = 0;
        high += 1;
    } else {
        low += 1;
    }
    uint8_t offset = mem.ram[high][low], value = mem.ram[0][offset];
    if (cpu.a == value) setsr(2);
}

void cmpzpgx()
{}

void cmpimm()
{}

void cmpabsy()
{}

void cmpabs()
{}

void cmpabsx()
{}
