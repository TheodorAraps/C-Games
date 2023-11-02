#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Pickup
{
private:
	//Start value for health pickups
	const int HEALTH_START_VALUE = 50;
	const int AMMO_START_VALUE = 12;
	const int START_WAIT_TIME = 10;
	const int START_SECONDS_TO_LIVE = 5;

	// The sprite that represents this pickup
	Sprite __Sprite;

	// The arena it exists in
	IntRect __Arena;

	// How much is this pickup worth?
	int __Value;

	// What type of pickup is this? 
	// 1 = health, 2 = ammo
	int __Type;

	// Handle spawning and disappearing
	bool __Spawned;
	float __SecondsSinceSpawn;
	float __SecondsSinceDeSpawn;
	float __SecondsToLive;
	float __SecondsToWait;

	// Public prototypes go here
public:

	Pickup(int type);

	// Prepare a new pickup
	void setArena(IntRect arena);

	void spawn();

	// Check the position of a pickup
	FloatRect getPosition();

	// Get the sprite for drawing
	Sprite getSprite();

	// Let the pickup update itself each frame
	void update(float elapsedTime);

	// Is this pickup currently spawned?
	bool isSpawned();

	// Get the goodness from the pickup
	int gotIt();

	// Upgrade the value of each pickup
	void upgrade();

};