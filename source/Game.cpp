#include <GLFW/glfw3.h>
#include "Game.h"
#include <iostream>

bool Game::Init()
{
    return true;
}

void Game::Update(float deltaTime)
{
    auto& input = ene::Engine::GetInstance().GetInputManager();
    if (input.IsKeyPressed(GLFW_KEY_A))
    {
        std::cout << "A key is pressed." << std::endl;
    }
}

void Game::Destroy()
{
    
}  