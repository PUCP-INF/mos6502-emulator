//
// Created by cst on 10/31/20.
//

#include "eor.h"
#include "cpu.h"
void eorxind()
{}

void eorzpg()
{}

void eorimm()
{
    /*Exclusive or con una valor inmediato y el acumulador*/
    uint8_t valor ;
    valor= get_arg(1);
    cpu.a ^=valor;
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

void eorabs()
{}

void eorindy()
{}

void eorzpgx()
{}

void eorabsy()
{
    uint8_t auxiliar = get_arg(1);
    uint8_t valor = get_arg(2);
    auxiliar = auxiliar + valor;
    cpu.a ^= auxiliar;
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

void eorabsx()
{}