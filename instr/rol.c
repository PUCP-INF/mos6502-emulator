//
// Created by cst on 10/31/20.
//

#include "rol.h"
#include "cpu.h"


void rolzpg()
{

}

void rola()
{   /*Rotamos un bit a la izquierda de la memoria que nos estan dando*/
    uint8_t auxiliar, regA;
    /*Aqui solo rotamos un bit del acumulador
     * para ello, procederemos con el metood para rotar:
     * Primero rotamos un bit a la izqueirda y hacemos un or con
     * un shift rigth de 7 para salbvar el ultimo valor*/
    regA = cpu.a;
    auxiliar = (regA << 1 ) | (regA >>(8-1));
    cpu.a = auxiliar;//asignamos el valor una vez hecha la rotacion
    //banderas
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

void rolabs()
{}

void rolzpgx()
{}

void rolabsx()
{}
