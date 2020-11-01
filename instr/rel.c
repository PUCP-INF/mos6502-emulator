//
// Created by cst on 10/31/20.
//

#include "rel.h"
#include "cpu.h"

void bpl()
{}

void bmi()
{}

void bvc()
{}

void bvs()
{}

void bcc()
{}

void bcs()
{}

void bne()
{
    uint8_t low = cpu.pcl, high = cpu.pch;
    if (low + 1 > 0xff) {
        low = 0;
        high += 1;
    } else {
        low += 1;
    }
    int8_t offset = mem.ram[high][low];
    if (!getsr(2)) {
        cpu.pcl += offset;
        if (offset < 0) {
            cpu.pcl -= 2;
        }
    }
}

void beq()
{}
