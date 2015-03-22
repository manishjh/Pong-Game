#include "stdafx.h"
#include "PlayerPaddle.h"
#include "Game.h"
PlayerPaddle::PlayerPaddle() :
_velocity(0), _maxVelocity(600.0f)
{
	Load("images/paddle.png");
	assert(IsLoaded());

	GetSprite().setOrigin(GetSprite().getGlobalBounds().width / 2, GetSprite().getGlobalBounds().height -15);
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		_velocity -= 30.0f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		_velocity += 30.0f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		_velocity = 0.0f;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		_velocity -= 30.0f;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		_velocity += 30.0f;
	}
	if (_velocity > _maxVelocity)
		_velocity = _maxVelocity;

	if (_velocity < -_maxVelocity)
		_velocity = -_maxVelocity;

	sf::Vector2f pos = this->GetPosition();

	if (pos.x<GetSprite().getLocalBounds().width / 2
		|| pos.x >(Game::SCREEN_WIDTH - GetSprite().getLocalBounds().width / 2))
	{
		_velocity = -_velocity;
	}

	GetSprite().move(50*_velocity*elapsedTime, 0);
}
//PlayerPaddle* PlayerPaddle::AddPaddle()
//{
//	return dynamic_cast<PlayerPaddle*>(Game::GetGameObjectManager().Get("Paddle1"));
//}