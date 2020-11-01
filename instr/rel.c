//
// Created by cst on 10/31/20.
//

#include "rel.h"
#include "cpu.h"

void bpl()/* Branch on Result Plus*/
{
    int8_t offset = get_arg(1);
    if (!getsr(7)) {
        cpu.pcl += offset;
        if (offset < 0) {
            cpu.pcl -= 2;
        }
    }
}

void bmi() /*Branch on Result Minus*/
{
    int8_t offset = get_arg(1);
    if (getsr(7)) {
        cpu.pcl += offset;
        if (offset < 0) {
            cpu.pcl -= 2;
        }
    }

}

void bvc() /*Branch on Overflow Clear*/
{
    int8_t offset = get_arg(1);
    if (!getsr(6)) {
        cpu.pcl += offset;
        if (offset < 0) {
            cpu.pcl -= 2;
        }
    }
}

void bvs() /*Branch on Overflow Set*/
{
    int8_t offset = get_arg(1);
    if (getsr(6)) {
        cpu.pcl += offset;
        if (offset < 0) {
            cpu.pcl -= 2;
        }
    }
}

void bcc() /*Branch on Carry Clear*/
{
    int8_t offset = get_arg(1);
    if (!getsr(0)) {
        cpu.pcl += offset;
        if (offset < 0) {
            cpu.pcl -= 2;
        }
    }
}

void bcs() /*Branch on Carry Set*/
{
    int8_t offset = get_arg(1);
    if (getsr(0)) {
        cpu.pcl += offset;
        if (offset < 0) {
            cpu.pcl -= 2;
        }
    }
}

void bne() /*Branch on Result not Zero*/
{
    int8_t offset = get_arg(1);
    if (!getsr(1)) {
        cpu.pcl += offset;
        if (offset < 0) {
            cpu.pcl -= 2;
        }
    }
}

void beq() /*Branch on Result Zero*/
{
    setsr(1);
    int8_t offset = get_arg(1);
    if (getsr(1)) {
        cpu.pcl += offset;
        if (offset < 0) {
            cpu.pcl -= 2;
        }
    }


}

