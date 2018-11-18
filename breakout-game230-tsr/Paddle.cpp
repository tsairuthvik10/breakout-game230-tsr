#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

#include "Paddle.h"



Paddle::Paddle()
{
}


Paddle::Paddle(int sw, int sh, float speed, int &l, int pad_num) {
	screen_width = sw;
	screen_height = sh;
	paddle_width = sw / 7;
	paddle_height = paddle_width / 5;
	paddle.setSize(Vector2f(paddle_width, paddle_height));
	paddle.setPosition(Vector2f(sw / 2 - paddle_width / 2, sh - paddle_height));
	this->speed = speed;
	lives = &l;
	if (pad_num == 0) {
		one_life.loadFromFile("one_life.png");
		two_lives.loadFromFile("two_lives.png");
		three_lives.loadFromFile("three_lives.png");
	}
	else if (pad_num == 1) {
		one_life.loadFromFile("one_life2.png");
		two_lives.loadFromFile("two_lives2.png");
		three_lives.loadFromFile("three_lives2.png");
	}
	setTex(lives);
	SoundBuffer buff;
	buff.loadFromFile("lose_life.wav");
	lose_life_sound.setBuffer(buff);
	buff.loadFromFile("lose.wav");
	lose.setBuffer(buff);
	paddle_num = pad_num;
}


Paddle::~Paddle()
{
}

void Paddle::setTex(int *l) {
	if (*l > 3) {
		return;
	}
	if (*l == 3) {
		paddle.setTexture(&three_lives);
		return;
	}
	if (*l == 2) {
		paddle.setTexture(&two_lives);
		return;
	}
	if (*l == 1) {
		paddle.setTexture(&one_life);
		return;
	}
	return;
}

void Paddle::lose_life() {
	if (paddle_num != 1)
		*lives = *lives - 1;
	if (*lives > 0) {
		lose_life_sound.play();
	}
	else {
		lose.play();
	}
	setTex(lives);
}

void Paddle::update(float dt)
{

	Vector2f pos = paddle.getPosition();
	if (Keyboard::isKeyPressed(Keyboard::Left) && paddle_num == 0) {
		pos.x -= speed * dt;
		if (pos.x < 0) pos.x = 0;
	}
	if (Keyboard::isKeyPressed(Keyboard::Right) && paddle_num == 0) {
		pos.x += speed * dt;
		if (pos.x > screen_width - paddle_width) {
			pos.x = screen_width - paddle_width;
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::A) && paddle_num == 1) {
		pos.x -= speed * dt;
		if (pos.x < 0) pos.x = 0;
	}
	if (Keyboard::isKeyPressed(Keyboard::D) && paddle_num == 1) {
		pos.x += speed * dt;
		if (pos.x > screen_width - paddle_width) {
			pos.x = screen_width - paddle_width;
		}
	}
	paddle.setPosition(pos);
}
