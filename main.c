#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#define ALEATOIRE al_map_rgb(rand()%256, rand()%256, rand()%256)
#define XRAND rand()%800
#define YRAND rand()%600
#define RRAND rand()%50


int main(){
    srand(time(NULL));

    // Declaration
    ALLEGRO_DISPLAY * game_display = NULL;
    ALLEGRO_EVENT_QUEUE * fifo= NULL;
    ALLEGRO_TIMER * game_timer= NULL;

    // Initialisation
    assert(al_init());
    assert(al_init_primitives_addon());
    assert(al_install_keyboard());

    // Creation "al_create
    //al_set_new_display_option(ALLEGRO_SINGLE_BUFFER,1, ALLEGRO_REQUIRE);
    al_set_new_display_flags(ALLEGRO_RESIZABLE);
    game_display = al_create_display(600,800);

    fifo = al_create_event_queue();
    game_timer = al_create_timer(1.0/1.0);

    // sources
    al_register_event_source(fifo, al_get_display_event_source(game_display));
    al_register_event_source(fifo, al_get_timer_event_source(game_timer));
    al_register_event_source(fifo, al_get_keyboard_event_source());

    bool fini = false;
    ALLEGRO_EVENT  event;
    al_flip_display();
    al_start_timer(game_timer);
    while(!fini){
        al_wait_for_event(fifo,&event);

        switch (event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                fini = true;
                break;
            case ALLEGRO_EVENT_TIMER:
                //al_clear_to_color(ALEATOIRE);
                al_flip_display();
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                switch (event.keyboard.keycode) {
                    case ALLEGRO_KEY_T:
                        al_draw_filled_triangle(XRAND, YRAND, XRAND, YRAND, XRAND, YRAND, ALEATOIRE);
                        break;
                    case ALLEGRO_KEY_C:
                        al_draw_filled_circle(XRAND, YRAND, RRAND, ALEATOIRE);
                        break;
                    default:
                        printf("La touche est %s \n", al_keycode_to_name(event.keyboard.keycode));
                        break;
                }
        }

    }

    // liberation
    al_destroy_display(game_display);
    al_destroy_event_queue(fifo);
    al_destroy_timer(game_timer);
    return 0;
}