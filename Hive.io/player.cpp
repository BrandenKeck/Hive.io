#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>
#include <iostream>

#define M_PI 3.14159265358979323846

double p_h, p_e, p_x, p_y, p_dx, p_dy, p_dx2, p_dy2;
double t_x, t_y, t_dx, t_dy;
std::vector< std::vector<float> > bullets;
std::vector<sf::Sprite> s_Projectile;

void init_player(double init_x, double init_y, double init_h, double init_e) {
	// Player Variables
	p_h = init_h;
	p_e = init_e;
	p_x = init_x;
	p_y = init_y;

	// Player Movement
	p_dx = 0;
	p_dy = 0; 
	p_dx2 = 0;
	p_dy2 = 0;

	// Player Targeting
	t_x = p_x+25;
	t_y = p_y+25;
}

void create_projectile() {
	double vel = 10;
	double del_x = ((t_x+50)-(p_x+75));
	double del_y = ((t_y + 50) - (p_y + 75));
	double angle = atan((del_y)/(del_x));
	if (del_x < 0) {
		angle += M_PI;
	}


	std::cout << angle << std::endl;

	std::vector<float> new_b;
	new_b.push_back(true);
	new_b.push_back(p_x + 75);
	new_b.push_back(p_y + 75);
	new_b.push_back(vel*cos(angle));
	new_b.push_back(vel*sin(angle));

	bullets.push_back(new_b);


	sf::Texture Projectile;
	Projectile.loadFromFile("../img/sprite/memnon/projectile.png");
	sf::Sprite _s;
	_s.setTexture(Projectile);
	s_Projectile.push_back(_s);
}

// Change position based on acceleration
void move_player() {
	p_dx += p_dx2;
	p_dy += p_dy2;
	p_x += p_dx;
	p_y += p_dy;
}

void move_target() {
	t_x += t_dx;
	t_y += t_dy;
}

void move_bullets() {
	int n = bullets.size();
	for (int i=0;i<n;i++) {
		if (bullets[i][0]) {
			bullets[i][1] += bullets[i][3];
			bullets[i][2] += bullets[i][4];
		}
	}
}

void set_accl_x(double ax) {
	// X direction
	if (p_dx2 == 0) { p_dx2 += ax; }
	else if (p_dx2 > 0 && p_dx2 < 0.1) {
		p_dx2 += ax;
	}
	else if (p_dx2 > -0.1 && p_dx2 < 0) {
		p_dx2 += ax;
	}
	else if (p_dx2 >= 0.1) {
		p_dx2 += 0 - p_dx2;
	}
	else if (p_dx2 <= -0.1) {
		p_dx2 += 0-p_dx2 ;
	}

	p_dx2 = p_dx2 / 10;
}

void set_accl_y(double ay) {
	// Y direction
	if (p_dy2 == 0) { p_dy2 += ay; }
	if (p_dy2 > 0 && p_dy2 < 0.1) {
		p_dy2 += ay;
	}
	else if (p_dy2 > -0.1 && p_dy2 < 0) {
		p_dy2 += ay;
	}
	else if (p_dy2 >= 0.1) {
		p_dy2 += 0 - p_dy2;
	}
	else if (p_dy2 <= -0.1) {
		p_dy2 += 0 - p_dy2;
	}

	p_dy2 = p_dy2 / 10;
}

void set_vel_tx(double vtx) {
	t_x += vtx;
}

void set_vel_ty(double vty) {
	t_y += vty;
}

void set_tx(double tx) {
	t_x = tx;
}

void set_ty(double ty) {
	t_y = ty;
}


double get_x() {
	return p_x;
}

double get_y() {
	return p_y;
}

double get_tx() {
	return t_x;
}

double get_ty() {
	return t_y;
}

std::vector<std::vector<float>> get_bullets() {
	return bullets;
}

std::vector<sf::Sprite> get_bsprites() {
	return s_Projectile; 
}