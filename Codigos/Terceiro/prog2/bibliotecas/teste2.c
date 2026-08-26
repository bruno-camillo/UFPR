#include <allegro5/allegro.h>

int main() {
    al_init();

    ALLEGRO_DISPLAY* display = al_create_display(640, 1024);
    al_clear_to_color(al_map_rgb(100, 0, 200));
    al_flip_display();

    al_rest(5.0);
    al_destroy_display(display);

    return 0;
}
