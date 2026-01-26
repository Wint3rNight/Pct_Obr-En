#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main() {
    //force x11 to keep things stable on linux(prevents wayland glitches)
    glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11); 
    
    //startup glfw
    if (!glfwInit())
    {
        return -1;
    }
    //modern openGL
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 

    //create window
    GLFWwindow* window = glfwCreateWindow(1280, 720, "GDP Engine", nullptr, nullptr);
    if (!window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }   
    
    //glfwSetWindowPos(window, 200, 200);
    //connect code to window
    glfwMakeContextCurrent(window);
    
    //load opengl functions using glew
    glewExperimental = GL_TRUE; 
    if (glewInit() != GLEW_OK) {
        glfwTerminate();
        return -1;
    }
    //keep running 
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.1f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        //show frame and check for events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    //cleanup
    glfwTerminate();
    return 0;
}