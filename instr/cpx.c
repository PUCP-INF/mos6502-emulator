#include "cpx.h"
#include "cpu.h"

void cpximm()
{
    uint8_t value_mem = get_arg(1);
    if(value_mem >= cpu.x)//Seteamos el carry flag
        setsr(0);
    else unsetsr(0);

    if(value_mem == cpu.x)//Seteamos el zero flag
        setsr(1);
    else unsetsr(1);

    if((value_mem >> 7) & 0x01)
        setsr(7);
    else unsetsr(7);
}

void cpxzpg()
{
    uint8_t offset = get_arg(1);
    uint8_t memory;
    memory = mem.ram[0][offset];
    if(memory >= cpu.x)//Seteamos el carry flag
        setsr(0);
    else unsetsr(0);

    if(memory == cpu.x)//Seteamos el zero flag
        setsr(1);
    else unsetsr(1);

    if((memory >> 7) & 0x01)
        setsr(7);
    else unsetsr(7);
}

void cpxabs()
{
    uint8_t variable = get_arg(1);
    uint8_t auxiliar ;
    auxiliar = cpu.x - variable;
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
