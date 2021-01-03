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
    uint16_t res = low + 3;
    if (res > 0xff) high += 1;
    push(low + 3);
    push(high);
    cpu.pch = get_arg(2);   // 7
    cpu.pcl = get_arg(1);   // 2
    cpu.pcu = 1;
}

void jmpabs()
{
    cpu.pch = get_arg(2);
    cpu.pcl = get_arg(1);
    cpu.pcu = 1;
}

void jmpind()
{
    uint8_t low, high, memory;
    low = get_arg(1);//obtenemos la direccion
    high = get_arg(2);
    //vamos a esa direccion
    //Esta instruccion no modifica ninguna bandera
    cpu.pch = high;
    cpu.pcl = low;
}
