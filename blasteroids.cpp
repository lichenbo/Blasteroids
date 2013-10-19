#include "blasteroids.h"
#include "asteroid.h"
#include "blast.h"
#include "spaceship.h"
#include <list>
#include <iostream>
using namespace std;


int main() {
	/* Maintained for the global environment of the game */
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	// linkedlist of the asteroids which are still on the screen
	std::list<Asteroid*> asteroids_list;
	// pointer to the current spaceship
	Spaceship *cur_spaceship = NULL;
	// linkedlist of blasts which are still on the screen
	std::list<Blast*> blasts_list;

	bool key[5] = {false, false, false, false, false};
	bool doexit = false;

	/* initialization: output is comment */
   if(!al_init()) {
      fprintf(stderr, "failed to initialize allegro!\n");
      return -1;
   }

   if(!al_install_keyboard()) {
		fprintf(stderr, "failed to initialize keyboard!\n");
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
   
   // to draw on display
   al_set_target_bitmap(al_get_backbuffer(display));

   event_queue = al_create_event_queue();
   if(!event_queue) {
	fprintf(stderr, "failed to create event_queue!\n");
	al_destroy_display(display);
	al_destroy_timer(timer);
	return -1;
   }
 
   // register event source
   al_register_event_source(event_queue, al_get_display_event_source(display));
   al_register_event_source(event_queue, al_get_timer_event_source(timer));
   al_register_event_source(event_queue, al_get_keyboard_event_source());


   // begin to work
   al_clear_to_color(al_map_rgb(255,0,0));
 
   al_start_timer(timer);
 
   // old_time for watching the appication clock, should be running till the program ends
   int old_time = 0;
   // ship_remain in total
   int ship_remain = 3;

   // create a ship
   if (ship_remain > 0) {
	   cur_spaceship = new Spaceship(); 
   }

   /* main loop */
   while(!doexit) {
	   ALLEGRO_EVENT ev;
	   al_wait_for_event(event_queue, &ev);
	   cout << al_current_time() << endl;	// console log for time
	   // <TIMER>
	   if(ev.type == ALLEGRO_EVENT_TIMER) {
		   
		   // <Asteroids>
		   int time = al_current_time();
		   /* We create an asteroid every 0.5 seconds */
		   if (time - old_time > 0.5) {
			   Asteroid* as = new Asteroid();
			   asteroids_list.push_back(as);
			   old_time = time;
		   }

		   /* We refresh the screen every timer event activated */
		   std::list<Asteroid*>::iterator i;
		   for(i = asteroids_list.begin(); i != asteroids_list.end(); ++i) {
		      (*i)->update();
			  (*i)->collisionDetect(cur_spaceship, blasts_list);
			  (*i)->draw();
		   }
		   // </Asteroids>

		   // <Spaceship>
		   cur_spaceship->update(key);
		   cur_spaceship->draw();
		   // </Spaceship>

		   al_flip_display();
		   al_clear_to_color(al_map_rgb(255,0,0));
	   }
	   // </TIMER>

	   // <KEYBOARD>
	   else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
		   switch(ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
                key[KEY_UP] = true;
                break;
 
            case ALLEGRO_KEY_DOWN:
               key[KEY_DOWN] = true;
               break;
 
            case ALLEGRO_KEY_LEFT: 
               key[KEY_LEFT] = true;
               break;
 
            case ALLEGRO_KEY_RIGHT:
               key[KEY_RIGHT] = true;
               break;
			
			case ALLEGRO_KEY_SPACE:
				key[KEY_SPACE] = true;
				break;

            case ALLEGRO_KEY_ESCAPE:
               doexit = true;
               break; 
		   }

	   }
	   else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
		   switch(ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
                key[KEY_UP] = false;
                break;
 
            case ALLEGRO_KEY_DOWN:
               key[KEY_DOWN] = false;
               break;
 
            case ALLEGRO_KEY_LEFT: 
               key[KEY_LEFT] = false;
               break;
 
            case ALLEGRO_KEY_RIGHT:
               key[KEY_RIGHT] = false;
               break;
			
			case ALLEGRO_KEY_SPACE:
				key[KEY_SPACE] = false;
				break;
		   }
	   }
   }
   al_destroy_timer(timer);
   al_destroy_display(display);
   al_destroy_event_queue(event_queue);
   return 0;

}