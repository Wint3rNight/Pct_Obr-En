#include "Engine.h"
#include "Application.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace ene
{
    bool Engine::Init(int width, int height)
    {
        glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);
        
        if (!m_application)
        {
            return false;
        }
        
        if (!glfwInit())
        {
            return false;
        }
        
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
        
        m_window = glfwCreateWindow(width, height, "GDP Engine", nullptr, nullptr);
        
        if (!m_window)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return false;
        }
        
        glfwMakeContextCurrent(m_window);
        
        glewExperimental = true;
        if (glewInit() != GLEW_OK)
        {
            std::cout << "Failed to initialize GLEW" << std::endl;
            glfwTerminate();
            return false;
        }
        
        return m_application->Init();
    }
    
    void Engine::Run()
    {
        if (!m_application)
        {
            return;
        }
        
        m_lastTimePoint = std::chrono::high_resolution_clock::now();
        while (!glfwWindowShouldClose(m_window) && !m_application->NeedsToClose())
        {
            glfwPollEvents();
            
            auto now = std::chrono::high_resolution_clock::now();
            float deltaTime = std::chrono::duration<float>(now - m_lastTimePoint).count();
            m_lastTimePoint = now;
            
            m_application->Update(deltaTime);
            
            glfwSwapBuffers(m_window);
        }
    }
    
    void Engine::Destroy()
    {
        if (m_application)
        {
            m_application->Destroy();
            m_application.reset();
            glfwTerminate();
            m_window = nullptr;
        }
    }
    
    void Engine::SetApplication(Application* app)
    {
        m_application.reset(app);
    }
    
    Application* Engine::GetApplication()
    {
        return m_application.get();
    }
}
