#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Zombie
{
private:
	// Zombie speed per zombie type
	const float BLOATER_SPEED = 40;
	const float CHASER_SPEED = 80;
	const float CRAWLER_SPEED = 20;

	// Zombie health per zombie type
	const float BLOATER_HEALTH = 5;
	const float CHASER_HEALTH = 1;
	const float CRAWLER_HEALTH = 3;

	// Make each zombie vary its speed slightly
	const int MAX_VARRIANCE = 30;
	const int OFFSET = 101 - MAX_VARRIANCE;

	// Zombie position
	Vector2f __zombiePosition;

	// Sprite for the zombie
	Sprite __zombieSprite;

	// Zombie speed
	float __zombieSpeed;

	// Zombie Health
	float __zombieHealth;

	// Alive or dead
	bool __zombieAlive;
	
public:

	// Handle when a bullet hits a zombie
	bool hit();

	// Find out if the zombie is alive
	bool isAlive();

	// Spawn a new zombie
	void spawn(float startX, float startY, int type, int seed);

	// Return a rectangle that is the position in the world
	FloatRect getPosition();

	// Get a copy of the sprite to draw
	Sprite getSprite();

	// Update the zombie each frame
	void update(float elapsedTime, Vector2f playerLocation);
};


