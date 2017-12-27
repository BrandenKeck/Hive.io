#include <SFML/Graphics.hpp>
#include <iostream>
#include "game.h"
#include "player.h"

bool trigger_reset = true;

void controller(sf::Event e) {
	if (sf::Joystick::isConnected(0)) {
		sf::Vector2f jMove = sf::Vector2f(0.f, 0.f);
		sf::Vector2f jTarget = sf::Vector2f(0.f, 0.f);
		float jShake;
		switch (e.type) {
			case sf::Event::JoystickMoved:
				jMove = sf::Vector2f(sf::Joystick::getAxisPosition(0, sf::Joystick::X), sf::Joystick::getAxisPosition(0, sf::Joystick::Y));
				jTarget = sf::Vector2f(sf::Joystick::getAxisPosition(0, sf::Joystick::U), sf::Joystick::getAxisPosition(0, sf::Joystick::R));
				jShake = sf::Joystick::getAxisPosition(0, sf::Joystick::Z);

				set_accl_x((jMove.x / 10000));
				set_accl_y((jMove.y / 10000));

				set_vel_tx((jTarget.x/20));
				set_vel_ty((jTarget.y/20));

				//ADD JSHAKE

				break;
			case sf::Event::JoystickButtonPressed:
				switch (e.joystickButton.button) {
					case 0:
						std::cout << "A" << std::endl;
						break;
					case 1:
						std::cout << "B" << std::endl;
						break;
					case 2:
						std::cout << "X" << std::endl;
						break;
					case 3:
						std::cout << "Y" << std::endl;
						break;
					case 4:
						if (trigger_reset) {
							create_projectile();
							trigger_reset = false;
						}
						break;
					case 5:
						std::cout << "Heal" << std::endl;
						break;
				}
				break;
			case sf::Event::JoystickButtonReleased:
				switch (e.joystickButton.button) {
					case 0:
						std::cout << "A" << std::endl;
						break;
					case 1:
						std::cout << "B" << std::endl;
						break;
					case 2:
						std::cout << "X" << std::endl;
						break;
					case 3:
						std::cout << "Y" << std::endl;
						break;
					case 4:
						trigger_reset = true;
						break;
					case 5:
						std::cout << "Heal" << std::endl;
						break;
				}
				break;
		}
		sf::Joystick::update();
	}
}

void keyboard(sf::Event e) {
	if (!sf::Joystick::isConnected(0)) {
		switch (e.type) {
			case sf::Event::MouseMoved:
					set_tx(e.mouseMove.x - 100);
					set_ty(e.mouseMove.y - 100);
				break;
			case sf::Event::MouseButtonPressed:
				switch (e.key.code) {
					case sf::Mouse::Left:
						std::cout << "Left Click" << std::endl;
						break;
					case sf::Mouse::Right:
						std::cout << "Right Click" << std::endl;
						break;
				}
				break;
			case sf::Event::MouseButtonReleased:
				switch (e.key.code) {
					case sf::Mouse::Left:
						std::cout << "Left Click" << std::endl;
						break;
					case sf::Mouse::Right:
						std::cout << "Right Click" << std::endl;
						break;
				}
				break;
			case sf::Event::KeyPressed:
				switch (e.key.code) {
					case sf::Keyboard::W:
						set_accl_y(-0.01);
						break;
					case sf::Keyboard::A:
						set_accl_x(-0.01);
						break;
					case sf::Keyboard::S:
						set_accl_y(0.01);
						break;
					case sf::Keyboard::D:
						set_accl_x(0.01);
						break;
					case sf::Keyboard::Num1:
						std::cout << "1" << std::endl;
						break;
					case sf::Keyboard::Num2:
						std::cout << "2" << std::endl;
						break;
					case sf::Keyboard::Num3:
						std::cout << "3" << std::endl;
						break;
					case sf::Keyboard::Num4:
						std::cout << "4" << std::endl;
						break;
				}
				break;
			case sf::Event::KeyReleased:
				switch (e.key.code) {
					case sf::Keyboard::W:
						set_accl_y(0);
						break;
					case sf::Keyboard::A:
						set_accl_x(0);
						break;
					case sf::Keyboard::S:
						set_accl_y(0);
						break;
					case sf::Keyboard::D:
						set_accl_x(0);
						break;
					case sf::Keyboard::Num1:
						std::cout << "1" << std::endl;
						break;
					case sf::Keyboard::Num2:
						std::cout << "2" << std::endl;
						break;
					case sf::Keyboard::Num3:
						std::cout << "3" << std::endl;
						break;
					case sf::Keyboard::Num4:
						std::cout << "4" << std::endl;
						break;
				}
				break;
		}
	}
}

// Pausing function.  Consider revising this.
void handle_pause(sf::Event e) {
	int state = getState();
	if (sf::Joystick::isConnected(0)) {
		switch (e.type) {
		case sf::Event::JoystickButtonPressed:
			if (e.joystickButton.button == 7) {
				if (state != 1) {
					setState(1);
					std::cout << "PAUSED" << std::endl;
				}
				else { setState(0); }
			}
			break;
		}
	}
	else {
		switch (e.type) {
		case sf::Event::KeyPressed:
			if (e.key.code == sf::Keyboard::Escape) {
				if (state != 1) {
					setState(1); 
					std::cout << "PAUSED" << std::endl;
				}
				else { setState(0); }
			}
			break;
		}
	}
}