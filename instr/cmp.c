//
// Created by cst on 10/31/20.
//

#include "cmp.h"
#include "cpu.h"
#include <stdio.h>
void setcmpflags(uint8_t value)
{
    if (cpu.a == value) {
        setsr(1);
    }else{
        unsetsr(1);
    }
    if (cpu.a >= value) {
        setsr(0);
    }else{
        unsetsr(0);
    }
}

void cmpxind()
{
    uint8_t dm=get_arg(1)+cpu.x;
    uint8_t high=mem.ram[0][dm+1];
    uint8_t low=mem.ram[0][dm];
    uint8_t value=mem.ram[high][low];
    setcmpflags(value);
}

void cmpindy()
{
    uint8_t dm = get_arg(1);
    uint8_t high=mem.ram[0][dm+1];
    uint8_t low=mem.ram[0][dm];
    uint16_t offset =(high<<8)+low+cpu.y;
    uint8_t value=mem.ram[offset>>8][offset & 0XFF];
    setcmpflags(value);
}
void cmpzpg()
{
    uint8_t offset = get_arg(1), value = mem.ram[0][offset];
    setcmpflags(value);
}

void cmpzpgx()
{
    uint8_t value = mem.ram[0][cpu.x + get_arg(1)];
    setcmpflags(value);
}

void cmpimm()
{
    //uint8_t low = get_arg(1), high = get_arg(2), value = mem.ram[high][low];
    setcmpflags(get_arg(1));
}

void cmpabsy()
{
    uint16_t addr = ((uint8_t)get_arg(2) << 8) | get_arg(1) + (uint16_t)cpu.y;
    uint8_t high = (addr & 0xff00) >> 8, low = addr & 0x00ff;
    setcmpflags(mem.ram[high][low]);
}

void cmpabs()
{
    uint8_t value = mem.ram[get_arg(2)][get_arg(1)];
    setcmpflags(value);
}

void cmpabsx()
{
    uint16_t addr = ((uint8_t)get_arg(2) << 8) | get_arg(1) + (uint16_t)cpu.x;
    uint8_t high = (addr & 0xff00) >> 8, low = addr & 0x00ff;
    setcmpflags(mem.ram[high][low]);
}
