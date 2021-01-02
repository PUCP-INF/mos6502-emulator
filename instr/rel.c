//
// Created by cst on 10/31/20.
//

#include "rel.h"
#include "cpu.h"

void branch(int condition)
{
    int8_t offset = get_arg(1) + 2;
    if (condition) {
        uint16_t sum = cpu.pcl + offset;
        if (sum > 0xff) cpu.pch += 1;
        cpu.pcl += offset;
        cpu.pcu = 1;
    }
}

void bpl()/* Branch on Result Plus*/
{
    branch(!getsr(7));
}

void bmi() /*Branch on Result Minus*/
{
    branch(getsr(7));
}

void bvc() /*Branch on Overflow Clear*/
{
    branch(!getsr(6));
}

void bvs() /*Branch on Overflow Set*/
{
    branch(getsr(6));
}

void bcc() /*Branch on Carry Clear*/
{
    branch(!getsr(0));
}

void bcs() /*Branch on Carry Set*/
{
    branch(getsr(0));
}

void bne() /*Branch on Result not Zero*/
{
    branch(!getsr(1));
}

void beq() /*Branch on Result Zero*/
{
    branch(getsr(1));
}

