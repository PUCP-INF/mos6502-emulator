//
// Created by cst on 10/31/20.
//

#include "asl.h"
#include "cpu.h"

void aslzpg()
{
    uint8_t offset = get_arg(1);
    uint8_t elem=mem.ram[0][offset];
    if(elem & 0b10000000)
        setsr(0);
    else
        unsetsr(0);

    if(elem & 0b010000000)
        setsr(7);
    else
        unsetsr(7);

    elem<<=1UL;
    if(!elem)
        setsr(1);
    else
        unsetsr(1);

    mem.ram[0][offset]=elem;

}

void asla()
{//shift left one bit del acumulador
    cpu.a= cpu.a<<1;//lo multiplicamos x2
    //bandera de 0 (Z)
    if(!cpu.a){
        setsr(1);
    }else{
        unsetsr(1);
    }
    //Bandera para negativo (N)
    if (cpu.a & 0b10000000){
        setsr(7);
    }else{
        unsetsr(7);
    }
    //Bandera de carry(C)
    if (getsr(0)){
        setsr(0);
    }else{
        unsetsr(0);
    }
{

}

void aslabs()
{}

void aslzpgx()
{
    uint8_t offset = get_arg(1)+cpu.x;
    uint8_t elem =mem.ram[0][offset];
    if(elem & 0b10000000)
        setsr(0);
    else
        unsetsr(0);

    if(elem & 0b010000000)
        setsr(7);
    else
        unsetsr(7);

    elem<<=1UL;
    if(!elem)
        setsr(1);
    else
        unsetsr(1);


    mem.ram[0][offset]=elem;
}

void aslabsx()
{}