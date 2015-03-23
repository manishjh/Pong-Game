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
	
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		
			_velocity = -800.0f;
	}
	
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{

		
	
			_velocity = 800.0f;
	}

	else
	{
		if (_velocity > 0)_velocity -= 1.50f;
		if (_velocity < 0)_velocity += 1.50f;
	}
	
	sf::Vector2f pos = this->GetPosition();

	if (pos.x <= GetSprite().getLocalBounds().width / 2 && _velocity<0
		|| pos.x >= (Game::SCREEN_WIDTH - GetSprite().getGlobalBounds().width / 2) && _velocity > 0)
	{
		_velocity = -_velocity; // Bounce by current velocity in opposite direction
	}


	GetSprite().move(_velocity * elapsedTime, 0);
}