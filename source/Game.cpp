#include "Game.h"
#include <GLFW/glfw3.h>
#include <iostream>

bool Game::Init()
{
    std::string vertexShaderSource=R"(
        #version 330 core
        layout(location = 0) in vec3 position;
        layout(location=1) in vec3 color;
            
        out vec3 vColor;
        
        void main()
        {
            vColor=color;
            gl_Position=vec4(position.x,position.y,position.z,1.0);
        }
    )";
    std::string fragmentShaderSource=R"(
        #version 330 core
        out vec4 fragColor;
        in vec3 vColor;
        void main()
        {
            fragColor = vec4(vColor, 1.0);
        }
    )";
    
    auto graphicsAPI = ene::Engine::GetInstance().GetGraphicsAPI();
    auto shaderProgram = graphicsAPI.CreateShaderProgram(vertexShaderSource,fragmentShaderSource); 
    m_material.SetShaderProgram(shaderProgram);
    
    std::vector<float> vertices = 
    {
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f 
    };
    
    std::vector<unsigned int> indices = 
    {
        0, 1, 2,
        0, 2, 3
    };
    
    ene::VertexLayout vertexLayout;
    
    //posi
    vertexLayout.elements.push_back({
        0, //index
        3, //size
        GL_FLOAT, //type
        0 //offset
    });
    //color
    vertexLayout.elements.push_back({
        1, //index
        3, //size
        GL_FLOAT, //type
        3*sizeof(float) //offset
    });
    vertexLayout.stride = 6*sizeof(float);
    
    m_mesh=std::make_unique<ene::Mesh>(vertexLayout, vertices, indices);
    
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