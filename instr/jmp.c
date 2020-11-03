//
// Created by cst on 10/31/20.
//

#include "jmp.h"
#include "cpu.h"
#include <stdio.h>

void jsrabs()
{
    uint8_t low, high;
    low = cpu.pcl;
    high = cpu.pch;
    if ((int)low + 3 > 0xff) high += 1;
    push(low + 3);
    push(high);
    cpu.pch = get_arg(2);
    cpu.pcl = get_arg(1);
    cpu.pcu = 1;
}

void jmpabs()
{
    cpu.pch = get_arg(2);
    cpu.pcl = get_arg(1);
    cpu.pcu = 1;
}

void jmpind()
{}
