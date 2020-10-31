#include "init.h"
#include "cpu.h"
#include "pipeline.h"

#include <stdlib.h>
#include <stdio.h>

struct CPU6502 cpu;
struct MEM6502 mem;

void init_cpu()
{
    mem.ram = malloc(256 * sizeof(uint8_t));
    // TODO: inicializar stack pointer
    for (int i = 0; i < 256; ++i) {
        mem.ram[i] = malloc(256 * sizeof(uint8_t));
        for (int j = 0; j < 256; ++j) {
            mem.ram[i][j] = 0;
        }
    }
}

void run_program()
{
    // end the program once the PC points to null memory
    uint8_t op_ind;
    while (mem.ram[cpu.pch][cpu.pcl] != 0x00) {
//        print_cpu();
        op_ind = fetch();
        execute(op_ind);
    }
//    print_cpu();
}

void load_file(const char* filename)
{
    FILE *file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "File %s not found.\n", filename);
        exit(0);
    }
    // get file size
    long size;
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    rewind(file);
    uint8_t byte, pcl, pch;
    // read program counter
    fread(&pcl, 1, 1, file);
    fread(&pch, 1, 1, file);
    cpu.pcl = pcl;
    cpu.pch = pch;
    // load program into memory, start on pc
    for (int i = 0; i < size-2; ++i) {
        fread(&byte, 1, 1, file);
        mem.ram[pch][pcl] = byte;
        if (pcl == 0xff) {
            pch += 1;
            pcl = 0;
        } else {
            pcl += 1;
        }
    }
    fclose(file);
}

void free_cpu()
{
    for (int i = 0; i < 256; ++i) {
        free(mem.ram[i]);
    }
}

void print_ram()
{
//    for (int i = 0; i < 256; ++i) {
//        for (int j = 0; j < 256; ++j) {
//            printf("%02x ", mem.ram[i][j]);
//        }
//        printf("\n");
//    }
    for (int j = 0; j < 256; ++j) {
        printf("%02x ", mem.ram[0][j]);
    }
    printf("\n");
}

void print_cpu()
{
//    uint8_t opcode = mem.ram[cpu.pch][cpu.pcl];
//    printf("%02x\n", opcode);
    printf("A:%02x  X:%02x  Y:%02x\n", cpu.a, cpu.x, cpu.y);
    uint8_t sr = cpu.sr;
    // status register
    printf("carry: %d\n", getsr(0));
    printf("zero: %d\n", getsr(1));
    printf("int: %d\n", getsr(2));
    printf("decimal: %d\n", getsr(3));
    printf("break: %d\n", getsr(4));
    printf("overflow: %d\n", getsr(6));
    printf("negative: %d\n", getsr(7));
    print_ram();
}

void setsr(int bit)
{
    cpu.sr |= 1UL << bit;
}

void unsetsr(int bit)
{
    cpu.sr &= ~(1UL << bit);
}

int getsr(int bit)
{
    uint8_t sr = cpu.sr;
    return (sr >> bit) & 0x01;
}