#include "bullet.h"


// The constructor
Bullet::Bullet()
{
	__BulletShape.setSize(sf::Vector2f(2, 2));
}

void Bullet::shoot(float startX, float startY,
	float targetX, float targetY)
{
	// Keep track of the bullet
	__InFlight = true;
	__Position.x = startX;
	__Position.y = startY;

	// Calculate the gradient of the flight path
	float gradient = (startX - targetX) / (startY - targetY);

	// Any gradient less than zero needs to be negative
	if (gradient < 0)
	{
		gradient *= -1;
	}

	// Calculate the ratio between x and t
	float ratioXY = __BulletSpeed / (1 + gradient);

	// Set the "speed" horizontally and vertically
	__BulletDistanceY = ratioXY;
	__BulletDistanceX = ratioXY * gradient;

	// Point the bullet in the right direction
	if (targetX < startX)
	{
		__BulletDistanceX *= -1;
	}

	if (targetY < startY)
	{
		__BulletDistanceY *= -1;
	}

	// Finally, assign the results to the
	// member variables
	__XTarget = targetX;
	__YTarget = targetY;

	// Set a max range of 1000 pixels
	float range = 1000;
	__MinX = startX - range;
	__MaxX = startX + range;
	__MinY = startY - range;
	__MaxY = startY + range;

	// Position the bullet ready to be drawn
	__BulletShape.setPosition(__Position);
}

void Bullet::stop()
{
	__InFlight = false;
}

bool Bullet::isInFlight()
{
	return __InFlight;
}

FloatRect Bullet::getPosition()
{
	return __BulletShape.getGlobalBounds();
}

RectangleShape Bullet::getShape()
{
	return __BulletShape;
}


void Bullet::update(float elapsedTime)
{
	// Update the bullet position variables
	__Position.x += __BulletDistanceX * elapsedTime;
	__Position.y += __BulletDistanceY * elapsedTime;

	// Move the bullet
	__BulletShape.setPosition(__Position);

	// Has the bullet gone out of range?
	if (__Position.x < __MinX || __Position.x > __MaxX ||
		__Position.y < __MinY || __Position.y > __MaxY)
	{
		__InFlight = false;
	}

}