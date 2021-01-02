#include "init.h"
#include "cpu.h"
#include "pipeline.h"
#include "debug.h"

#include <stdlib.h>
#include <stdio.h>
#include <gc/gc.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>

#ifdef __MINGW64__
#   include <ncurses/ncurses.h>
#else
#   include <ncurses.h>
#endif

//Ver estrutura del cpu y de la mem
struct CPU6502 cpu;
struct MEM6502 mem;

ALLEGRO_TIMER* timer;
ALLEGRO_EVENT_QUEUE* queue;
ALLEGRO_DISPLAY* disp;

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
    timer = al_create_timer(1.0/1500.0);
    must_init(timer, "timer");
    queue = al_create_event_queue();
    must_init(queue, "queue");
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    disp = al_create_display(640, 640);
    must_init(disp, "display");
    must_init(al_init_primitives_addon(), "primitives");
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
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
    float x1 = 0, y1 = 0, x2 = 20, y2 = 20;
    while (1) {
        al_wait_for_event(queue, &event);

        if (mem.ram[cpu.pch][cpu.pcl] == 0x00) break;

        switch (event.type) {
            case ALLEGRO_EVENT_TIMER:
                mem.ram[0][0xfe] = rand() % 256;
                op_ind = fetch();
                execute(op_ind);
                info_cpu();
                redraw = true;
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

        // $02 - $05
        if(redraw && al_is_event_queue_empty(queue)) {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            ALLEGRO_COLOR white = al_map_rgb_f(1, 1, 1);
            ALLEGRO_COLOR red = al_map_rgb_f(1, 0, 0);

            // blanquear posiciones anteriores
            for (int i = 2; i <= 5; ++i) {
                for (int j = 0; j < 256; ++j) {
                    mem.ram[i][j] = 0;
                }
            }

            // cabeza
            if (mem.ram[0][0x11] != 0 && mem.ram[0][0x10] != 0) {
                mem.ram[mem.ram[0][0x11]][mem.ram[0][0x10]] = 0x23;
            }

            // cuerpo
            uint8_t body = 0x12;
            while (mem.ram[0][body+1] != 0) {
                mem.ram[mem.ram[0][body+1]][mem.ram[0][body]] = 0x23;
                body += 2;
            }

            // manzana
            if (mem.ram[0][0x1] != 0 && mem.ram[0][0x0] != 0) {
                mem.ram[mem.ram[0][0x1]][mem.ram[0][0x0]] = 0x22;
            }

            for (int i = 2; i <= 5; ++i) {
                for (int j = 0; j < 256; ++j) {
                    if (mem.ram[i][j]) {
                        if (mem.ram[i][j] == 0x22) {
                            al_draw_filled_rectangle(x1, y1, x2, y2, red);
                        } else if (mem.ram[i][j] == 0x23){
                            al_draw_filled_rectangle(x1, y1, x2, y2, white);
                        }
                    }
                    if (x2 == 640) {
                        y1 += 20;
                        y2 += 20;
                        x1 = 0;
                        x2 = 20;
                    } else {
                        x1 += 20;
                        x2 += 20;
                    }
                }
            }
            x1 = 0; y1 = 0; x2 = 20; y2 = 20;
            al_flip_display();
            redraw = false;
        }
    }
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    endwin();
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
