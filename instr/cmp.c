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
    uint8_t offset = get_arg(1), value = mem.ram[0][offset];
    if (cpu.a == value) {
        setsr(1);
    } else {
        unsetsr(1);
    }
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
