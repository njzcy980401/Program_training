

#include <iostream>
//GLEW
#define GLEW_STATIC
#include <GL/glew.h>
//GLFW
#include <GLFW/glfw3.h>
#include "Shader.h"
#include <glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "Camera.h"
#include "Light.h"
#include "Model.h"



void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow *window, double xPos, double yPos);
void ScrollCallback(GLFWwindow *window, double xOffset, double yOffset);
void DoMovement();

bool keys[1024];
const GLint WIDTH = 800, HEIGHT = 600;
Camera camera(glm::vec3(0.0f, 0.0f, 2.0f));

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

GLfloat lastX = WIDTH/2;
GLfloat lastY = HEIGHT/2;

bool firstMouse = true;
glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 0.0f);

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    GLFWwindow * window = glfwCreateWindow(WIDTH, HEIGHT, "H16000511", nullptr, nullptr);
    
    if (nullptr == window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetCursorPosCallback(window, MouseCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
    
    glfwMakeContextCurrent(window);
    
    glewExperimental = GL_TRUE;
    
    if (GLEW_OK != glewInit()) {
        std::cout << "Failed to initialise GLEW" << std::endl;
        glfwTerminate();
        return -1;
    }
    Shader lightShader = Shader("res/shaders/light.vs","res/shaders/light.frag");
    
    Light lightModel = Light();
    
    Shader shader = Shader("res/shaders/core.vs","res/shaders/core.frag");
    Model robot("res/models/nanosuit.obj");
    
    
    //Light lightModel1 = Light();
    
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::perspective(glm::radians(camera.GetZoom()), static_cast<GLfloat>(screenWidth)/static_cast<GLfloat>(screenHeight), 0.1f, 1000.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    
    
    
    while (!glfwWindowShouldClose(window)) {
        GLfloat currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;
        
        glfwPollEvents();
        DoMovement();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, screenWidth, screenHeight);
        view = camera.GetViewMatrix();
        glm::mat4 transform = glm::mat4(1.0f);
        lightShader.Use();
        lightPos = glm::vec3(20.0f, 0.0f, 0.0f);
        lightPos = glm::rotate(lightPos, glm::radians(20.0f)*static_cast<GLfloat>(glfwGetTime()), glm::vec3(1.0f, 1.0f, 1.0f));
        transform = glm::scale(transform, glm::vec3(0.1f, 0.1f, 0.1f));
        transform = glm::translate(transform, lightPos);
        glUniformMatrix4fv(glGetUniformLocation(lightShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(transform));
        glUniformMatrix4fv(glGetUniformLocation(lightShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(lightShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        
        lightModel.Draw();
        shader.Use();
        transform = glm::mat4(1.0f);
        transform = glm::scale(transform, glm::vec3(0.2f, 0.2f, 0.2f));
        GLuint transLoc = glGetUniformLocation(shader.Program, "model");
        glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(transform));
        
        GLuint viewLoc = glGetUniformLocation(shader.Program, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        
        GLuint projLoc = glGetUniformLocation(shader.Program, "projection");
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
        glUniform3f(glGetUniformLocation(shader.Program, "LightPos"), lightPos.x,lightPos.y,lightPos.z);
        glUniform3f(glGetUniformLocation(shader.Program, "ViewPos"), camera.GetPosition().x,camera.GetPosition().y,camera.GetPosition().z);
        glUniform1f(glGetUniformLocation(shader.Program, "material.shininess"), 128.0f);
        robot.Draw(shader);
        //glBindVertexArray(0);
        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}

void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if (key>=0 & key<1024) {
        if (action == GLFW_PRESS) {
            keys[key] = true;
        }else if (action == GLFW_RELEASE){
            keys[key] = false;
        }
    }
}

void DoMovement()
{
    if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP]) {
        camera.ProcessMovement(FORWARD, deltaTime);
    }
    if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN]) {
        camera.ProcessMovement(BACKWARD, deltaTime);
    }
    if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT]) {
        camera.ProcessMovement(LEFT, deltaTime);
    }
    if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT]) {
        camera.ProcessMovement(RIGHT, deltaTime);
    }
}

void MouseCallback(GLFWwindow *window, double xPos, double yPos)
{
    if (firstMouse) {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }
    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = yPos - lastY;
    
    lastX = xPos;
    lastY = yPos;
    
    camera.ProcessOrientation(xOffset, yOffset);
}
