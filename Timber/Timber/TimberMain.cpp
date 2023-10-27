#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


using namespace sf;

// Function declaration
void lowerBranches(int seed);

const int NUM_BRANCHES = 6;
const int NUM_CLOUDS = 6;
// Line the axe up with the tree
const float AXE_POSITION_LEFT = 690;
const float AXE_POSITION_RIGHT = 1220;

// Where is the player/branch? 
// Left or Right
enum class side { LEFT, RIGHT, NONE };
side branchPositions[NUM_BRANCHES];

// The player starts on the left
side playerSide = side::LEFT;

// Bee is moving 
bool beeActive = false;

// bee's speed
float beeSpeed = 0.0f;

// Clouds
int cloudSpeeds[NUM_CLOUDS];
bool cloudsActive[NUM_CLOUDS];

int main()
{
	// Create a video mode object
	VideoMode vm(1920, 1080);

	// Create and open a window for the game
	RenderWindow window(vm, "Timber!!!", Style::Fullscreen);

	// Create a texture to hold a graphic on the GPU
	Texture textureBackground;
	Texture textureTree;
	Texture textureBee;
	Texture textureCloud;
	Texture textureBranch;
	Texture texturePlayer;
	Texture textureRIP;
	Texture textureLog;
	Texture textureAxe;

	// Load a graphic into the texture
	textureBackground.loadFromFile("graphics/background.png");
	textureTree.loadFromFile("graphics/tree.png");
	textureBee.loadFromFile("graphics/bee.png");
	textureCloud.loadFromFile("graphics/cloud.png");
	textureBranch.loadFromFile("graphics/branch.png");
	texturePlayer.loadFromFile("graphics/player.png");
	textureRIP.loadFromFile("graphics/rip.png");
	textureLog.loadFromFile("graphics/log.png");
	textureAxe.loadFromFile("graphics/axe.png");

	// Create a sprite
	Sprite spriteBackground;
	Sprite spriteTree;
	Sprite spriteBee;
	Sprite branches[NUM_BRANCHES];
	Sprite clouds[NUM_CLOUDS];
	Sprite spritePlayer;
	Sprite spriteRIP;
	Sprite spriteLog;
	Sprite spriteAxe;

	// Attach the texture to the sprite
	spriteBackground.setTexture(textureBackground);
	spriteTree.setTexture(textureTree);
	spriteBee.setTexture(textureBee);
	spritePlayer.setTexture(texturePlayer);
	spriteRIP.setTexture(textureRIP);
	spriteAxe.setTexture(textureAxe);

	// Set the of the sprite on the screen
	spriteBackground.setPosition(0, 0);
	spriteTree.setPosition(810, 0);
	spriteBee.setPosition(0, 800);
	spritePlayer.setPosition(580, 720);
	spriteRIP.setPosition(600, 860);
	spriteAxe.setPosition(700, 810);


	for (int i = 0; i < NUM_CLOUDS; i++)
	{
		clouds[i].setTexture(textureCloud);
		clouds[i].setPosition(-300, i * 150);
		cloudsActive[i] = false;
		cloudSpeeds[i] = 0;

	}

	// Set the texture for each branch sprite
	for (int i = 0; i < NUM_BRANCHES; i++) {
		branches[i].setTexture(textureBranch);
		branches[i].setPosition(-2000, -2000);

		// Set the sprite's origin to dead center
		// We can then flip it around without changing its position
		branches[i].setOrigin(220, 20);
	}



	// Variables to control time itself
	Clock clock;
	// Time bar
	RectangleShape timeBar;
	float timeBarStartWidth = 400;
	float timeBarHeight = 80;
	timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
	timeBar.setFillColor(Color::Red);
	timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);

	Time gameTimeTotal;
	float timeRemaining = 6.0f;
	float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

	// Track whether the game is running
	bool paused = true;
	// Draw some text
	int score = 0;

	Text messageText;
	Text scoreText;
	Text fpsText;

	// Font style
	Font font;
	font.loadFromFile("fonts/KOMIKAP_.ttf");

	// Set the font to our message
	messageText.setFont(font);
	scoreText.setFont(font);
	fpsText.setFont(font);


	// Set up the fps text
	fpsText.setFillColor(Color::White);
	fpsText.setCharacterSize(100);
	fpsText.setPosition(1200, 20);

	// Assign the actual message
	messageText.setString("Press Enter to start!");
	scoreText.setString("Score = 0");

	// Make it really big
	messageText.setCharacterSize(75);
	scoreText.setCharacterSize(100);

	// Choose a color
	messageText.setFillColor(Color::White);
	scoreText.setFillColor(Color::White);

	// Position the text
	FloatRect textRect = messageText.getLocalBounds();

	messageText.setOrigin(textRect.left +
		textRect.width / 2.0f,
		textRect.top +
		textRect.height / 2.0f);

	messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

	scoreText.setPosition(20, 20);

	// Backgrounds for the text
	RectangleShape rect1;
	rect1.setFillColor(sf::Color(0, 0, 0, 150));
	rect1.setSize(Vector2f(600, 105));
	rect1.setPosition(0, 30);

	RectangleShape rect2;
	rect2.setFillColor(sf::Color(0, 0, 0, 150));
	rect2.setSize(Vector2f(1000, 105));
	rect2.setPosition(1150, 30);

	// control the drawing of the score
	int lastDrawn = 0;



	// Prepare the flying log
	spriteLog.setTexture(textureLog);
	spriteLog.setPosition(810, 720);

	// Some other useful log related variables
	bool logActive = false;
	float logSpeedX = 1000;
	float logSpeedY = -1500;

	// Control the player input
	bool acceptInput = false;

	// Prepare the sound
	SoundBuffer chopBuffer;
	SoundBuffer deathBuffer;
	SoundBuffer ootBuffer;
	
	chopBuffer.loadFromFile("sound/chop.wav");
	deathBuffer.loadFromFile("sound/death.wav");
	ootBuffer.loadFromFile("sound/out_of_time.wav");
	
	Sound chop;
	Sound death;
	Sound outOfTime;

	chop.setBuffer(chopBuffer);
	death.setBuffer(deathBuffer);
	outOfTime.setBuffer(ootBuffer);


	while (window.isOpen())
	{
		// score ++;
		Event event;
		while (window.pollEvent(event))
		{


			if (event.type == Event::KeyReleased && !paused)
			{
				// Listen for key presses again
				acceptInput = true;

				// hide the axe
				spriteAxe.setPosition(2000,
					spriteAxe.getPosition().y);
			}

		}

		/*
		****************************************
		Handle the players input
		****************************************
		*/

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		// Start the game
		if (Keyboard::isKeyPressed(Keyboard::Return))
		{
			paused = false;

			// Reset the time and the score
			score = 0;
			timeRemaining = 6;

			// Make all the branches disappear
			for (int i = 1; i < NUM_BRANCHES; i++)
			{
				branchPositions[i] = side::NONE;
			}

			// Make sure the gravestone is hidden
			spriteRIP.setPosition(675, 2000);

			// Move the player into position
			spritePlayer.setPosition(580, 720);

			acceptInput = true;


		}

		// Wrap the player controls to
		// Make sure we are accepting input
		if (acceptInput)
		{
			// More code here next...
			// First handle pressing the right cursor key
			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				// Make sure the player is on the right
				playerSide = side::RIGHT;

				score++;

				// Add to the amount of time remaining
				timeRemaining += (2 / score) + .15;


				spriteAxe.setScale(-1.f, 1.f);

				spriteAxe.setPosition(AXE_POSITION_RIGHT,
					spriteAxe.getPosition().y);
							   
				spritePlayer.setScale(-1.f, 1.f);
				spritePlayer.setPosition(1280, 720);

				// update the branches
				lowerBranches(score);

				// set the log flying to the left
				spriteLog.setPosition(810, 720);
				logSpeedX = -5000;
				logActive = true;


				acceptInput = false;

				// Play a chop sound
				chop.play();

			}

			// Handle the left cursor key
			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				// Make sure the player is on the left
				playerSide = side::LEFT;

				score++;

				// Add to the amount of time remaining
				timeRemaining += (2 / score) + .15;


				spriteAxe.setScale(1.f, 1.f);

				spriteAxe.setPosition(AXE_POSITION_LEFT,
					spriteAxe.getPosition().y);

				spritePlayer.setScale(1.f, 1.f);
				spritePlayer.setPosition(610, 720);

				// update the branches
				lowerBranches(score);

				// set the log flying
				spriteLog.setPosition(810, 720);
				logSpeedX = 5000;
				logActive = true;


				acceptInput = false;

				// Play a chop sound
				chop.play();

			}


		}


		/*
		****************************************
		Update the scene
		****************************************
		*/
		if (!paused)
		{

			// Measure time
			Time dt = clock.restart();

			// Subtract from the amount of time remaining
			timeRemaining -= dt.asSeconds();
			// size up the time bar
			timeBar.setSize(Vector2f(timeBarWidthPerSecond *
				timeRemaining, timeBarHeight));


			if (timeRemaining <= 0.0f) {

				// Pause the game
				paused = true;

				// Change the message shown to the player
				messageText.setString("Out of time!!");

				//Reposition the text based on its new size
				FloatRect textRect = messageText.getLocalBounds();
				messageText.setOrigin(textRect.left +
					textRect.width / 2.0f,
					textRect.top +
					textRect.height / 2.0f);

				messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

				// Play the out of time sound
				outOfTime.play();
			}

			// Setup the bee
			if (!beeActive)
			{

				// How fast is the bee
				srand((int)time(0) * 10);
				beeSpeed = (rand() % 200) + 200;

				// How high is the bee
				srand((int)time(0) * 10);
				float height = (rand() % 500) + 500;
				spriteBee.setPosition(2000, height);
				beeActive = true;

			}
			else
				// Move the bee
			{

				spriteBee.setPosition(
					spriteBee.getPosition().x -
					(beeSpeed * dt.asSeconds()),
					spriteBee.getPosition().y);

				// Has the bee reached the right hand edge of the screen?
				if (spriteBee.getPosition().x < -100)
				{
					// Set it up ready to be a whole new cloud next frame
					beeActive = false;
				}
			}

			// Manage the clouds with arrays
			for (int i = 0; i < NUM_CLOUDS; i++)
			{
				if (!cloudsActive[i])
				{
					// How fast is the cloud
					srand((int)time(0) * i);
					cloudSpeeds[i] = (rand() % 200);

					// How high is the cloud
					srand((int)time(0) * i);
					float height = (rand() % 150);
					clouds[i].setPosition(-200, height);
					cloudsActive[i] = true;

				}
				else
				{
					// Set the new position
					clouds[i].setPosition(
						clouds[i].getPosition().x +
						(cloudSpeeds[i] * dt.asSeconds()),
						clouds[i].getPosition().y);

					// Has the cloud reached the right hand edge of the screen?
					if (clouds[i].getPosition().x > 1920)
					{
						// Set it up ready to be a whole new cloud next frame
						cloudsActive[i] = false;
					}

				}

			}
			
			// Draw the score and the frame rate once every 100 frames
			lastDrawn++;
			if (lastDrawn == 100) {
				// Update the score text
				std::stringstream ss;
				ss << "Score = " << score;
				scoreText.setString(ss.str());

				// Draw the fps
				std::stringstream ss2;
				ss2 << "FPS = " << 1 / dt.asSeconds();
				fpsText.setString(ss2.str());
				lastDrawn = 0;
			}

			// update the branch sprites
			for (int i = 0; i < NUM_BRANCHES; i++)
			{

				float height = i * 150;

				if (branchPositions[i] == side::LEFT)
				{
					// Move the sprite to the left side
					branches[i].setPosition(610, height);
					// Flip the sprite round the other way
					branches[i].setOrigin(220, 40);
					branches[i].setScale(-1.f, 1.f);
				}
				else if (branchPositions[i] == side::RIGHT)
				{
					// Move the sprite to the right side
					branches[i].setPosition(1330, height);
					// Set the sprite rotation to normal
					branches[i].setOrigin(220, 40);
					branches[i].setScale(1.f, 1.f);

				}
				else
				{
					// Hide the branch
					branches[i].setPosition(3000, height);
				}
			}

			// Handle a flying log				
			if (logActive)
			{

				spriteLog.setPosition(
					spriteLog.getPosition().x + (logSpeedX * dt.asSeconds()),
					spriteLog.getPosition().y + (logSpeedY * dt.asSeconds()));

				// Has the insect reached the right hand edge of the screen?
				if (spriteLog.getPosition().x < -100 ||
					spriteLog.getPosition().x > 2000)
				{
					// Set it up ready to be a whole new cloud next frame
					logActive = false;
					spriteLog.setPosition(810, 720);
				}
			}

			// has the player been squished by a branch?
			if (branchPositions[5] == playerSide)
			{
				// death
				paused = true;
				acceptInput = false;

				// Draw the gravestone
				if (playerSide == side::LEFT) spriteRIP.setPosition(560, 760);
				if (playerSide == side::RIGHT) spriteRIP.setPosition(1255, 760);

				// hide the player
				spritePlayer.setPosition(3000, 660);

				// Change the text of the message
				messageText.setString("SQUISHED!!");

				// Center it on the screen
				FloatRect textRect = messageText.getLocalBounds();

				messageText.setOrigin(textRect.left +
					textRect.width / 2.0f,
					textRect.top + textRect.height / 2.0f);

				messageText.setPosition(1920 / 2.0f,
					1080 / 2.0f);

				// Play the death sound
				death.play();


			}


		}// End if(!paused)

		 /*
		 ****************************************
					Draw the scene
		 ****************************************
		 */

		// Clear everything from the last frame
		window.clear();

		// Draw our game scene here
		window.draw(spriteBackground);

		// Draw the clouds
		for (int i = 0; i < NUM_CLOUDS; i++)
		{
			window.draw(clouds[i]);
		}

		// Draw the branches
		for (int i = 0; i < NUM_BRANCHES; i++) {
			window.draw(branches[i]);
		}
		// Draraw the flying log
		window.draw(spriteLog);

		// Draw the tree
		window.draw(spriteTree);

		// Draw the player
		window.draw(spritePlayer);

		// Draw the axe
		window.draw(spriteAxe);


		// Draw the gravestone
		window.draw(spriteRIP);

		// Draw backgrounds for the text
		window.draw(rect1);
		window.draw(rect2);

		// Drawraw the bee
		window.draw(spriteBee);

		// Draw the score
		window.draw(scoreText);



		// Draw the FPS
		window.draw(fpsText);

		// Draw the timebar
		window.draw(timeBar);


		if (paused)
		{
			// Draw our message
			window.draw(messageText);
		}

		// Show everything we just drew
		window.display();


	}

	return 0;
}

// Function definition
void lowerBranches(int seed)
{
	// Move all the branches down one place
	for (int j = NUM_BRANCHES - 1; j > 0; j--) {
		branchPositions[j] = branchPositions[j - 1];
	}

	// Spawn a new branch at position 0
	// LEFT, RIGHT or NONE
	srand((int)time(0) + seed);
	int r = (rand() % 5);

	switch (r) {
	case 0:
		branchPositions[0] = side::LEFT;
		break;

	case 1:
		branchPositions[0] = side::RIGHT;
		break;

	default:
		branchPositions[0] = side::NONE;
		break;
	}


}