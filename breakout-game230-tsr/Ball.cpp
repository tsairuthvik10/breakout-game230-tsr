#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

#include "Ball.h"



Ball::Ball()
{
}

float dist(Vector2f a, Vector2f b) {
	return sqrtf(((b.x - a.x) * (b.x - a.x)) + ((b.y - a.y) * (b.y - a.y)));
}

Ball::Ball(int sw, int sh, int r, vector<Paddle*> &pad, Vector2f baseVel) {
	paddles = &pad;
	screen_height = sh;
	screen_width = sw;
	radius = r;
	ball.setRadius(radius);
	ball.setOrigin(Vector2f(r, r));
//	ball.setOutlineColor(Color::Black);
	//ball.setOutlineThickness(2);
	bt.loadFromFile("coin.jpg");
	ball.setTexture(&bt);
	launching = true;
	velocity.x = baseVel.x;
	velocity.y = -baseVel.y;
	baseVelocity.x = baseVel.x;
	baseVelocity.y = baseVel.y;

	buff1.loadFromFile("cointoss.ogg");
	buff2.loadFromFile("coinhit.ogg");
	wall_bounce.setBuffer(buff2);

	paddle_bounce.setBuffer(buff1);

}


Ball::~Ball()
{
}

void Ball::update(float dt)
{

	float rotation = ball.getRotation();
	ball.setRotation(rotation + 100 * dt);

	Vector2f pos = ball.getPosition();
	if (Keyboard::isKeyPressed(Keyboard::Space)) launching = false;
	if (launching) {
		pos.x = (*paddles)[0]->getMidpoint().x;
		pos.y = (*paddles)[0]->getMidpoint().y - radius;
	}
	else {
		pos.x += velocity.x * dt;
		pos.y += velocity.y * dt;
		if (pos.x + radius >= screen_width) {
			pos.x = screen_width - radius;
			reverseX();
			wall_bounce.play();
		}
		if (pos.x - radius <= 0) {
			pos.x = radius;
			reverseX();
			wall_bounce.play();
		}
		if (pos.y - radius <= 0) {
			pos.y = radius;
			reverseY();
			wall_bounce.play();
		}
		if (pos.y + radius >= screen_height) {
			launching = true;
			for (int i = 0; i < (*paddles).size(); ++i)
				(*paddles)[i]->lose_life();
		}
		for (int i = 0; i < (*paddles).size(); ++i) {
			Vector2f paddlePos = (*paddles)[i]->getPosition();
			if (!launching &&
				pos.x >= paddlePos.x &&
				pos.x <= paddlePos.x + (*paddles)[i]->getWidth() &&
				pos.y + radius >= paddlePos.y) {
				paddle_bounce.play();
				pos.y = paddlePos.y - radius;
				reverseY();
				float distance = dist(pos, (*paddles)[i]->getMidpoint());
				velocity.x = baseVelocity.x * distance / 12;
				if (pos.x < (*paddles)[i]->getMidpoint().x) {
					if (velocity.x > 0) {
						reverseX();
					}
				}
				else {
					if (velocity.x < 0) {
						reverseX();
					}
				}
			}
		}
	}
	ball.setPosition(pos);
}
