#include "Game.h"
#include "ResourceLoader.h"
#include <glm/gtx/string_cast.hpp>
#include <chrono>


Game::Game(const int width, const int height) : width(width), height(height), gameState(GAME_START)
{
	
}

void Game::init()
{
	Shader spriteShader("src\\Shaders\\vertex.shader", "src\\Shaders\\fragment.shader");
	Shader textShader("src\\Shaders\\characterVertex.shader", "src\\Shaders\\characterFragment.shader");

	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, -1.0f, 1.0f);

	ResourceLoader::loadShader("sprite", spriteShader); 
	ResourceLoader::loadShader("text", textShader);
	ResourceLoader::loadTexture("paddle", "C:\\Users\\bryce\\Desktop\\paddle.png");

	spriteShader.useShader();

	spriteShader.setInt("image", 0);
	spriteShader.setMat4("projection", projection);

	renderer = new SpriteRenderer(spriteShader); // render stuff using this shader to draw

	middleOfScreen = glm::vec2(width / 2, height / 2);

	glm::vec2 player1Pos = glm::vec2( PLAYER_SIZE.x, height / 2 - PLAYER_SIZE.y / 2); // left edge of screen
	glm::vec2 player2Pos = glm::vec2(width - (2 * PLAYER_SIZE.x), height / 2 - PLAYER_SIZE.y / 2); // right edge of screen

	Texture paddleTexture = ResourceLoader::getTexture("paddle");

	player1 = new GameObject(player1Pos, PLAYER_SIZE, paddleTexture);
	player2 = new GameObject(player2Pos, PLAYER_SIZE, paddleTexture);

	glm::vec2 ballPos = middleOfScreen;

	ball = new Ball(ballPos, generateRandomVelocity(), paddleTexture);

	welcomeText = new Text("Fonts/arial.ttf", 32);
	displayScoreText = new Text("Fonts/arial.ttf", 24);
	winnerText = welcomeText;
	textShader.useShader();

	welcomeText->renderText(textShader, "Welcome to Pong", middleOfScreen, 1.0, glm::vec3(0.0f, 0.0f, 1.0f));
}

void Game::update(float deltaTime)
{
	if(gameState == GAME_PLAYING)
	{
		ball->moveBall(deltaTime);
	}

	if(checkIfBallScored(*ball))
	{
		ball->getPosition().x < middleOfScreen.x ? player2Score++ : player1Score++;
		ball->resetBall(middleOfScreen, generateRandomVelocity());
	}

	performCollisionChecking();
}

void Game::render()
{
	Shader shader = ResourceLoader::getShader("text");

	switch(gameState)
	{
		case GAME_START:
		{
			welcomeText->renderText(shader, "Welcome to OpenGL Pong Game", middleOfScreen - glm::vec2(200, 0), 1.0, glm::vec3(0.0f, 0.0f, 1.0f));
			welcomeText->renderText(shader, "Press Enter to begin", middleOfScreen - glm::vec2(130, 50), 1.0, glm::vec3(0.0f, 0.0f, 1.0f));
		}
		break;

		case GAME_PLAYING:
		{
			player1->draw(*renderer);
			player2->draw(*renderer);
			ball->draw(*renderer);

			std::string player1ScoreString = "Player1: " + std::to_string(player1Score);
			std::string player2ScoreString = "Player2: " + std::to_string(player2Score);

			displayScoreText->renderText(shader, player1ScoreString, glm::vec2(0.25 * width, height - 50), 1.0, glm::vec3(0.0f, 0.0f, 1.0f));
			displayScoreText->renderText(shader, player2ScoreString, glm::vec2(0.75 * width, height - 50), 1.0, glm::vec3(0.0f, 0.0f, 1.0f));

			if (player1Score == WIN_SCORE || player2Score == WIN_SCORE)
			{
				gameState = GAME_WON;
				winnerName = player1Score == 10 ? "player1 wins!" : "player2 wins!";
			}
		}
		break;

		case GAME_WON:
		{
			winnerText->renderText(shader, winnerName, middleOfScreen - glm::vec2(100, 0), 1.0, glm::vec3(0.0f, 0.0f, 1.0f));
			winnerText->renderText(shader, "Press Enter to begin", middleOfScreen - glm::vec2(150, 50), 1.0, glm::vec3(0.0f, 0.0f, 1.0f));
			winnerText->renderText(shader, "Press Escape to exit", middleOfScreen - glm::vec2(150, 100), 1.0, glm::vec3(0.0f, 0.0f, 1.0f));
			player1Score = 0;
			player2Score = 0;
		}
		break;
	}
}

bool Game::checkCollision(GameObject& object1, GameObject& object2)
{
	// Collision x-axis?
	bool collisionX = object1.getPosition().x + object1.getSize().x >= object2.getPosition().x &&
		object2.getPosition().x + object2.getSize().x >= object1.getPosition().x;
	// Collision y-axis?
	bool collisionY = object1.getPosition().y + object1.getSize().y >= object2.getPosition().y &&
		object2.getPosition().y + object2.getSize().y >= object1.getPosition().y;

	// Collision only if on both axes
	return collisionX && collisionY;
}

void Game::performCollisionChecking()
{
	if(checkCollision(*ball, *player1) || checkCollision(*ball, *player2))
	{
		ball->reflectBall();
	}
}

glm::vec2 Game::generateRandomVelocity()
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);

	std::uniform_int_distribution<int> sign(0, 1);

	float xSpeed = BALL_VELOCITY * (2 * sign(generator) - 1);

	std::uniform_int_distribution<int> disY(-100, 100);
	float randomY = disY(generator);

	// return targetPos;
	return glm::vec2(xSpeed, randomY);
}

bool Game::checkIfBallScored(GameObject& ball)
{
	return (ball.getPosition().x >= (width - ball.getSize().x) || ball.getPosition().x <= 0);
} 

void Game::processInput(float deltaTime)
{
	if(keys[GLFW_KEY_R])
	{
		ball->resetBall(glm::vec2(width / 2, height / 2), generateRandomVelocity());
	}

	switch(gameState)
	{
		case GAME_START:
		{
			if (keys[GLFW_KEY_ENTER])
			{
				gameState = GAME_PLAYING;
			}
		}
		break;

		case GAME_PLAYING:
		{
			float velocity = PLAYER_VELOCITY * deltaTime;

			// Move player1
			if (keys[GLFW_KEY_W])
			{
				if (player1->getPosition().y >= 0)
				{
					player1->moveObject(0, -velocity);
				}
			}

			if (keys[GLFW_KEY_S])
			{
				if (player1->getPosition().y <= (height - PLAYER_SIZE.y))
				{
					player1->moveObject(0, velocity);
				}
			}

			//Move player 2
			if (keys[GLFW_KEY_UP])
			{
				if (player2->getPosition().y >= 0)
				{
					player2->moveObject(0, -velocity);
				}
			}

			if (keys[GLFW_KEY_DOWN])
			{
				if (player2->getPosition().y <= (height - PLAYER_SIZE.y))
				{
					player2->moveObject(0, velocity);
				}
			}
		}
		break;

		case GAME_WON:
		{
			if (keys[GLFW_KEY_ENTER])
			{
				gameState = GAME_START;
			}
		}
		break;
	}
	
}

Game::~Game()
{
	delete renderer;
	delete player1;
	delete player2;
	delete ball;
	delete welcomeText;
	delete displayScoreText;
}
