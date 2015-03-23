#pragma once
#include "visiblegameobject.h"
#include<random>

class GameBall :
	public VisibleGameObject
{
public:
	GameBall();
	virtual ~GameBall();
	void Update(float);

private:
	float _velocity;
	float _angle;
	float _elapsedTimeSinceStart;
	
	float LinearVelocityX(float angle);
	float LinearVelocityY(float angle);
};
