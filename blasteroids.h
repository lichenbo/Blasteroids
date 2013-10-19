#include <stdio.h>
#include <allegro5\allegro.h>

const float FPS = 60;
const int SCREEN_W = 640;
const int SCREEN_H = 480;
// Serve for keyboard events
enum MKEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_SPACE
};

inline double DEGTORAD(float deg) {
	return deg * 3.14159 / 180;
}