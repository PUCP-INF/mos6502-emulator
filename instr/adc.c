//
// Created by cst on 10/31/20.
//

#include "adc.h"
#include "cpu.h"

void adcxind()
{
    uint8_t dm=get_arg(1)+cpu.x;
    uint8_t high=mem.ram[0][dm+1];
    uint8_t low=mem.ram[0][dm];
    cpu.a=cpu.a+mem.ram[high][low];
    if(getsr(0)){
        cpu.a=cpu.a+1;
    }
    if(!cpu.a)//Analizamos el 0 flag
        setsr(1);
    else
        unsetsr(1);

    if(cpu.a & 0b10000000)//Analizamos el negative flag
        setsr(7);
    else
        unsetsr(7);

    if(cpu.a<0)unsetsr(0);  // flag C
    else setsr(0);

    if(256-mem.ram[high][low]>cpu.a)setsr(6);       //OJITO
}

void adczpg()
{}

void adcimm()
{/*Para esta instruccion se tendra que sumar 1 al acumulador en caso el flag de
 * C(acarreo) tenga el bit encendido. En caso no lo sea, no agregamos nada*/
    uint8_t auxiliar = get_arg(1);//tomamos el valor inmmediato
    cpu.a += auxiliar;//le agregamos ese valor al acumulador
    //verificamos el carry
    if (getsr(0)) {
        cpu.a++;
    }
    //luego tendremos que verificar las 4 banderas(N,Z,C,V)
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
    //Bandera de carry(C)

    if (getsr(0)){
        setsr(0);
    }else{
        unsetsr(0);
    }
    //Bandera de overflow(V)
    if(cpu.a > 256)setsr(6);//bandera del overflow

}

void adcabs()
{
    uint8_t low, high;
    low=get_arg(1);
    high=get_arg(2);
    cpu.a=cpu.a+mem.ram[high][low];
    if(getsr(0)){
        cpu.a=cpu.a+1;
    }
    if(!cpu.a)//Analizamos el 0 flag
        setsr(1);
    else
        unsetsr(1);

    if(cpu.a & 0b10000000)//Analizamos el negative flag
        setsr(7);
    else
        unsetsr(7);

    if(256-mem.ram[high][low]>cpu.a)setsr(6);       //OJITO

}

void adcindy()
{
    uint8_t dm = get_arg(1);

    uint8_t high=mem.ram[0][dm+1];
    uint8_t low=mem.ram[0][dm];
    uint16_t offset =(high<<8)+low+cpu.y;
    cpu.a=cpu.a+mem.ram[offset>>8][offset & 0XFF];
    if(getsr(0)){
        cpu.a=cpu.a+1;
    }
    if(!cpu.a)//Analizamos el 0 flag
        setsr(1);
    else
        unsetsr(1);

    if(cpu.a & 0b10000000)//Analizamos el negative flag
        setsr(7);
    else
        unsetsr(7);

    if(256-mem.ram[high][low]>cpu.a)setsr(6);       //OJITO
}

void adczpgx()
{}

void adcabsy()
{
    uint8_t memory = mem.ram[get_arg(2)][get_arg(1)];
    //Se agrega al acumulador el valor de la memoria y tambien el valor del registro Y
    cpu.a=cpu.a+memory + cpu.y;
    if(getsr(0)){
        cpu.a=cpu.a+1;//en caso tenga el carry
    }
    //Bandera 0 (Z).
    if(!cpu.a)
        setsr(1);
    else
        unsetsr(1);

    //Bandera negativo (N).
    if(cpu.a & 0b10000000)//Analizamos el negative flag
        setsr(7);
    else
        unsetsr(7);
    //Bandera de carry(C)

    if (getsr(0)){
        setsr(0);
    }else{
        unsetsr(0);
    }
    //Bandera de overflow(V)
    if(cpu.a > 256)setsr(6);//bandera del overflow
}

void adcabsx()
{
    uint16_t offset;
    uint8_t low = get_arg(1);
    uint8_t high = get_arg(2);
    offset = (high*256)+low+cpu.x;
    high = offset/256;
    low = offset%256;
    cpu.a=cpu.a+mem.ram[high][low];
    if(getsr(0)){
        cpu.a=cpu.a+1;
    }
    if(!cpu.a)//Analizamos el 0 flag
        setsr(1);
    else
        unsetsr(1);

    if(cpu.a & 0b10000000)//Analizamos el negative flag
        setsr(7);
    else
        unsetsr(7);

    if(256-mem.ram[high][low]>cpu.a)setsr(6);       //OJITO
}