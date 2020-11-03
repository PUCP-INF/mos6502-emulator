//
// Created by cst on 10/31/20.
//
#include "cpu.h"
#include "ora.h"

void oraxind()
{
    uint8_t dm=get_arg(1)+cpu.x;
    uint16_t high=mem.ram[0][dm+1];
    uint16_t low=mem.ram[0][dm];
    cpu.a |=mem.ram[high][low];

    if(!cpu.a)
        setsr(1);
    else
        unsetsr(1);

    if(cpu.a & 0b10000000)
        setsr(7);
    else
        unsetsr(7);

}

void orazpg()
{
    uint8_t offset = get_arg(1);
    cpu.a |=mem.ram[0][offset];

    if(!cpu.a)
        setsr(1);
    else
        unsetsr(1);

    if(cpu.a &0b10000000)
        setsr(7);
    else
        unsetsr(7);
}

void oraimmd()
{//falta revisar
    //Aqui tengo que completar la funcion
    uint8_t valor;
    valor = get_arg(1);//ya que tiene 2 bytes
    cpu.a |=valor;//guardamos en a el valor de esa instruccion
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

void oraabs()
{
    uint8_t low = get_arg(1);
    uint8_t high = get_arg(2);
    cpu.a |= mem.ram[high][low];

    if(!cpu.a)//Analizamos el 0 flag
        setsr(1);
    else
        unsetsr(1);

    if(cpu.a & 0b10000000)//Analizamos el negative flag
        setsr(7);
    else
        unsetsr(7);
}

void oraindy()
{
    uint8_t dm = get_arg(1);
    uint8_t high=mem.ram[0][dm+1];
    uint8_t low=mem.ram[0][dm];
    uint16_t offset =(high<<8)+low+cpu.y;
    cpu.a |=mem.ram[offset>>8][offset & 0XFF];

    if(!cpu.a)
        setsr(1);
    else
        unsetsr(1);

    if(cpu.a &0b10000000)
        setsr(7);
    else
        unsetsr(7);

}

void orazpgx()
{
    uint8_t offset = get_arg(1)+cpu.x;
    cpu.a |=mem.ram[0][offset];

    if(!cpu.a)
        setsr(1);
    else
        unsetsr(1);

    if(cpu.a &0b10000000)
        setsr(7);
    else
        unsetsr(7);

}

void oraabsy()
{
    //tenemos que hacer el OR del registro a con el operando 1 agregando el valor del
    //registro y
    uint8_t auxiliar = get_arg(1);
    uint8_t valor = get_arg(2);
    auxiliar = auxiliar + valor;
    cpu.a |= auxiliar;
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

void oraabsx()
{
    uint16_t offset;
    uint8_t low = get_arg(1);
    uint8_t high = get_arg(2);
    offset = high*256+low+cpu.x;

    high=offset/256;
    low=offset%256;

    cpu.a |=mem.ram[high][low];

    if(!cpu.a)
        setsr(1);
    else
        unsetsr(1);

    if(cpu.a & 0b10000000)
        setsr(7);
    else
        unsetsr(7);
}
