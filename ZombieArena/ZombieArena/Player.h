#pragma once

# include <SFML/Graphics.hpp>

using namespace sf;

class Player
{
private:
	// Initial values for player
	const float INITIAL_HEALTH = 100;
	const float INITIAL_SPEED = 200;

	// Player Health
	int __playerHealth;		// Current health
	int __playerMaxHealth;	// Max Health

	// Player Position
	Vector2f __playerPosition;
	
	// Player Graphics
	Sprite __playerSprite;
	Texture __playerTexture;

	// Player Movement
	bool __upPressed;
	bool __downPressed;
	bool __rightPressed;
	bool __leftPressed;
	float __playerSpeed;

	// Screen Resolution
	Vector2f __screenResolution;

	// Arena and Tile Size
	IntRect __arenaSize;
	int __tileSize;

	// Last time the player got hit
	Time __lastHit;

public:
	Player();

	// Call this at the end of every game
	void resetPlayerStats();

	void spawn(IntRect arena, Vector2f resolution, int tileSize);

	// Handle the player getting hit by a zombie
	bool hit(Time timeHit);

	// How long ago was the player last hit
	Time getLastHitTime();

	// Where is the player
	FloatRect getPosition();

	// Where is the center of the player
	Vector2f getCenter();

	// Which angle is the player facing
	float getRotation();

	// Send a copy of the sprite to main
	Sprite getSprite();

	// How much health has the player currently got?
	int getHealth();

	// The next four functions move the player
	void moveLeft();

	void moveRight();

	void moveUp();

	void moveDown();

	// Stop the player moving in a specific direction
	void stopLeft();

	void stopRight();

	void stopUp();

	void stopDown();

	// We will call this function once every frame
	void update(float elapsedTime, Vector2i mousePosition);

	// Give player a speed boost
	void upgradeSpeed();

	// Give the player some health
	void upgradeHealth();

	// Increase the maximum amount of health the player can have
	void increaseHealthLevel(int amount);

 };