//
// Created by cst on 10/31/20.
//
#include "cpu.h"
#include "ora.h"
#include <stdio.h>

void oraxind()
{}

void orazpg()
{}

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
{}

void oraindy()
{}

void orazpgx()
{}

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
{}
