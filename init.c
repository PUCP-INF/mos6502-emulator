#include <stdlib.h>
#include <stdio.h>
#include <gc/gc.h>
#include <time.h>
#include <allegro5/allegro5.h>
#ifdef __MINGW64__
#   include <ncurses/ncurses.h>
#else
#   include <ncurses.h>
#endif

#include "init.h"
#include "cpu.h"
#include "pipeline.h"
#include "debug.h"
#include "display.h"

extern ALLEGRO_TIMER* timer;
extern ALLEGRO_EVENT_QUEUE* queue;

//Ver estrutura del cpu y de la mem
struct CPU6502 cpu;
struct MEM6502 mem;

void end_cpu()
{
    delete_display();
    endwin();
}

void init_cpu()
{
    srand(time(NULL));
    /*Simplementa aqui inicializamos la RAM, son 256 paginas con
     * 256 bytes cada una. Todas se ponen en 0*/
    mem.ram = GC_malloc(256 * sizeof(uint8_t));
    cpu.sp = 0xff;
    for (int i = 0; i < 256; ++i) {
        mem.ram[i] = GC_malloc(256 * sizeof(uint8_t));
        for (int j = 0; j < 256; ++j) {
            mem.ram[i][j] = 0;
        }
    }
    initscr();
    curs_set(0);
}

void run_program()
{
    // end the program once the PC points to null memory
    uint8_t op_ind;
    //como hemos inicializado en 0 todo, cuando llege a 0 entonces parara el bucle
    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;

    al_start_timer(timer);
    while (1) {
        al_wait_for_event(queue, &event);

        if (mem.ram[cpu.pch][cpu.pcl] == 0x00) break;

        switch (event.type) {
            case ALLEGRO_EVENT_TIMER:
                mem.ram[0][0xfe] = rand() % 256;
                op_ind = fetch();
                execute(op_ind);
                info_cpu();
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                if (event.keyboard.keycode == ALLEGRO_KEY_W)
                    mem.ram[0][0xff] = 0x77;
                else if (event.keyboard.keycode == ALLEGRO_KEY_A)
                    mem.ram[0][0xff] = 0x61;
                else if (event.keyboard.keycode == ALLEGRO_KEY_S)
                    mem.ram[0][0xff] = 0x73;
                else if (event.keyboard.keycode == ALLEGRO_KEY_D)
                    mem.ram[0][0xff] = 0x64;
                break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
        }

        if (done) break;
    }
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
