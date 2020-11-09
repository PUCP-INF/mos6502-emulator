//
// Created by cst on 10/31/20.
//

#include "ror.h"
#include "cpu.h"

void rorzpg()
{
    uint8_t offset = get_arg(1);
    uint8_t memory = mem.ram[0][offset];
    uint8_t auxiliar= (memory >> 1)|(uint8_t)getsr(0)<<7;
    mem.ram[0][offset]=auxiliar;

    if(!auxiliar){
        setsr(1);
    }else{
        unsetsr(1);
    }
    if (auxiliar & 0b10000000){
        setsr(7);
    }else{
        unsetsr(7);
    }
    //Bandera para carry (C)
    if (memory & 0b00000001){
        setsr(0);
    }else {
        unsetsr(0);
    }
}

void rorzpgx()
{
    uint8_t offset = get_arg(1)+cpu.x;
    uint8_t memory = mem.ram[0][offset];
    uint8_t auxiliar= (memory >> 1)|(uint8_t)getsr(0)<<7;

    mem.ram[0][offset]=auxiliar;

    if(!auxiliar){
        setsr(1);
    }else{
        unsetsr(1);
    }
    if (auxiliar & 0b10000000){
        setsr(7);
    }else{
        unsetsr(7);
    }
    //Bandera para carry (C)
    if (memory & 0b00000001){
        setsr(0);
    }else {
        unsetsr(0);
    }


}

void rora()
{
    /*Rotamos un bit a la derecha de la memoria que nos estan dando*/
    uint8_t auxiliar, regA;
    /*Aqui solo rotamos un bit del acumulador
     * para ello, procederemos con el metood para rotar:
     * Primero rotamos un bit a la izqueirda y hacemos un or con
     * un shift rigth de 7 para salbvar el ultimo valor*/
    regA = cpu.a;
    auxiliar = (regA >> 1 ) | (uint8_t)getsr(0)<<7;
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
    if (regA& 0b00000001){
        setsr(0);
    }else{
        unsetsr(0);
    }
}

void rorabs()
{
    uint8_t memory;
    uint8_t low = get_arg(1);
    uint8_t high = get_arg(2);
    memory = mem.ram[high][low];
    mem.ram[high][low] = (memory >> 1)|(uint8_t)getsr(0)<<7;//8bits-1bit


    if(!cpu.a)//Analizamos el 0 flag
        setsr(1);
    else
        unsetsr(1);

    if(memory & 0b10000000)//Analizamos el negative flag
        setsr(7);
    else
        unsetsr(7);

    if (memory & 0b00000001){ //carry flag
        setsr(0);
    }else{
        unsetsr(0);
    }

}

void rorabsx()
{
    uint16_t offset, memory;
    uint8_t low = get_arg(1);
    uint8_t high = get_arg(2);
    offset = high*256+low+cpu.x;
    high=offset/256;
    low=offset%256;
    memory = mem.ram[high][low];
    mem.ram[high][low] = (memory >> 1)|(uint8_t)getsr(0)<<7;//8bits-1bit

    if(!cpu.a)//Analizamos el 0 flag
        setsr(1);
    else
        unsetsr(1);

    if(cpu.a & 0b10000000)//Analizamos el negative flag
        setsr(7);
    else
        unsetsr(7);
    if (memory & 0b00000001){ //carry flag
        setsr(0);
    }else{
        unsetsr(0);
    }


}
