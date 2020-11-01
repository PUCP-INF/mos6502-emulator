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
    int8_t offset = get_arg(1);
    if (!getsr(1)) {
        cpu.pcl += offset;
        if (offset < 0) {
            cpu.pcl -= 2;
        }
    }
}

void beq()
{}
