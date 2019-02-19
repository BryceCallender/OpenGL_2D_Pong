#pragma once
#include "SpriteRenderer.h"
#include "GameObject.h"
#include "GameClasses/Ball.h"
#include <random>
#include <ctime>
#include "Text.h"

enum GameState
{
	GAME_START,
	GAME_PLAYING,
	GAME_WON,
};

// Initial size of the player paddle
const glm::vec2 PLAYER_SIZE(20, 100);

// Initial velocity of the player paddle
const float PLAYER_VELOCITY = 200.0f;
const float BALL_VELOCITY = 250.0f;

class Game
{
public:
	Game(const int width, const int height);
	~Game();

	void init();
	void update(float deltaTime);
	void render();
	void processInput(float deltaTime);
	bool checkIfBallScored(GameObject& ball);
	bool checkCollision(GameObject& object1, GameObject& object2);
	void performCollisionChecking();

	bool keys[1024];
private:
	glm::vec2 generateRandomVelocity();
	
	int width;
	int height;
	int player1Score;
	int player2Score;
	const int WIN_SCORE = 10;
	glm::vec2 middleOfScreen;
	std::string winnerName;

	GameState gameState;
	SpriteRenderer* renderer;
	GameObject *player1;
	GameObject *player2;
	Ball *ball;
	Text *welcomeText;
	Text *displayScoreText;
	Text *winnerText;
};

