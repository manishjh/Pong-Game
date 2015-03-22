#pragma once
#include "VisibleGameObject.h"

class PlayerPaddle : public VisibleGameObject
{
public:
	PlayerPaddle();
	~PlayerPaddle();

	void Update(float elaspedTime);
	void Draw(sf::RenderWindow& rw);
	static PlayerPaddle* AddPaddle();
	float GetVelocity() const;

private:
	float _velocity;
	float _maxVelocity;
};