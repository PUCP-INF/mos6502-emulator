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
    timer = al_create_timer(1.0/30.0);
    must_init(timer, "timer");
    queue = al_create_event_queue();
    must_init(queue, "queue");
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
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
}

void run_program()
{
    // end the program once the PC points to null memory
    uint8_t op_ind;
    //como hemos inicializado en 0 todo, cuando llege a 0 entonces parara el bucle
    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;
    ALLEGRO_KEYBOARD_STATE ks;

    al_start_timer(timer);
    float x1 = 0, y1 = 0, x2 = 20, y2 = 20;
    mem.ram[0][0xff] = 0x64;
    while (1) {
        al_wait_for_event(queue, &event);

        if (mem.ram[cpu.pch][cpu.pcl] == 0x00) break;

        switch (event.type) {
            case ALLEGRO_EVENT_TIMER:
                mem.ram[0][0xfe] = rand() % 256;
                op_ind = fetch();
                execute(op_ind);
                fflush(stdout);
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
            ALLEGRO_COLOR black = al_map_rgb_f(0, 0, 0);

            // blanquear posiciones anteriores
            for (int i = 2; i <= 5; ++i) {
                for (int j = 0; j < 256; ++j) {
                    if (mem.ram[i][j] != 0x22) {
                        mem.ram[i][j] = 0;
                    }
                }
            }
            if(mem.ram[0][0x11] ==0x03 && mem.ram[0][0x10] == 0xf1){
                printf("work sbc\n");
            }
            // cabeza
            if (mem.ram[0][0x11] != 0 && mem.ram[0][0x10] != 0) {
                mem.ram[mem.ram[0][0x11]][mem.ram[0][0x10]] = 1;
            }
            // manzana
            if (mem.ram[0][0x1] != 0 && mem.ram[0][0x0] != 0) {
                mem.ram[mem.ram[0][0x1]][mem.ram[0][0x0]] = 0x22;
            }
            char str[3];
            for (int i = 2; i <= 5; ++i) {
                for (int j = 0; j < 256; ++j) {
                    sprintf(str, "%02hhX", mem.ram[i][j]);
                    al_draw_text(font, white, x1, y1, 0, str);
//                    al_draw_filled_rectangle(x1, y1, x2, y2, white);
//                    sprintf(str, "%02hhX", mem.ram[i][j]);
                    if (mem.ram[i][j]) {
//                        al_draw_text(font, white, x1, y1, 0, str);
//                        al_draw_filled_rectangle(x1, y1, x2, y2, white);
                    } else {
                        al_draw_filled_rectangle(x1, y1, x2, y2, black);
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
