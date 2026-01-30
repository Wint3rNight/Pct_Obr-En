#include "Game.h"
#include <iostream>

bool Game::Init()
{
    return true;
}

void Game::Update(float deltaTime)
{
    std::cout << "cur delta " << deltaTime << std::endl;
}

void Game::Destroy()
{
    
}  