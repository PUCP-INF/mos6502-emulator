//
// Created by cst on 10/31/20.
//

#include "lda.h"
#include "cpu.h"
#include <stdio.h>

void ldaxind()
{}

void ldaindy()
{}

void ldazpg()
{
    uint8_t offset = get_arg(1);
    cpu.a = mem.ram[0][offset];
}

void ldazpgx()
{}

void ldaimm()
{   //en esta funcion le asigno al registro a el valor de getarg
    cpu.a = get_arg(1);//
}

void ldaabsy()
{}

void ldaabs()
{}

void ldaabsx()
{}
