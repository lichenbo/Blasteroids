#include "blasteroids.h"
#include "asteroid.h"
#include "blast.h"
#include "spaceship.h"
#include <list>
#include <iostream>
using namespace std;

enum MKEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};

int main() {
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	std::list<Asteroid*> as_list;
	Spaceship *cur_spaceship = NULL;

	bool key[4] = {false, false, false, false};
	bool redraw = true;
	bool doexit = false;

   if(!al_init()) {
      fprintf(stderr, "failed to initialize allegro!\n");
      return -1;
   }

   if(!al_install_keyboard()) {
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
	
	al_set_target_bitmap(al_get_backbuffer(display));

   event_queue = al_create_event_queue();
   if(!event_queue) {
	fprintf(stderr, "failed to create event_queue!\n");
	al_destroy_display(display);
	al_destroy_timer(timer);
	return -1;
   }
 
   al_register_event_source(event_queue, al_get_display_event_source(display));
   al_register_event_source(event_queue, al_get_timer_event_source(timer));
   al_register_event_source(event_queue, al_get_keyboard_event_source());

   al_clear_to_color(al_map_rgb(255,0,0));
 
   al_start_timer(timer);
 
   int old_time = 0;
   int ship_remain = 3;

   if (ship_remain > 0) {
	   cur_spaceship = new Spaceship(); 
   }

   while(!doexit) {
	   ALLEGRO_EVENT ev;
	   al_wait_for_event(event_queue, &ev);
	   cout << al_current_time() << endl;
	   if(ev.type == ALLEGRO_EVENT_TIMER) {
		   int time = al_current_time();
		   /* We create an asteroid every 0.5 seconds */
		   if (time - old_time > 0.5) {
			   Asteroid* as = new Asteroid();
			   as_list.push_back(as);
			   old_time = time;
		   }

		   /* We refresh the screen every timer event activated */
		   std::list<Asteroid*>::iterator i;
		   for(i = as_list.begin(); i != as_list.end(); ++i) {
		      (*i)->update();
			  (*i)->draw();
			  cur_spaceship->update();
			  cur_spaceship->draw();
		   }
		   al_flip_display();
		   al_clear_to_color(al_map_rgb(255,0,0));
	   }
   }
   al_destroy_timer(timer);
   al_destroy_display(display);
   al_destroy_event_queue(event_queue);
   return 0;

}