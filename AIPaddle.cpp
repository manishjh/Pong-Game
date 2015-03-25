#include"stdafx.h"
#include "AIPaddle.h"
#include "Game.h"
#include "GameBall.h"

AIPaddle::AIPaddle() : _velocity(0), _maxVelocity(600.0f)
{
	Load("images/paddle.png");
	assert(IsLoaded());

	GetSprite().setOrigin(GetSprite().getLocalBounds().width / 2, GetSprite().getGlobalBounds().height / 2);
}

AIPaddle::~AIPaddle()
{}

void AIPaddle::Draw(sf::RenderWindow & rw)
{
	VisibleGameObject::Draw(rw);
}

float AIPaddle::GetVelocity() const
{
	return _velocity;
}

void AIPaddle::Update(float elapsedTime)
{
	const GameBall* gameBall = static_cast<GameBall*>
		(Game::GetGameObjectManager().Get("Ball"));
	sf::Vector2f ballPosition = gameBall->GetPosition();

	if (GetPosition().x - 20 < ballPosition.x)
		_velocity = 550.0f;
	else if (GetPosition().x + 20 > ballPosition.x)
		_velocity = -550.0f;
	else
		_velocity = 0.0f;


	sf::Vector2f pos = this->GetPosition();

	if (pos.x <= GetSprite().getLocalBounds().width / 2 && _velocity<0
		|| pos.x >= (Game::SCREEN_WIDTH - GetSprite().getGlobalBounds().width / 2) && _velocity > 0)
	{
		_velocity = -_velocity; // Bounce by current velocity in opposite direction
	}


	GetSprite().move(_velocity * elapsedTime, 0);


	
}