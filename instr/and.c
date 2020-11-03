//
// Created by cst on 10/31/20.
//

#include "and.h"
#include "cpu.h"

void andxind()
{
    uint8_t dm=get_arg(1)+cpu.x;
    uint8_t high=mem.ram[0][dm+1];
    uint8_t low=mem.ram[0][dm];
    cpu.a &=mem.ram[high][low];

    if(!cpu.a)
        setsr(1);
    else
        unsetsr(1);

    if(cpu.a & 0b10000000)
        setsr(7);
    else
        unsetsr(7);

}

void andzpg()
{
    uint8_t offset = get_arg(1);
    cpu.a &=mem.ram[0][offset];

    if(!cpu.a)
        setsr(1);
    else
        unsetsr(1);

    if(cpu.a & 0b10000000)
        setsr(7);
    else
        unsetsr(7);

}

void andimm()
{
    uint8_t valor;
    valor = get_arg(1);
    cpu.a &=valor;//guardamos en a el valor de esa instruccion
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
}

void andabs()
{}

void andindy()
{
    uint8_t dm = get_arg(1);
    uint8_t high=mem.ram[0][dm+1];
    uint8_t low=mem.ram[0][dm];
    uint16_t offset =(high<<8)+low+cpu.y;
    cpu.a &=mem.ram[offset>>8][offset & 0XFF];
    if(!cpu.a)
        setsr(1);
    else
        unsetsr(1);

    if(cpu.a & 0b10000000)
        setsr(7);
    else
        unsetsr(7);

}

void andzpgx()
{
    uint8_t offset = get_arg(1)+cpu.x;
    cpu.a &=mem.ram[0][offset];

    if(!cpu.a)
        setsr(1);
    else
        unsetsr(1);

    if(cpu.a & 0b10000000)
        setsr(7);
    else
        unsetsr(7);

}

void andabsy()
{
    uint8_t auxiliar = get_arg(1);
    uint8_t valor = get_arg(2);
    auxiliar = auxiliar + valor;
    cpu.a &= auxiliar;
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
}

void andabsx()
{

}