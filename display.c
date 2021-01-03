#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <stdio.h>
#include <math.h>

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

void update_score()
{
    mem.ram[0][0xf0]++;
    // each apple adds operation overhead, increase game timer to keep game speed constant
    double timersp = pow(al_get_timer_speed(timer), -1) + 200;
    al_set_timer_speed(timer, 1 / timersp);
}

void init_display()
{
    al_init();
    al_install_keyboard();
    timer = al_create_timer(1.0/1000.0);
    queue = al_create_event_queue();
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    disp = al_create_display(640, 650);
    font = al_create_builtin_font();
    al_init_primitives_addon();
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

    // puntaje
    char snum[30];
    sprintf(snum, "Puntaje: %d", mem.ram[0][0xf0] * 100);
    al_draw_text(font, white, 0, 640, 0, snum);

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
        if(mem.ram[0][0x8] == 0x02 && mem.ram[0][0x18] <=0x20)mem.ram[0][0xfd] = 1;//up
        if(mem.ram[0][0x8] == 0x05 && mem.ram[0][0x18] >=0xdf)mem.ram[0][0xfd] = 2;//down
        if((mem.ram[0][0x18]-0x1f)%0x20 ==0)mem.ram[0][0xfd] = 4;//right
        if(mem.ram[0][0x18]%0x20 ==0)mem.ram[0][0xfd] = 8;//left
    }

    if((mem.ram[0][0x18]-0x1d)%0x20 ==0)mem.ram[0x00][0x06]+=0x01;
    char text[30];
    sprintf(text,"el puntaje es : %d",mem.ram[0x00][0x06]);
    al_draw_text(font, al_map_rgb(255, 255, 255), 260, 640, 0, text);
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