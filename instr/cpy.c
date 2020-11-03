//
// Created by cst on 10/31/20.
//

#include "cpy.h"
#include "cpu.h"
void cpyimm()
{}

void cpyzpg()
{}

void cpyabs()
{
    uint8_t variable = get_arg(1);
    uint8_t auxiliar ;
    auxiliar = cpu.y - variable;
    //bandera de 0 (Z)
    if(!auxiliar){
        setsr(1);
    }else{
        unsetsr(1);
    }
    //Bandera para negativo (N)
    if (auxiliar & 0b10000000){
        setsr(7);
    }else{
        unsetsr(7);
    }
    //Bandera para carry (C)
    if (auxiliar& 0b00000001){
        setsr(0);
    }else{
        unsetsr(0);
    }
}