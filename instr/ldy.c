//
// Created by cst on 10/31/20.
//

#include "ldy.h"
#include "cpu.h"
#include <stdio.h>
void ldyimm()
{}

void ldyzpg()
{}

void ldyzpgx()
{}

void ldyabs()
{   /*Buscaremos la direccion  y lo pondremos en el registro y*/
    cpu.y = mem.ram[get_arg(1)][get_arg(2)];//asi cargamos el registro
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

void ldyabsx()
{
    uint8_t auxiliar = get_arg(3);
    cpu.y = mem.ram[get_arg(1)][get_arg(2)] + auxiliar;
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
