#include "stdafx.h"
#include "zombie.h"
#include "TextureHolder.h"
#include <cstdlib>
#include <ctime>

using namespace std;

void Zombie::spawn(float startX, float startY, int type, int seed)
{

	switch (type)
	{
	case 0:
		// Bloater
		__zombieSprite = Sprite(TextureHolder::GetTexture(
			"graphics/bloater.png"));

		__zombieSpeed = 40;
		__zombieHealth = 5;
		break;

	case 1:
		// Chaser
		__zombieSprite = Sprite(TextureHolder::GetTexture(
			"graphics/chaser.png"));

		__zombieSpeed = 70;
		__zombieHealth = 1;
		break;

	case 2:
		// Crawler
		__zombieSprite = Sprite(TextureHolder::GetTexture(
			"graphics/crawler.png"));

		__zombieSpeed = 20;
		__zombieHealth = 3;
		break;
	}

	// Modify the speed to make the zombie unique
	// Every zombie is unique. Create a speed modifier
	srand((int)time(0) * seed);
	// Somewhere between 80 an 100
	float modifier = (rand() % MAX_VARRIANCE) + OFFSET;
	// Express as a fraction of 1
	modifier /= 100; // Now equals between .7 and 1
	__zombieSpeed *= modifier;

	__zombiePosition.x = startX;
	__zombiePosition.y = startY;

	__zombieSprite.setOrigin(25, 25);
	__zombieSprite.setPosition(__zombiePosition);
}

bool Zombie::hit()
{
	__zombieHealth--;

	if (__zombieHealth < 0)
	{
		// dead
		__zombieAlive = false;
		__zombieSprite.setTexture(TextureHolder::GetTexture(
			"graphics/blood.png"));

		return true;
	}

	// injured but not dead yet
	return false;
}

bool Zombie::isAlive()
{
	return __zombieAlive;
}

FloatRect Zombie::getPosition()
{
	return __zombieSprite.getGlobalBounds();
}


Sprite Zombie::getSprite()
{
	return __zombieSprite;
}

void Zombie::update(float elapsedTime,
	Vector2f playerLocation)
{
	float playerX = playerLocation.x;
	float playerY = playerLocation.y;

	// Update the zombie position variables
	if (playerX > __zombiePosition.x)
	{
		__zombiePosition.x = __zombiePosition.x +
			__zombieSpeed * elapsedTime;
	}

	if (playerY > __zombiePosition.y)
	{
		__zombiePosition.y = __zombiePosition.y +
			__zombieSpeed * elapsedTime;
	}

	if (playerX < __zombiePosition.x)
	{
		__zombiePosition.x = __zombiePosition.x -
			__zombieSpeed * elapsedTime;
	}

	if (playerY < __zombiePosition.y)
	{
		__zombiePosition.y = __zombiePosition.y -
			__zombieSpeed * elapsedTime;
	}

	// Move the sprite
	__zombieSprite.setPosition(__zombiePosition);

	// Face the sprite in the correct direction
	float angle = (atan2(playerY - __zombiePosition.y,
		playerX - __zombiePosition.x)
		* 180) / 3.141;

	__zombieSprite.setRotation(angle);


}