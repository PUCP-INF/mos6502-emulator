//
// Created by cst on 10/31/20.
//

#include "lda.h"
#include "cpu.h"
#include <stdio.h>

void ldaxind()
{
    uint8_t dm=get_arg(1)+cpu.x;
    uint8_t high=mem.ram[0][dm+1];
    uint8_t low=mem.ram[0][dm];
    cpu.a=mem.ram[high][low];
    if(!cpu.a)//Analizamos el 0 flag
        setsr(1);
    else
        unsetsr(1);

    if(cpu.a & 0b10000000)//Analizamos el negative flag
        setsr(7);
    else
        unsetsr(7);

}

void ldaindy()
{
    uint8_t dm = get_arg(1);
    uint8_t high=mem.ram[0][dm+1];
    uint8_t low=mem.ram[0][dm];
    uint16_t offset =(high<<8)+low+cpu.y;
    cpu.a=mem.ram[offset>>8][offset & 0XFF];
    if(!cpu.a)//Analizamos el 0 flag
        setsr(1);
    else
        unsetsr(1);

    if(cpu.a & 0b10000000)//Analizamos el negative flag
        setsr(7);
    else
        unsetsr(7);
}

void ldazpg()
{
    uint8_t offset = get_arg(1);
    cpu.a = mem.ram[0][offset];
}

void ldazpgx()
{
    uint8_t offset = get_arg(1);
    cpu.a = mem.ram[0][offset] + cpu.x;

    //modify N flag
    if(cpu.a>127)setsr(7);
    //modify z flag
    if(cpu.a==0)setsr(1);
}

void ldaimm()
{   //en esta funcion le asigno al registro a el valor de getarg
    cpu.a = get_arg(1);//
}

void ldaabsy()
{
    uint8_t low = get_arg(1), high = get_arg(2);
    if(low+cpu.y>255){
        high++;
        cpu.x=mem.ram[high][low+cpu.y-255];
    }else {
        cpu.x = mem.ram[high][low + cpu.y];
    }
}

void ldaabs()
{
    cpu.a=mem.ram[get_arg(2)][get_arg(1)];
    if(!cpu.a)//Analizamos el 0 flag
        setsr(1);
    else
        unsetsr(1);

    if(cpu.a & 0b10000000)//Analizamos el negative flag
        setsr(7);
    else
        unsetsr(7);
}

void ldaabsx()
{
    uint16_t offset;
    uint8_t low = get_arg(1);
    uint8_t high = get_arg(2);
    offset = (high*256)+low+cpu.x;
    high= offset/256;
    low= offset%256;
    cpu.a=mem.ram[high][low];
    if(!cpu.a)//Analizamos el 0 flag
        setsr(1);
    else
        unsetsr(1);

    if(cpu.a & 0b10000000)//Analizamos el negative flag
        setsr(7);
    else
        unsetsr(7);
}