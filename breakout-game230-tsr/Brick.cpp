#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

#include "Brick.h"



Brick::Brick()
{
}


Brick::Brick(bool ohb, bool invis, float x, float y, int sw, int sh, int l, Ball * b, Score * s) {

	ball = b;
	score = s;
	one_hit_brick = ohb;
	invisible = invis;
	if (!invis) {
		brick.setOutlineColor(Color::Black);
		brick.setOutlineThickness(2);
		coke_tex.loadFromFile("coke.jpg");
	}
	if (ohb) {
		lives = 1;
	}
	else if (invis) {
		lives = 2;
		invisible_tex.loadFromFile("Transparent.png");
	}
	else {
		lives = l;
	}
	brick_width = sw / 10;
	brick_height = brick_width / 2;
	brick.setPosition(Vector2f(x, y));
	brick.setSize(Vector2f(brick_width, brick_height));
	buff2.loadFromFile("coinhit.ogg");
	brick_hit.setBuffer(buff2);
	buff1.loadFromFile("cointoss.ogg");
	brick_break.setBuffer(buff1);

}


Brick::~Brick()
{
}

void Brick::update(float dt)
{
	Vector2f pos = brick.getPosition();
	Vector2f ballPos = ball->getPosition();
	int radius = ball->getRadius();
	if (ballPos.x + radius >= pos.x &&
		ballPos.x - radius <= pos.x &&
		ballPos.y >= pos.y &&
		ballPos.y <= pos.y + brick_height) {
		ball->setPosition(pos.x - radius, ballPos.y);
		lives--;
		if (invisible) {
			brick.setTexture(NULL);
			one_hit_brick = true;
			invisible = false;
		}
		if (lives > 0) {
			brick_hit.play();
		}
		else {
			brick_break.play();
		}
		ball->reverseX();
		score->increase_score();
	}
	if (ballPos.x - radius <= pos.x + brick_width &&
		ballPos.x + radius >= pos.x + brick_width &&
		ballPos.y >= pos.y &&
		ballPos.y <= pos.y + brick_height) {
		ball->setPosition(pos.x + brick_width + radius, ballPos.y);
		lives--;
		if (invisible) {
			brick.setTexture(NULL);
			one_hit_brick = true;
			invisible = false;
		}
		if (lives > 0) {
			brick_hit.play();
		}
		else {
			brick_break.play();
		}
		ball->reverseX();
		score->increase_score();
	}
	if (ballPos.y - radius <= pos.y + brick_height &&
		ballPos.y + radius >= pos.y + brick_height &&
		ballPos.x - radius >= pos.x &&
		ballPos.x + radius <= pos.x + brick_width) {
		ball->setPosition(ballPos.x, pos.y + brick_height + radius);
		ball->reverseY();
		lives--;
		if (invisible) {
			brick.setTexture(NULL);
			one_hit_brick = true;
			invisible = false;
		}
		if (lives > 0) {
			brick_hit.play();
		}
		else {
			brick_break.play();
		}
		score->increase_score();
	}
	if (ballPos.y + radius >= pos.y &&
		ballPos.y - radius <= pos.y &&
		ballPos.x - radius >= pos.x &&
		ballPos.x + radius <= pos.x + brick_width) {
		ball->setPosition(ballPos.x, pos.y - radius);
		ball->reverseY();
		lives--;
		if (invisible) {
			brick.setTexture(NULL);
			one_hit_brick = true;
			invisible = false;
		}
		if (lives > 0) {
			brick_hit.play();
		}
		else {
			brick_break.play();
		}
		score->increase_score();
	}
}
