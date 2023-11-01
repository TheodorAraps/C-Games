#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Bullet
{
private:
	// Where is the bullet?
	Vector2f __Position;

	// What each bullet looks like
	RectangleShape __BulletShape;

	// Is this bullet currently whizzing through the air
	bool __InFlight = false;

	// How fast does a bullet travel?
	float __BulletSpeed = 1000;

	// What fraction of 1 pixel does the bullet travel, 
	// Horizontally and vertically each frame?
	// These values will be derived from __BulletSpeed
	float __BulletDistanceX;
	float __BulletDistanceY;

	// Where is this bullet headed to?
	float __XTarget;
	float __YTarget;

	// Some boundaries so the bullet doesn't fly forever
	float __MaxX;
	float __MinX;
	float __MaxY;
	float __MinY;

	// Public function prototypes go here
public:
	// The constructor
	Bullet();

	// Stop the bullet
	void stop();

	// Returns the value of __InFlight
	bool isInFlight();

	// Launch a new bullet
	void shoot(float startX, float startY,
		float xTarget, float yTarget);

	// Tell the calling code where the bullet is in the world
	FloatRect getPosition();

	// Return the actual shape (for drawing)
	RectangleShape getShape();

	// Update the bullet each frame
	void update(float elapsedTime);

};