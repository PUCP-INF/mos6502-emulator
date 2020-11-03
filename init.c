#include "init.h"
#include "cpu.h"
#include "pipeline.h"

#include <stdlib.h>
#include <stdio.h>
#include <gc/gc.h>
//Ver estrutura del cpu y de la mem
struct CPU6502 cpu;
struct MEM6502 mem;

void init_cpu()
{
    /*Simplementa aqui inicializamos la RAM, son 256 paginas con
     * 256 bytes cada una. Todas se ponen en 0*/
    mem.ram = GC_malloc(256 * sizeof(uint8_t));
    // TODO: inicializar stack pointer
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
    //como hemos inicializado en 0 todo, cuando llege a 0 entonces parara el bucle
    while (mem.ram[cpu.pch][cpu.pcl] != 0x00) {
//        print_cpu();
//En el pipeline del 6502 solo tiene 2 etapas que es el fetch y el execute
        op_ind = fetch();
        execute(op_ind);
    }
    print_cpu();
}

/*El load file carga el archivo binario del acme.
 * Ejecutar %hexdump -C test
 * Con ese comando se vera el archivop binario de la compilacion de acme.
 * El archivo principal del ensamblador es el test.s
 * En esas 2 primeras lineas estaran la directiva para el acme y el valor del
 * program counter que le ponemos. Luego ya podremos pobrar el codigo usando el acme.
 * Luego, para compilarlo simplemente hacemos acme test.s y luego hexdump -C test*/
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
    //sacamos el tamanhio
    uint8_t byte, pcl, pch;
    // read program counter
    //Sacamos el program counter del archivo binario generado por el acme
    fread(&pcl, 1, 1, file);
    fread(&pch, 1, 1, file);
    cpu.pcl = pcl;//parte mas significativa
    cpu.pch = pch;//parte menos significativa
    // load program into memory, start on pc
    //Luego de haber cargado el pc, procedemos a cargar los bytes del programa en si
    //en la ram, empezando justo despues del pc
    for (int i = 0; i < size-2; ++i) {
        fread(&byte, 1, 1, file);
        mem.ram[pch][pcl] = byte;
        if (pcl == 0xff) {//condicionales para cambiar de pagina
            pch += 1;
            pcl = 0;
        } else {
            pcl += 1;
        }
    }
    fclose(file);
}

void print_ram()
{
    printf("\n");
    for (int j = 0; j < 256; ++j) {
        printf("%02x ", mem.ram[0][j]);
        if ((j+1) % 16 == 0) printf("\n");
    }
    printf("\n");
}

void print_cpu()
{
    printf("A = %02x\t\tC Z I D B V N\nX = %02x\t\t%d %d %d %d %d %d %d\nY = %02x\n",
           cpu.a, cpu.x,
           getsr(0), getsr(1), getsr(2), getsr(3), getsr(4), getsr(6), getsr(7),
           cpu.y);
    print_ram();
}
//pone las banderas en uno
void setsr(int bit)
{
    cpu.sr |= 1UL << bit;
}

//pone las banderas en 0
void unsetsr(int bit)
{
    cpu.sr &= ~(1UL << bit);
}

int getsr(int bit)
{
    uint8_t sr = cpu.sr;
    return (sr >> bit) & 0x01;
}

uint8_t get_arg(int n)
{   //aumenta en n bytes del pc y te devuelve ese valor de la ram
    uint8_t low = cpu.pcl, high = cpu.pch;
    if ((int)low + n > 0xff) high += 1;
    low += n;
    return mem.ram[high][low];
}