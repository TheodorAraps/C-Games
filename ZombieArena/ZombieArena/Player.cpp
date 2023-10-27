#include "player.h"
#include "TextureHolder.h"

Player::Player()
{
	__playerSpeed = INITIAL_SPEED;
	__playerHealth = INITIAL_HEALTH;
	__playerMaxHealth = INITIAL_HEALTH;

	// Associate a texture with the sprite
	// !!Watch this space!!
	__playerSprite = Sprite(TextureHolder::GetTexture(
		"graphics/player.png"));

	// Set the origin of the sprite to the centre, 
	// for smooth rotation
	__playerSprite.setOrigin(25, 25);
}

void Player::spawn(IntRect arena, Vector2f resolution, int tileSize)
{
	// Place the player in the middle of the arena
	__playerPosition.x = arena.width / 2;
	__playerPosition.y = arena.height / 2;

	// Copy the details of the arena to the player's __arenaSize
	__arenaSize.left = arena.left;
	__arenaSize.width = arena.width;
	__arenaSize.top = arena.top;
	__arenaSize.height = arena.height;

	// Remember how big the tiles are in this arena
	__tileSize = tileSize;

	// Strore the resolution for future use
	__screenResolution.x = resolution.x;
	__screenResolution.y = resolution.y;

}

Time Player::getLastHitTime()
{
	return __lastHit;
}

bool Player::hit(Time timeHit)
{
	if (timeHit.asMilliseconds() - __lastHit.asMilliseconds() > 200)// 2 tenths of second
	{
		__lastHit = timeHit;
		__playerHealth -= 10;
		return true;
	}
	else
	{
		return false;
	}

}

void Player::resetPlayerStats()
{
	__playerSpeed = INITIAL_SPEED;
	__playerHealth = INITIAL_HEALTH;
	__playerMaxHealth = INITIAL_HEALTH;
}

FloatRect Player::getPosition()
{
	return __playerSprite.getGlobalBounds();
}

Vector2f Player::getCenter()
{
	return __playerPosition;
}

float Player::getRotation()
{
	return __playerSprite.getRotation();
}

Sprite Player::getSprite()
{
	return __playerSprite;
}

int Player::getHealth()
{
	return __playerHealth;
}

void Player::moveLeft()
{
	__leftPressed = true;
}

void Player::moveRight()
{
	__rightPressed = true;
}

void Player::moveUp()
{
	__upPressed = true;
}

void Player::moveDown()
{
	__downPressed = true;
}

void Player::stopLeft()
{
	__leftPressed = false;
}

void Player::stopRight()
{
	__rightPressed = false;
}

void Player::stopUp()
{
	__upPressed = false;
}

void Player::stopDown()
{
	__downPressed = false;__playerTileSize
}

void Player::update(float elapsedTime, Vector2i mousePosition)
{

	if (__upPressed)
	{
		__playerPosition.y -= __playerSpeed * elapsedTime;
	}

	if (__downPressed)
	{
		__playerPosition.y += __playerSpeed * elapsedTime;
	}

	if (__rightPressed)
	{
		__playerPosition.x += __playerSpeed * elapsedTime;
	}

	if (__leftPressed)
	{
		__playerPosition.x -= __playerSpeed * elapsedTime;
	}

	__playerSprite.setPosition(__playerPosition);



	// Keep the player in the arena
	if (__playerPosition.x > __arenaSize.width - __tileSize)
	{
		__playerPosition.x = __arenaSize.width - __tileSize;
	}

	if (__playerPosition.x < __arenaSize.left + __tileSize)
	{
		__playerPosition.x = __arenaSize.left + __tileSize;
	}

	if (__playerPosition.y > __arenaSize.height - __tileSize)
	{
		__playerPosition.y = __arenaSize.height - __tileSize;
	}

	if (__playerPosition.y < __arenaSize.top + __tileSize)
	{
		__playerPosition.y = __arenaSize.top + __tileSize;
	}

	// Calculate the angle the player is facing
	float angle = (atan2(mousePosition.y - __screenResolution.y / 2,
		mousePosition.x - __screenResolution.x / 2)
		* 180) / 3.141;

	__playerSprite.setRotation(angle);
}

void Player::upgradeSpeed()
{
	// 20% speed upgrade
	__playerSpeed += (INITIAL_SPEED * .2);
}

void Player::upgradeHealth()
{
	// 20% max health upgrade
	__playerMaxHealth += (INITIAL_HEALTH * .2);

}

void Player::increaseHealthLevel(int amount)
{
	__playerHealth += amount;

	// But not beyond the maximum
	if (__playerHealth > __playerMaxHealth)
	{
		__playerHealth = __playerMaxHealth;
	}
}