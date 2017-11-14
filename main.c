#include "draw.h"

int main() 
{
    ALLEGRO_BITMAP *bitmap;
    ALLEGRO_EVENT_QUEUE *eventQueue;
    ALLEGRO_DISPLAY *display;
    int width = 800;
    int height = 600;
    double x = -2.0;
    double y = -1.0;
    double step = 3.0/width;
    if(!al_init())
    {
        fprintf(stderr, "al_init() failed. Exiting.\n");
        return 1;
    }
    al_set_app_name("Mandelbrot");
    if(!al_install_keyboard())
    {
        fprintf(stderr, "al_install_keyboard() failed. Exiting.\n");
        return 1;
    }
    if(!al_install_mouse())
    {
        fprintf(stderr, "al_install_mouse() failed. Exiting.\n");
        return 1;
    }
    bitmap = al_create_bitmap(width, height);
    if (!bitmap)
    {
        fprintf(stderr, "Bitmap initialization failed. Exiting.");
        return 1;
    }
    eventQueue = al_create_event_queue();
    if (!eventQueue)
    {
        fprintf(stderr, "Event queue initialization failed. Exiting.");
        al_destroy_bitmap(bitmap);
        return 1;
    }
    display = al_create_display(width, height);
    if (!display)
    {
        fprintf(stderr, "Display initialization failed. Exiting.");
        al_destroy_event_queue(eventQueue);
        al_destroy_bitmap(bitmap);
        return 1;
    }
    al_register_event_source(eventQueue, al_get_keyboard_event_source());
    al_register_event_source(eventQueue, al_get_mouse_event_source());
    al_register_event_source(eventQueue, al_get_display_event_source(display));
    al_set_target_bitmap(al_get_backbuffer(display));
    draw(bitmap, width, height, x, y, step);
    printf("x: <%f, %f> y: <%f, %f>\n", x, x + step * width, y, y + step * height);
    while(1)
    {
        ALLEGRO_EVENT event;
        al_wait_for_event(eventQueue, &event);
        if ((event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) || event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            al_destroy_event_queue(eventQueue);
            al_destroy_bitmap(bitmap);
            al_destroy_display(display);
            return 0;
        }
        else if (event.type == ALLEGRO_EVENT_KEY_DOWN && event.keyboard.keycode == ALLEGRO_KEY_R)
        {
            x = -2.0;
            y = -1.0;
            step = 3.0/width;
            draw (bitmap, width, height, x, y, step);
            printf("x: <%f, %f> y: <%f, %f>\n", x, x + step * width, y, y + step * height);
        }
        else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            ALLEGRO_MOUSE_STATE state;
            al_get_mouse_state(&state);
            if (state.buttons & 1)
            {
                x += event.mouse.x * step;
                y += (height - event.mouse.y) * step;
                step /= 2.0;
                x -= step * (width >> 1);
                y -= step * (height >> 1);
                draw (bitmap, width, height, x, y, step);
                printf("x: <%f, %f> y: <%f, %f>\n", x, x + step * width, y, y + step * height);
            }
            else if (state.buttons & 2)
            {
                x -= step * width / 2.0;
                y -= step * height / 2.0;
                step *= 2;
                draw (bitmap, width, height, x, y, step);  
                printf("x: <%f, %f> y: <%f, %f>\n", x, x + step * width, y, y + step * height);
            }
        }
    }
}