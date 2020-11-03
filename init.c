#include "init.h"
#include "cpu.h"
#include "pipeline.h"
#include "debug.h"

#include <stdlib.h>
#include <stdio.h>
#include <gc/gc.h>

struct CPU6502 cpu;
struct MEM6502 mem;

void init_cpu()
{
    mem.ram = GC_malloc(256 * sizeof(uint8_t));
    cpu.sp = 0xff;
    for (int i = 0; i < 256; ++i) {
        mem.ram[i] = GC_malloc(256 * sizeof(uint8_t));
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
        op_ind = fetch();
        execute(op_ind);
    }
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
