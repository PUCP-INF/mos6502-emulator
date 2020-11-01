//
// Created by cst on 10/31/20.
//

#include "impl.h"
#include "cpu.h"

void brk()
{}

void rti()
{}

void rts()
{}

void php()
{
    push(cpu.sr);
}

void clc()
{}

void plp()
{
    cpu.sr = pop();
}

void sec()
{}

void pha()
{
    push(cpu.a);
}

void cli()
{}

void pla()
{
    cpu.a = pop();
}

void sei()
{}

void dey()
{}

void tya()
{}

void tay()
{}

void clv()
{}

void iny()
{
    cpu.y++;
}

void cld()
{}

void inx()
{
    cpu.x++;
}

void sed()
{}

void txa()
{}

void txs()
{
    cpu.sp = cpu.x;
}

void tax()
{}

void tsx()
{
    cpu.x = cpu.sp;
}

void dex()
{}

void nop()
{}
