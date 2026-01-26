#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <string>

struct Vec2
{
    float x=0.0f; 
    float y=0.0f;
};

Vec2 offset;


void keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        switch (key)
        {
        case GLFW_KEY_UP:
            offset.y += 0.01f;
            break;
        case GLFW_KEY_DOWN:
            offset.y -= 0.01f;
            break;
        case GLFW_KEY_LEFT:
            offset.x -= 0.01f;
            break;
        case GLFW_KEY_RIGHT:
            offset.x += 0.01f;
            break;
        default:
            break;
        }
    }
}

int main() 
{
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
    
    glfwSetKeyCallback(window, keyCallback);
    
    glfwSetWindowPos(window, 200, 200);
    //connect code to window
    glfwMakeContextCurrent(window);
    
    //load opengl functions using glew
    glewExperimental = GL_TRUE; 
    if (glewInit() != GLEW_OK) {
        glfwTerminate();
        return -1;
    }
    // shader source strings
    std::string vertexShaderSource = R"(
        #version 330 core
        layout(location = 0) in vec3 posi;
        layout(location = 1) in vec3 color;
        
        uniform vec2 uOffset;
        
        out vec3 vColor;

        void main()
        {
            vColor = color; 
            gl_Position = vec4(posi.x + uOffset.x, posi.y + uOffset.y, posi.z, 1.0);
        }
    )";
    // compile vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vertexShaderCStr = vertexShaderSource.c_str();
    glShaderSource(vertexShader, 1, &vertexShaderCStr, nullptr);
    glCompileShader(vertexShader);
    // check for vertex errors
    GLint success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cerr << "ERROR:VERTEX_SHADER_COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader source
    std::string fragmentShaderSource = R"(
        #version 330 core
        out vec4 fragColor;

        in vec3 vColor;
        uniform vec4 uColor;

        void main()
        {
            fragColor = vec4(vColor, 1.0)*uColor;
        }
    )";
    // compile fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentShaderSourceCStr = fragmentShaderSource.c_str();
    glShaderSource(fragmentShader, 1, &fragmentShaderSourceCStr, nullptr);
    glCompileShader(fragmentShader);
    // check for fragment errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cerr << "ERROR:FRAGMENT_SHADER_COMPILATION_FAILED\n" << infoLog << std::endl;
    }  
    // link shaders to shader program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "ERROR:SHADER_PROGRAM_LINKING_FAILED\n" << infoLog << std::endl;
    }
    // shaders are linked into program, can delete them now
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    // vertex data
    std::vector<float> vertices = 
    {
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f
    };
    // index data
    std::vector<unsigned int> indices = 
    {
        0, 1, 2,
        2, 3, 0
    };

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, false, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    GLint uColorLoc = glGetUniformLocation(shaderProgram, "uColor");
    GLint uOffsetLoc = glGetUniformLocation(shaderProgram, "uOffset");
    
    //keep running 
    while (!glfwWindowShouldClose(window)) {
        //rendering commands here(back buffer)
        glClearColor(0.1f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(shaderProgram);
        glUniform4f(uColorLoc, 1.0f, 1.0f, 1.0f, 1.0f); 
        glUniform2f(uOffsetLoc, offset.x, offset.y);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        //glBindVertexArray(0);
        
        //show frame and check for events(front buffer)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    //cleanup
    glfwTerminate();
    return 0;
}