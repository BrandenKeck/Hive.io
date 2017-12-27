#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "resource.h"
#include "game.h"
#include "player.h"

int t = 0;
float r = 0;
std::vector<float> w;

int getTime() {
	return t;
}

void set_window(float w_x, float w_y) {
	w.clear();
	w.push_back(w_x);
	w.push_back(w_y);
}

int main() {

	setState(-1);

	sf::VideoMode mode = sf::VideoMode::getDesktopMode();
	sf::RenderWindow window(sf::VideoMode(mode.width, mode.height), "Hive.io");
	set_window(mode.width, mode.height);

	sf::Texture Memnon, Target;
	Memnon.loadFromFile("../img/sprite/memnon/stencil.png");
	Target.loadFromFile("../img/sprite/memnon/scope.png");

	sf::Sprite s_Memnon, s_Target;
	s_Memnon.setTexture(Memnon);
	s_Target.setTexture(Target);

	while (window.isOpen()) {

		// Controls and Event Handling
		sf::Event e;
		while (window.pollEvent(e)) {
			if (e.type == sf::Event::Closed) {
				window.close();
			}
			if (e.type == sf::Event::Resized) {
				double w = e.size.width;
				double h = e.size.height;
				set_window(w, h);
			}
			if (e.type == sf::Event::LostFocus) {
				int s = getState();
				if (s == 0) {
					setState(1);
				}
			}
			if (e.type == sf::Event::GainedFocus) {

				// Maybe use, probably not

			}

			updateInputs(e);
		}
		 
		// Re-render
		window.clear();

		// Handle time-steps
		t += 1;
		if (t > 600) {
			t = 0;
		}

		// DRAW MAP HERE

		// Projectile Drawings
		std::vector<std::vector<float>> b = get_bullets();
		std::vector<sf::Sprite> s_Projectile = get_bsprites();
		int n = b.size();
		for (int i = 0; i < n; i++) {
			s_Projectile[i].setPosition(b[i][1], b[i][2]);
			window.draw(s_Projectile[i]);
		}

		// Player Drawn
		window.draw(s_Memnon);
		double x = get_x();
		double y = get_y();
		s_Memnon.setPosition(x, y);

		// Player Target Drawn
		window.draw(s_Target);
		double tx = get_tx();
		double ty = get_ty();
		s_Target.setPosition(tx, ty);
		s_Target.setOrigin(50, 50);
		if (t % 5 == 0) {
			s_Target.setRotation(r++);
		}

		updateGame();
		window.display();
	}
}

std::vector<float> get_window() {
	return w;
}