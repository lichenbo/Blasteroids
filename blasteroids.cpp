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
   al_init_font_addon();
   al_init_ttf_addon();
   ALLEGRO_FONT* font24 = al_load_font("arial.ttf", 24, 0);
   al_clear_to_color(al_map_rgb(255,0,0));
 
   al_start_timer(timer);
 
   // ship_remain in total
   int ship_remain = 3;
   int score = 0;


   /* main loop */
   while(!doexit && ship_remain >= 0) {
	   if (cur_spaceship == NULL) {
		   cur_spaceship = new Spaceship();
	   }
	   assert(cur_spaceship != NULL);

	   ALLEGRO_EVENT ev;
	   al_wait_for_event(event_queue, &ev);
	   // <TIMER>
	   if(ev.type == ALLEGRO_EVENT_TIMER) {
		   
		   ALLEGRO_TRANSFORM transform;
		   al_identity_transform(&transform);
		   al_use_transform(&transform);
		   // <Stat>
		   al_draw_textf(font24, al_map_rgb(0,0,0),0,0,ALLEGRO_ALIGN_LEFT,"Life Remaining: %d",ship_remain);
		   // </Stat>
		   
		   // <Asteroids>
		   float time = al_current_time();
		   // old_time for watching the appication clock, should be running till the program ends
		   static float old_time = 0;
		   /* We create an asteroid every 1.0 seconds */
		   if (time - old_time > 1.0) {
			   Asteroid* as = new Asteroid(1);
			   asteroids_list.push_back(as);
			   old_time = time;
		   }

		   /* We refresh the screen every timer event activated */
		   std::list<Asteroid*>::iterator i;
		   for(i = asteroids_list.begin(); i != asteroids_list.end();) {
		      (*i)->update();
			  (*i)->collisionDetect(cur_spaceship, asteroids_list);
			  (*i)->draw();
			  if ((*i)->isGone()) {
				  Asteroid* delAsteroid = *i;
				  asteroids_list.erase(i++);
				  delete delAsteroid;
				  delAsteroid = NULL;
			  } else {
				i++;
			  }
		   }
		   // </Asteroids>

		   // <Spaceship>
		   cur_spaceship->update(key);
		   cur_spaceship->draw();
		   // </Spaceship>

		   // <Blast>
		   // Blast is a child of spaceship, so the spaceship will update it and draw it
		   // </Blast>

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

	   if (cur_spaceship->isGone()) {
		   delete cur_spaceship;
		   cout << "Died!" << endl;
		   cur_spaceship = NULL;
		   ship_remain--;
	   }
   }
   al_destroy_timer(timer);
   al_destroy_display(display);
   al_destroy_event_queue(event_queue);
   return 0;

}