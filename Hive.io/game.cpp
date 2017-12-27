#include <SFML/Graphics.hpp>
#include <iostream>
#include "main.h"
#include "player.h"
#include "controls.h"
#include "camera.h"

int state;

void setState(int flag) {
	state = flag;
	/*
	-1 - Reset/initialize
	0 - PLAYING
	1 - PAUSED
	*/
}

int getState() {
	return state;
}

void updateInputs(sf::Event e) {
	switch (state) {
		case -1:
			break;
		case 0:
			// Checks for new inputs, including pause
			controller(e);
			keyboard(e);
			handle_pause(e);
			break;
		case 1:
			// If paused, resumes game
			handle_pause(e);
			break;
		case 2:
			break;
	}
}

void updateGame() {
	int t = getTime();
	switch (state) {
		case -1:
			init_player(0, 0, 100, 50);
			setState(0);
			break;
		case 0:
			// Updates player variables
			move_player();
			move_target();
			move_bullets();
			move_camera();
			break;
		case 1:
			// if paused
			break;
		case 2:
			break;
	}
}