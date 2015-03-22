#include"stdafx.h"
#include"GameBall.h"

GameBall::GameBall() :_velocity(230.0f), _elapsedTimeSinceStart(0.0f)
{
	Load("images/ball.png");
	assert(IsLoaded());

	GetSprite().setOrigin(15, 15);


	//the random device that will seed the generator
	std::random_device seeder;
	//then make a mersenne twister engine
	std::mt19937 engine(seeder());
	//then the easy part... the distribution
	std::uniform_real_distribution<float> dist(0.0, 360.0);
	//then just generate the integer like this:
    _angle = dist(engine);
}

GameBall::~GameBall()
{
}

void GameBall::Update(float elapsedTime)
{
	_elapsedTimeSinceStart += elapsedTime;

	//Delay game from starting until 3 seconds
	if (_elapsedTimeSinceStart < 3.0f)
		return;

	float moveAmount = 50*_velocity * elapsedTime;

	float moveByX = LinearVelocityX(_angle)*moveAmount;
	float moveByY = LinearVelocityY(_angle)* moveAmount;

	//left side screen collision
	if (GetPosition().x + moveByX <= 0 + GetWidth() / 2
		|| GetPosition().x + GetHeight() / 2 + moveByX >= Game::SCREEN_WIDTH)
	{
		_angle = 360.0f - _angle;
		if (_angle > 260.0f&&_angle < 280.0f) _angle += 20.0f;
		if (_angle>80.0f&&_angle < 100.0f)_angle += 20.0f;
		moveByX = -moveByX;
	}

	PlayerPaddle* player1 =
		dynamic_cast<PlayerPaddle*>(Game::GetGameObjectManager().Get("Paddle1"));
	if (player1 != NULL)
	{
		sf::Rect<float> p1BB = player1->GetBoundingRect();
		if (p1BB.intersects(GetBoundingRect()))
		{
			_angle = 360.0f - (_angle - 180.0f);
			if (_angle>360.0f) _angle -= 360.0f;

			moveByY = -moveByY;

		//Make sure Ball is not inside paddle
			if (GetBoundingRect().height > player1->GetBoundingRect().top)
			{
				SetPosition(GetPosition().x, player1->GetBoundingRect().top - GetWidth() / 2 - 1);
			}

		// Now add english based on players velocity

			float playerVelocity = player1->GetVelocity();

			if (playerVelocity < 0)
			{
				//moving left
				_angle -= 20.0f;
				if (_angle < 0) _angle = 360.0f - _angle;
			}
			else if (playerVelocity > 0)
			{
				_angle += 20.0f;
				if (_angle > 360.0f) _angle = _angle - 360.0f;
			}

			_velocity += 5.0f;
		}
		if (GetPosition().y - GetHeight() / 2 <= 0)
		{
			_angle = 180 - _angle;
			moveByY = -moveByY;
		}

		if (GetPosition().y + GetHeight() / 2 + moveByY >= Game::SCREEN_HEIGHT)
		{
			//move to middle of the screen for now and randomize angle
			GetSprite().setPosition(Game::SCREEN_WIDTH / 2, Game::SCREEN_HEIGHT / 2);
			
			
			
			
			//the random device that will seed the generator
			std::random_device seeder;
			//then make a mersenne twister engine
			std::mt19937 engine(seeder());
			//then the easy part... the distribution
			std::uniform_real_distribution<float> dist(0.0, 360.0);
			//then just generate the integer like this:
			_angle = dist(engine);
			


			_velocity = 220.0f;
			_elapsedTimeSinceStart = 0.0f;
		}

		GetSprite().move(moveByX, moveByY);
	}
}

float GameBall::LinearVelocityX(float angle)
{
	angle -= 90;
	if (angle < 0) angle = 360 + angle;
	return (float)std::cos(angle * (3.1415926 / 180.0f));
}
float GameBall::LinearVelocityY(float angle)
{
	angle -= 90;
	if (angle < 0) angle = 360 + angle;
	return (float)std::sin(angle * (3.1415926 / 180.0f));
}
