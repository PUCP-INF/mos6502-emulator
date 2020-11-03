//
// Created by cst on 10/31/20.
//

#include "and.h"
#include "cpu.h"
void andxind()
{}

void andzpg()
{}

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
{}

void andzpgx()
{}

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
{}