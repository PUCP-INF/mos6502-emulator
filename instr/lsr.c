//
// Created by cst on 10/31/20.
//

#include "lsr.h"
#include "cpu.h"
void lsrzpg()
{}

void lsra()
{
    cpu.a >>=1;//lo dividimos entre 2
    //bandera de 0 (Z)
    if(!cpu.a){
        setsr(1);
    }else{
        unsetsr(1);
    }
    //Bandera para negativo (N)
    // se setea por defecto
    setsr(7);
    if (cpu.a & 0b00000001){
        setsr(0);
    }
}

void lsrabs()
{}

void lsrzpgx()
{}

void lsrabsx()
{}
