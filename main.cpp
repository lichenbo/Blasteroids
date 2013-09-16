#include <stdio.h>
#include <allegro5\allegro.h>

const float FPS = 60;

int main() {
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	bool redraw = true;

   if(!al_init()) {
      fprintf(stderr, "failed to initialize allegro!\n");
      return -1;
   }

   timer = al_create_timer(1.0 / FPS);
   if(!timer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
   }
 
   display = al_create_display(640, 480);
   if(!display) {
      fprintf(stderr, "failed to create display!\n");
      return -1;
   }

   event_queue = al_create_event_queue();
   if(!event_queue) {
	fprintf(stderr, "failed to create event_queue!\n");
	al_destroy_display(display);
	al_destroy_timer(timer);
	return -1;
   }
 
   al_register_event_source(event_queue, al_get_display_event_source(display));

   al_clear_to_color(al_map_rgb(255,0,0));
 
   al_flip_display();
 
   while(1) {
		ALLEGRO_EVENT ev;
		ALLEGRO_TIMEOUT timeout;
		al_init_timeout(&timeout, 0.06);

		bool get_event = al_wait_for_event_until(event_queue, &ev, &timeout);

		if(get_event && ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
   
		al_clear_to_color(al_map_rgb(255,0,0));
		al_flip_display();
   
   }
   al_destroy_display(display);
   return 0;

}