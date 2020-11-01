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
{}

void decabs()
{}

void decabsx()
{}