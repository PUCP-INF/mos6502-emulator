//
// Created by cst on 10/31/20.
//

#include "impl.h"
#include "cpu.h"
#include <stdio.h>
void setzeronegflags(uint8_t value)
{
    if (!value) setsr(1);
    if ((value >> 7) & 0x01) setsr(7);
}

void brk()
{}

void rti()
{}

void rts()
{
    cpu.pch = pop();
    cpu.pcl = pop();
    cpu.pcu = 1;
}

void php()
{
    push(cpu.sr);
}

void clc()
{
    unsetsr(0);
}

void plp()
{
    cpu.sr = pop();
}

void sec()
{
    setsr(0);
}

void pha()
{
    push(cpu.a);
}

void cli()
{
    unsetsr(2);
}

void pla()
{
    cpu.a = pop();
    setzeronegflags(cpu.a);
}

void sei()
{
    setsr(2);
}

void dey()
{
    cpu.y--;
    setzeronegflags(cpu.y);
}

void tya()
{
    cpu.a = cpu.y;
    setzeronegflags(cpu.a);
}

void tay()
{
    cpu.y = cpu.a;
    setzeronegflags(cpu.y);
}

void clv()
{
    unsetsr(6);
}

void iny()
{
    cpu.y++;
    setzeronegflags(cpu.y);
}

void cld()
{
    unsetsr(3);
}

void inx()
{
    cpu.x++;
    setzeronegflags(cpu.x);
}

void sed()
{
    setsr(3);
}

void txa()
{
    cpu.a = cpu.x;
    setzeronegflags(cpu.a);
}

void txs()
{
    cpu.sp = cpu.x;
}

void tax()
{
    cpu.x = cpu.a;
    setzeronegflags(cpu.x);
}

void tsx()
{
    cpu.x = cpu.sp;
    setzeronegflags(cpu.x);
}

void dex()
{
    cpu.x--;
    setzeronegflags(cpu.x);
}

void nop()
{
    printf("aqui toy (nop)\n");
    //DO NOTHING
}
