//
// Created by cst on 10/31/20.
//

#include "ldy.h"
#include "cpu.h"

void ldyimm()
{
    uint8_t value_mem = get_arg(1);
    cpu.y=value_mem;

    if(cpu.y==0)
        setsr(1);

    if(cpu.y & 0b10000000)
        setsr(7);
}

void ldyzpg()
{
    uint8_t offset = get_arg(1);
    cpu.y = mem.ram[0][offset];
}

void ldyzpgx()
{
    uint8_t offset = get_arg(1) + cpu.x;
    cpu.y=mem.ram[0][offset];
}

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
