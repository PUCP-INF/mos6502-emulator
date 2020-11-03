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
{
    unsetsr(3);
}

void inx()
{
    cpu.x++;
}

void sed()
{
    setsr(3);
}

void txa()
{}

void txs()
{}

void tax()
{}

void tsx()
{}

void dex()
{}

void nop()
{
    //DO NOTHING
}
