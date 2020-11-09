//
// Created by cst on 10/31/20.
//

#include "sbc.h"
#include "cpu.h"

void sbcxind()
{
    uint8_t dm=get_arg(1)+cpu.x;
    uint8_t high=mem.ram[0][dm+1];
    uint8_t low=mem.ram[0][dm];
    cpu.a= cpu.a-mem.ram[high][low];
    uint8_t value_a = cpu.a;

    //modify C flag
    if(value_a<0)unsetsr(0);
    else setsr(0);
    //modify N flag
    if(value_a<0)setsr(7);
    else unsetsr(7);
    //modify z flag
    if(value_a==0)setsr(1);
    else unsetsr(1);
    //modifi V flag
    if(value_a > 127 || value_a < -127) {
        setsr(6);
    } else {
        unsetsr(6);
    }
}

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
    //RAA ESTO RAAA
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
{
    uint8_t value_mem = mem.ram[0][get_arg(1) + cpu.x];
    int16_t value_a = cpu.a + getsr(0) * 256 - value_mem;
    cpu.a += getsr(0) * 256 - value_mem;
    //modify C flag
    if(value_a<0)unsetsr(0);
    else setsr(0);
    //modify N flag
    if(value_a>127) {
        setsr(7);
    } else {
        unsetsr(7);
    }
    //modify z flag
    if(value_a==0) {
        setsr(1);
    } else {
        unsetsr(1);
    }
    //modify V flag
    if(value_a > 127 || value_a < -127) {
        setsr(5);
    } else {
        unsetsr(5);
    }
}

void sbcimm()
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

void sbcabsy()
{
    uint16_t offset;
    uint8_t low = get_arg(1);
    uint8_t high = get_arg(2);
    offset = (high*256)+low+cpu.y;
    high= offset/256;
    low= offset%256;
    uint8_t value_mem = mem.ram[high][low];
    cpu.a =cpu.a- value_mem + cpu.y;

    uint8_t value_a = cpu.a;

    //modify C flag
    if(value_a<0)unsetsr(0);
    else setsr(0);
    //modify N flag
    if(value_a<0)setsr(7);
    else unsetsr(7);
    //modify z flag
    if(value_a==0)setsr(1);
    else unsetsr(1);
    //modifi V flag
    if(value_a > 127 || value_a < -127) {
        setsr(6);
    } else {
        unsetsr(6);
    }
}

void sbcabs()
{
    uint8_t low, high;
    low=get_arg(1);
    high=get_arg(2);
    cpu.a=cpu.a-mem.ram[high][low];
    uint8_t value_a = cpu.a;

    //modify C flag
    if(value_a<0)unsetsr(0);
    else setsr(0);
    //modify N flag
    if(value_a<0)setsr(7);
    else unsetsr(7);
    //modify z flag
    if(value_a==0)setsr(1);
    else unsetsr(1);
    //modifi V flag
    if(value_a > 127 || value_a < -127) {
        setsr(6);
    } else {
        unsetsr(6);
    }
}

void sbcabsx()
{
    uint16_t offset;
    uint8_t low = get_arg(1);
    uint8_t high = get_arg(2);
    offset = (high*256)+low+cpu.x;
    high= offset/256;
    low= offset%256;
    uint8_t value_mem = mem.ram[high][low];
    cpu.a =cpu.a- value_mem + cpu.x;

    uint8_t value_a = cpu.a;

    //modify C flag
    if(value_a<0)unsetsr(0);
    else setsr(0);
    //modify N flag
    if(value_a<0)setsr(7);
    else unsetsr(7);
    //modify z flag
    if(value_a==0)setsr(1);
    else unsetsr(1);
    //modifi V flag
    if(value_a > 127 || value_a < -127) {
        setsr(6);
    } else {
        unsetsr(6);
    }
}
