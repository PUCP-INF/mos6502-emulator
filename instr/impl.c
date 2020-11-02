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
{}

void clc()
{}

void plp()
{}

void sec()
{}

void pha()
{}

void cli()
{}

void pla()
{}

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
{
    cpu.a=cpu.x;
}

void txs()
{
    cpu.sr=cpu.x;
}

void tax()
{
    cpu.x=cpu.a;
}

void tsx()
{
    cpu.x=cpu.sr;
}

void dex()
{
    cpu.x--;
}

void nop()
{}
