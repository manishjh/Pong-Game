#include "stdafx.h"
#include "Game.h"
#include"MainMenu.h"
#include"GameBall.h"

void Game::Start(void)
{
	if (_gameState != Uninitialized)
		return;

	_mainWindow.create(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT, 32), "Pang!");


	PlayerPaddle *player1 = new PlayerPaddle();
	//player1->Load("images/paddle.png");
	player1->SetPosition((SCREEN_WIDTH / 2), (SCREEN_HEIGHT)-15);
	_gameObjectManager.Add("Paddle1", player1);
	GameBall *ball = new GameBall();
	//ball->Load("images/ball.png");
	ball->SetPosition((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2) - 15);
	_gameObjectManager.Add("Ball", ball);
	

	_gameState = Game::ShowingSplash;

	while (!IsExiting())
	{
		GameLoop();
	}

	_mainWindow.close();
}

bool Game::IsExiting()
{
	if (_gameState == Game::Exiting)
		return true;
	else
		return false;
}

sf::RenderWindow& Game::GetWindow()
{
	return _mainWindow;
}

const sf::Event& Game::GetInput()
{
	sf::Event currentEvent;
	_mainWindow.pollEvent(currentEvent);
	return currentEvent;
}

void Game::GameLoop()
{
	sf::Event currentEvent;
	_mainWindow.pollEvent(currentEvent);
	switch (_gameState)
   {
     case Game::ShowingMenu:
       {
	        ShowMenu();
	         break;
	   }
	 case Game::ShowingSplash:
	       {
	         ShowSplashScreen();
	         break;
	       }
	 case Game::Playing:
	       {
			   _mainWindow.clear(sf::Color(0, 0, 0));
			   _gameObjectManager.UpdateAll();
			   _gameObjectManager.DrawAll(_mainWindow);
			   _mainWindow.display();
	
				if (currentEvent.type == sf::Event::Closed) _gameState = Game::Exiting;
	
				if (currentEvent.type == sf::Event::KeyPressed)
					{
						if (currentEvent.key.code == sf::Keyboard::Escape) ShowMenu();
					}
	         }
	         break;
	      }
	   }
	

void Game::ShowSplashScreen()
{
	SplashScreen splashScreen;
	splashScreen.Show(_mainWindow);
	_gameState = Game::ShowingMenu;

}

void Game::ShowMenu()
{
	MainMenu mainMenu;
	MainMenu::MenuResult result = mainMenu.Show(_mainWindow);
	switch (result)
	{
	case MainMenu::Exit:
		_gameState = Game::Exiting;
		break;
	case MainMenu::Play:
		_gameState = Game::Playing;
		break;
	}
}
const GameObjectManager& Game::GetGameObjectManager()
{
	return Game::_gameObjectManager;
}


// static member variables need to be instantiated outside of the class
Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
GameObjectManager Game::_gameObjectManager;