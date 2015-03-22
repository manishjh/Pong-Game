#include "StdAfx.h"
#include "PlayerPaddle.h"
#include "Game.h"


PlayerPaddle::PlayerPaddle() :
_velocity(0),
_maxVelocity(600.0f)
{
	Load("images/paddle.png");
	assert(IsLoaded());

	GetSprite().setOrigin(GetSprite().getLocalBounds().width /2, GetSprite().getLocalBounds().height / 2);

}


PlayerPaddle::~PlayerPaddle()
{
}

void PlayerPaddle::Draw(sf::RenderWindow & rw)
{
	VisibleGameObject::Draw(rw);
}

float PlayerPaddle::GetVelocity() const
{
	return _velocity;
}

void PlayerPaddle::Update(float elapsedTime)
{
	sf::Vector2f pos = this->GetPosition();

	if (pos.x <= GetSprite().getLocalBounds().width / 2
		|| pos.x >= (Game::SCREEN_WIDTH - GetSprite().getGlobalBounds().width / 2))
	{
		_velocity = -_velocity; // Bounce by current velocity in opposite direction
	}
	
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		sf::Vector2f pos = this->GetPosition();
		
		if (pos.x <= GetSprite().getLocalBounds().width / 2
			|| pos.x >= (Game::SCREEN_WIDTH - GetSprite().getGlobalBounds().width / 2))
		{
			pos.x += 20;
			_velocity = 450.0f;
		}
		else
			_velocity = -450.0f;
	}
	
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		sf::Vector2f pos = this->GetPosition();

		
		if (pos.x <= GetSprite().getLocalBounds().width / 2
			|| pos.x >= (Game::SCREEN_WIDTH - GetSprite().getGlobalBounds().width / 2))
		{
			pos.x -= 20;
			_velocity = -450.0f;
			;
		}
		else
			_velocity = 450.0f;
	}

	else
	{
		if (_velocity > 0)_velocity -= 3.0f;
		if (_velocity < 0)_velocity += 3.0f;
	}
	
	

	GetSprite().move(_velocity * elapsedTime, 0);
}