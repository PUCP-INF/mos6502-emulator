#include "init.h"
#include "cpu.h"
#include "pipeline.h"
#include "debug.h"

#include <stdlib.h>
#include <stdio.h>
#include <gc/gc.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

//Ver estrutura del cpu y de la mem
struct CPU6502 cpu;
struct MEM6502 mem;

ALLEGRO_TIMER* timer;
ALLEGRO_EVENT_QUEUE* queue;
ALLEGRO_DISPLAY* disp;
ALLEGRO_FONT* font;

void must_init(bool test, const char *description)
{
    if(test) return;
    printf("couldn't initialize %s\n", description);
    exit(1);
}

void init_display()
{
    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");
    timer = al_create_timer(1.0);
    must_init(timer, "timer");
    queue = al_create_event_queue();
    must_init(queue, "queue");
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);
    disp = al_create_display(640, 640);
    font = al_create_builtin_font();
    must_init(disp, "display");
    must_init(al_init_primitives_addon(), "primitives");
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
}

void init_cpu()
{
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

        if (mem.ram[cpu.pch][cpu.pcl] == 0x00) done = true;

        switch (event.type) {
            case ALLEGRO_EVENT_TIMER:
                op_ind = fetch();
                execute(op_ind);
                redraw = true;
                break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
        }

        if (done) break;

        if(redraw && al_is_event_queue_empty(queue)) {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            char snum[100];
            sprintf(snum, "%d", mem.ram[0][0]);
            al_draw_text(font, al_map_rgb(255, 255, 255), 0, 0, 0, snum);
            al_flip_display();
            redraw = false;
        }
    }
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
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
