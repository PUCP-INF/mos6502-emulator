//
// Created by cst on 10/31/20.
//

#include "bit.h"
#include "cpu.h"
#include "and.h"

void bitzpg()
{
    int bitSvn,bitSix;
    uint8_t memory;
    uint8_t offset = get_arg(1);
    memory = mem.ram[0][offset];

    bitSvn= (memory >> 7) & 0x01;
    bitSix= (memory >> 6) & 0x01;

    //Asignamos los bits
    if(bitSvn)
        setsr(7);
    else
        unsetsr(7);

    if(bitSix)
        setsr(6);
    else
        unsetsr(6);

    //Activamos el zero flag
    if(cpu.a&memory==0)
        setsr(1);
}

void bitabs() //Oper means a memory direction
{
    int bitSvn,bitSix;
    uint8_t memory;
    uint8_t low = get_arg(1);
    uint8_t high = get_arg(2);
    memory = mem.ram[high][low];

    bitSvn= (memory >> 7) & 0x01;
    bitSix= (memory >> 6) & 0x01;

    //Asignamos los bits
    if(bitSvn)
        setsr(7);
    else
        unsetsr(7);

    if(bitSix)
        setsr(6);
    else
        unsetsr(6);

    //Activamos el zero flag
    if(cpu.a&memory==0)
        setsr(1);
}

