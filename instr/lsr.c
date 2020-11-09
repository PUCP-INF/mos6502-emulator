//
// Created by cst on 10/31/20.
//

#include "lsr.h"
#include "cpu.h"

void lsrzpg()
{
    uint8_t offset = get_arg(1);
    uint8_t elem=mem.ram[0][offset];
    if(elem & 0b00000001)
        setsr(0);
    else
        unsetsr(0);

    elem>>=1;

    if(!elem)
        setsr(1);
    else
        unsetsr(1);

    unsetsr(7);

    mem.ram[0][offset]=elem;

}

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
{
    uint8_t memory;
    uint8_t low = get_arg(1);
    uint8_t high = get_arg(2);
    memory = mem.ram[high][low];
    mem.ram[high][low] = memory>>1;

    if(getsr(0))
        setsr(0);
    else
        unsetsr(0);

    if(!cpu.a)//Analizamos el 0 flag
        setsr(1);
    else
        unsetsr(1);

    if(cpu.a & 0b10000000)//Analizamos el negative flag
        setsr(7);
    else
        unsetsr(7);
}

void lsrzpgx()
{
    uint8_t offset = get_arg(1)+cpu.x;
    uint8_t elem=mem.ram[0][offset];
    if(elem & 0b00000001)
        setsr(0);
    else
        unsetsr(0);

    elem>>=1;

    if(!elem)
        setsr(1);
    else
        unsetsr(1);

    unsetsr(7);

    mem.ram[0][offset]=elem;


}

void lsrabsx()
{
    uint16_t offset, memory;
    uint8_t low = get_arg(1);
    uint8_t high = get_arg(2);
    offset = high*256+low+cpu.x;
    high=offset/256;
    low=offset%256;
    memory = mem.ram[high][low];
    mem.ram[high][low] = memory>>1;

    if(getsr(0))
        setsr(0);
    else
        unsetsr(0);

    if(!cpu.a)//Analizamos el 0 flag
        setsr(1);
    else
        unsetsr(1);

    if(cpu.a & 0b10000000)//Analizamos el negative flag
        setsr(7);
    else
        unsetsr(7);
}
