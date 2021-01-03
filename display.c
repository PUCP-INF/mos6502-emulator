#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>

#include "display.h"
#include "cpu.h"
#include <stdio.h>
extern ALLEGRO_TIMER* timer;
extern ALLEGRO_EVENT_QUEUE* queue;
extern ALLEGRO_DISPLAY* disp;
extern ALLEGRO_FONT* font;

ALLEGRO_TIMER* timer;
ALLEGRO_EVENT_QUEUE* queue;
ALLEGRO_DISPLAY* disp;
ALLEGRO_FONT* font;

void must_init(bool test, const char *description)
{
    if(test) return;
//    printf("couldn't initialize %s\n", description);
    exit(1);
}

void init_display()
{
    must_init(al_init(), "allegro");
    must_init(al_install_keyboard(), "keyboard");
    timer = al_create_timer(1.0/60.0);
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

void update_snake()
{
    float x1 = 0, y1 = 0, x2 = 20, y2 = 20;
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
    al_flip_display();
}

void update_pong(){
    float x1 = 0, y1 = 0, x2 = 20, y2 = 20;
    al_clear_to_color(al_map_rgb(0, 0, 0));
    ALLEGRO_COLOR white = al_map_rgb_f(1, 1, 1);
    ALLEGRO_COLOR red = al_map_rgb_f(1, 0, 0);

    // blanquear posiciones anteriores
    for (int i = 2; i <= 5; ++i) {
        for (int j = 0; j < 256; ++j) {
            mem.ram[i][j] = 0;
        }
    }

    //PLAYER1
    if (mem.ram[0][0x9] != 0 && mem.ram[0][0x19] != 0) {
        mem.ram[mem.ram[0][0x9]][mem.ram[0][0x19]] = 0x22;
    }

    //PLAYER2
    if (mem.ram[0][0x0a] != 0 && mem.ram[0][0x1a] != 0) {
        mem.ram[mem.ram[0][0x0a]][mem.ram[0][0x1a]] = 0x22;
    }

    //BALL
    if (mem.ram[0][0x8] != 0 || mem.ram[0][0x18] != 0) {
        mem.ram[mem.ram[0][0x8]][mem.ram[0][0x18]] = 0x23;
        //corregir el borde
        if(mem.ram[0][0x8] == 0x02 && mem.ram[0][0x18] <=0x20)mem.ram[0][0xfd] = 1;//up
        //if(mem.ram[0][0x8] == 0x02 && mem.ram[0][0x18] <=0x20)mem.ram[0][0x20] = 0x02;
        if(mem.ram[0][0x8] == 0x05 && mem.ram[0][0x18] >=0xdf)mem.ram[0][0xfd] = 2;//down
        if((mem.ram[0][0x18]-0x1f)%0x20 ==0)mem.ram[0][0xfd] = 4;//right
        if(mem.ram[0][0x18]%0x20 ==0)mem.ram[0][0xfd] = 8;//left
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
    al_flip_display();
}

void update_display()
{
    //update_snake();
    update_pong();
}

void delete_display()
{
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
}