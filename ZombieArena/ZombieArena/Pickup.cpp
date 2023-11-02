#include "Pickup.h"
#include "TextureHolder.h"

Pickup::Pickup(int type)
{
	// Store the type of this pickup
	__Type = type;

	// Associate the texture with the sprite
	if (__Type == 1)
	{
		__Sprite = Sprite(TextureHolder::GetTexture("graphics/health_pickup.png"));

		// How much is pickup worth
		__Value = HEALTH_START_VALUE;

	}
	else
	{
		__Sprite = Sprite(TextureHolder::GetTexture("graphics/ammo_pickup.png"));

		// How much is pickup worth
		__Value = AMMO_START_VALUE;
	}

	__Sprite.setOrigin(25, 25);

	__SecondsToLive = START_SECONDS_TO_LIVE;
	__SecondsToWait = START_WAIT_TIME;
}

void Pickup::setArena(IntRect arena)
{

	// Copy the details of the arena to the pickup's __Arena
	__Arena.left = arena.left + 50;
	__Arena.width = arena.width - 50;
	__Arena.top = arena.top + 50;
	__Arena.height = arena.height - 50;

	spawn();
}

void Pickup::spawn()
{
	// Spawn at a random location
	srand((int)time(0) / __Type);
	int x = (rand() % __Arena.width);
	srand((int)time(0) * __Type);
	int y = (rand() % __Arena.height);

	// Not currently spawned
	//__Spawned = false;
	__SecondsSinceSpawn = 0;
	__Spawned = true;

	__Sprite.setPosition(x, y);
}

FloatRect Pickup::getPosition()
{
	return __Sprite.getGlobalBounds();
}

Sprite Pickup::getSprite()
{
	return __Sprite;
}

bool Pickup::isSpawned()
{
	return __Spawned;
}

int Pickup::gotIt()
{
	__Spawned = false;
	__SecondsSinceDeSpawn = 0;
	return __Value;
}

void Pickup::update(float elapsedTime)
{
	if (__Spawned)
	{
		__SecondsSinceSpawn += elapsedTime;
	}
	else
	{
		__SecondsSinceDeSpawn += elapsedTime;
	}


	// Do we need to hide a pickup?
	if (__SecondsSinceSpawn > __SecondsToLive && __Spawned)
	{
		// Revove the pickup and put it somewhere else
		__Spawned = false;
		__SecondsSinceDeSpawn = 0;
	}

	// Do we need to spawn a pickup
	if (__SecondsSinceDeSpawn > __SecondsToWait && !__Spawned)
	{
		// spawn the pickup and reset the timer
		spawn();
	}

}

void Pickup::upgrade()
{
	if (__Type == 1)
	{
		__Value += (HEALTH_START_VALUE * .5);
	}
	else
	{
		__Value += (AMMO_START_VALUE * .5);
	}

	// Make them more frequent and last longer
	__SecondsToLive += (START_SECONDS_TO_LIVE / 10);
	__SecondsToWait -= (START_WAIT_TIME / 10);
}
