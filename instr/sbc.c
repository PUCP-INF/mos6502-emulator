//
// Created by cst on 10/31/20.
//

#include "sbc.h"
#include "cpu.h"
void sbcxind()
{}

void sbcindy()
{
    uint8_t dm = get_arg(1);
    uint8_t high=mem.ram[0][dm+1];
    uint8_t low=mem.ram[0][dm];
    uint16_t offset =(high<<8)+low+cpu.y;
    cpu.a =cpu.a - mem.ram[offset>>8][offset & 0XFF];
    uint8_t auxiliar = cpu.a;
    uint8_t value_mem=mem.ram[offset>>8][offset & 0XFF];
    //Vamos a modifiar las banderas
    //modigy C carry
    if(auxiliar<0)unsetsr(0);
    else setsr(0);
    //modify N flag
    if(auxiliar<0)setsr(7);
    else unsetsr(7);
    //modify z flag
    if(auxiliar==0)setsr(1);
    else unsetsr(1);
    //modify V flag overflow
    if(value_mem > 127 || value_mem < -127) {//se pasa de los rangos
        setsr(6);
    } else {
        unsetsr(6);
    }
}

void sbczpg()
{
    uint8_t offset = get_arg(1);
    cpu.a = cpu.a - mem.ram[0][offset];
    uint8_t value_mem = mem.ram[0][offset];
    //banderas
    //bandera de 0 (Z)
    uint8_t auxiliar;
    auxiliar = cpu.a;
    //Vamos a modifiar las banderas
    //modigy C carry
    if(auxiliar<0)unsetsr(0);
    else setsr(0);
    //modify N flag
    if(auxiliar<0)setsr(7);
    else unsetsr(7);
    //modify z flag
    if(auxiliar==0)setsr(1);
    else unsetsr(1);
    //modify V flag overflow
    if(value_mem > 127 || value_mem < -127) {//se pasa de los rangos
        setsr(6);
    } else {
        unsetsr(6);
    }
}

void sbczpgx()
{}

void sbcimm()
{}

void sbcabsy()
{}

void sbcabs()
{}

void sbcabsx()
{}
