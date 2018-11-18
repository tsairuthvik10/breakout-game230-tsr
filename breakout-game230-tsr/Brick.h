#pragma once
#include "GameObject.h"
#include "Ball.h"
#include "Score.h"
class Brick :
	public GameObject
{
public:
	Brick();
	Brick(bool obh, bool invis, float x, float y, int sw, int sh, int l, Ball * b, Score * s);
	~Brick();
	void update(float dt);
	void render(RenderWindow &w) {
		w.draw(brick);
	};
	void lower_life() {
		lives--;
	};
	int getLives() {
		return lives;
	};
	void setTexture(Texture & t) {
		if (invisible)
			brick.setTexture(&invisible_tex);
		else if (one_hit_brick)
			brick.setTexture(&coke_tex);
		else
			brick.setTexture(&t);
	}
	bool getOHB() {
		return one_hit_brick;
	};
private:
	Ball * ball;
	Score * score;
	RectangleShape brick;
	int brick_width;
	int brick_height;
	int lives;
	bool one_hit_brick;
	bool invisible;
	Sound brick_break;
	Sound brick_hit;
	SoundBuffer buff2;
	SoundBuffer buff1;
	Texture invisible_tex;
	Texture coke_tex;




};

