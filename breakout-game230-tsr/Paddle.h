#pragma once
#include "GameObject.h"
class Paddle :
	public GameObject
{
public:
	Paddle();
	Paddle(int sw, int sh, float speed, int &l, int pad_num);
	~Paddle();
	void update(float dt);
	void render(RenderWindow &w) {
		w.draw(paddle);
	}
	Vector2f getMidpoint() {
		return Vector2f(paddle.getPosition().x + paddle_width / 2, paddle.getPosition().y);
	}
	const Vector2f getPosition() {
		return paddle.getPosition();
	}
	int getWidth() {
		return paddle_width;
	}
	void lose_life();
	void setTex(int *l);
private:
	int paddle_width;
	int paddle_height;
	int screen_width;
	int screen_height;
	int paddle_num;
	RectangleShape paddle;
	float speed = 150;
	int *lives;
	Texture one_life, two_lives, three_lives;
	Sound lose_life_sound;
	Sound lose;
};

