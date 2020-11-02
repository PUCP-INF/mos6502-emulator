//
// Created by cst on 10/31/20.
//

#include "rol.h"
#include "cpu.h"

void rolzpg()
{
    uint8_t offset = get_arg(1);
    uint8_t elem=mem.ram[0][offset];
    if(elem & 0b10000000){
        setsr(0);
        elem<<=1;
        elem|=0b00000001;
    }
    else{
        unsetsr(0);
        elem<<=1;
    }
    if(!elem)
        setsr(1);
    else
        unsetsr(1);

    if(elem>127)
        setsr(6);
    else
        unsetsr(6);

    mem.ram[0][offset]=elem;

}

void rola()
{}

void rolabs()
{}

void rolzpgx()
{
    uint8_t offset = get_arg(1)+cpu.x;
    uint8_t elem=mem.ram[0][offset];
    if(elem & 0b10000000){
        setsr(0);
        elem<<=1;
        elem|=0b00000001;
    }
    else{
        unsetsr(0);
        elem<<=1;
    }

    if(elem>127)
        setsr(6);
    else
        unsetsr(6);


    mem.ram[0][offset]=elem;
}

void rolabsx()
{}
