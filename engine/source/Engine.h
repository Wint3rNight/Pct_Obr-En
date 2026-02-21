#pragma once
#include "input/InputManager.h"
#include <graphics/GraphicsAPI.h>
#include <memory>
#include <chrono>


struct GLFWwindow;
namespace ene
{
    class Application;
    class Engine
    {
    public:
        static Engine& GetInstance();
        
    private:
        Engine()=default;
        Engine(const Engine&)=delete;
        Engine(Engine&&)=delete;
        Engine& operator=(const Engine&)=delete;
        Engine& operator=(Engine&&)=delete;
    
    public:
        bool Init(int width, int height);
        void Run();
        void Destroy();
        void SetApplication(Application* app);
        Application* GetApplication();
        InputManager& GetInputManager();
        GraphicsAPI GetGraphicsAPI();
        
    private:
        std::unique_ptr<Application> m_application;
        std::chrono::high_resolution_clock::time_point m_lastTimePoint;
        GLFWwindow* m_window=nullptr;
        InputManager m_inputManager;
        GraphicsAPI m_graphicsAPI;
    };
}