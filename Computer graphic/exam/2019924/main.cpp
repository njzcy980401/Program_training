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

#include "SOIL2/SOIL2.h"
#include "SOIL2/stb_image.h"

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode); //关于键盘操作的
void DoMovement();
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
void processInput(GLFWwindow* window);
float mixValue=0.0f;
const GLint WIDTH = 800, HEIGHT = 600; //新建窗口
bool keys[1024]; //保留键盘上的功能的
GLfloat translation1;
GLfloat translation2;
GLfloat translation3;
GLfloat translation4;
GLfloat translation5;
Camera camera(glm::vec3(0.0f, 2.0f, 2.0f));//放2.0使得人往后挪
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

GLfloat lastX = WIDTH / 2;
GLfloat lastY = HEIGHT / 2;
bool firstMouse = true;

glm::vec3 lightPos=glm::vec3(0.0f,0.0f,0.0f);
int main() {
    glfwInit(); //初始化
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //提供一个参数，设置一个值
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //OpenGL 3.3 version
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //打开OpenGL的类型CORE_PROFILE
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // must for Mac 向前兼容
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);//禁止缩放
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "H16000429", nullptr, nullptr);//后面两个属性--是否全屏、是否共享

    if (nullptr == window) { //是否生成窗口
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
    }

    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight); //实际显存需要的大小空间；
    glfwMakeContextCurrent(window); //创建窗口作为当前窗口
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetCursorPosCallback(window, MouseCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetScrollCallback(window, ScrollCallback);//传递函数
    glewExperimental = GL_TRUE;
    glfwSetKeyCallback(window, KeyCallback);
    if (GLEW_OK != glewInit()) { //是否正常初始化
    std::cout << "Failed to initialise GLEW" << std::endl;
    glfwTerminate();
    return -1;
    }
    //深度测试
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    Shader shader = Shader("res/shaders/core.vs", "res/shaders/core.frag");
    Shader lightShader=Shader("res/shaders/light.vs", "res/shaders/light.frag");
    Light lightModel = Light();
     GLfloat vertices[] = {
    0.5f, -0.5f, 0.5f,  1.0f, 0.0f, 0.0f,0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, 0.5f,  1.0f, 0.0f, 0.0f,0.0f, 1.0f, 0.0f, -1.0f, 1.0f,
    0.5f,  -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,0.0f, 1.0f, 0.0f, 1.0f, -1.0f,
             
    -0.5f,  -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,0.0f, 1.0f, 0.0f, -1.0f,-1.0f,
    0.5f,  -0.5f, -0.5f, 1.0f, 0.0f,0.0f,0.0f, 1.0f, 0.0f, 1.0f, -1.0f,
    -0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,0.0f, 1.0f, 0.0f, -1.0f, 1.0f
             
         };
    
    


    GLuint VAO, VBO;//VAO将存在显存的数据与着色器联系在一起，即如何解读使用VBO中的数据
    glGenVertexArrays(1, &VAO);//生成一个对象，存在VAO地址里
    glGenBuffers(1, &VBO);
    //将VAO与VBO绑定
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);//GL_ARRAY_BUFFER存放顶点属性
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), (GLvoid*)(9 * sizeof(GLfloat)));
    glEnableVertexAttribArray(3);
    
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::perspective(glm::radians(camera.GetZoom()),
                                            static_cast<GLfloat>(screenWidth) / static_cast<GLfloat>(screenHeight), 0.1f,1000.0f);
    

    
    GLuint texture1,texture2;
    int width,height;
    
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    unsigned char*image= SOIL_load_image("res/images/image1.jpg", &width, &height, 0, SOIL_LOAD_RGBA);//unsigned 非负数
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);//0 第零级图片 不断缩小
    glGenerateMipmap(GL_TEXTURE_2D);
    
    
    
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    image= SOIL_load_image("res/images/image2.JPG", &width, &height, 0, SOIL_LOAD_RGBA);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);//0 第零级图片 不断缩小
    glGenerateMipmap(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    SOIL_free_image_data(image);

    while (!glfwWindowShouldClose(window)){
        GLfloat currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;
        glfwPollEvents();
        DoMovement();
        glViewport(0, 0, screenWidth, screenHeight);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        lightShader.Use();
        glm::mat4 transform = glm::mat4(1.0f);//定义一个4阶矩阵
        transform = glm::translate(transform, glm::vec3(translation1, translation2, 0.0f));
        transform=glm::translate(transform, lightPos);
        transform=glm::scale(transform, glm::vec3(0.2f,0.2f,0.2f));
        lightPos=glm::vec3(0.0f,0.0f,3.0f);
       
           if (keys [GLFW_KEY_1]) {
               translation3 +=0.01f;
               if (translation3>0){
                   camera.ProcessMovement(RIGHT, deltaTime);
               }
              
           }
           if (keys [GLFW_KEY_2]) {
               translation3-=0.01f;
              if (translation3<0){
                  camera.ProcessMovement(LEFT, deltaTime);
              }
           }
           /*if (keys [GLFW_KEY_3]) {
               translation4+=0.01f;
               
           }
           if (keys [GLFW_KEY_4]) {
               translation4-=0.01f;
               
           }*/
        if (keys [GLFW_KEY_5]) {
            translation5+=0.01f;
            
        }
        if (keys [GLFW_KEY_6]) {
            translation5-=0.01f;
            
        }
      lightPos=glm::vec3(lightPos.x+translation3,lightPos.y+translation4,lightPos.z+translation5); glUniformMatrix4fv(glGetUniformLocation(lightShader.Program,"model"),1,GL_FALSE,glm::value_ptr(transform));
        view = camera.GetViewMatrix(); //获取相机矩阵
        //lightPos=glm::rotate(lightPos, glm::radians(80.0f)*static_cast<GLfloat>(glfwGetTime()), glm::vec3(1.0f,1.0f,1.0f));
    glUniformMatrix4fv(glGetUniformLocation(lightShader.Program,"view"),1,GL_FALSE,glm::value_ptr(view));
        
        projection = glm::perspective(glm::radians(camera.GetZoom()),
        static_cast<GLfloat>(screenWidth) / static_cast<GLfloat>(screenHeight), 0.1f, 1000.0f);
    glUniformMatrix4fv(glGetUniformLocation(lightShader.Program,"projection"),1,GL_FALSE,glm::value_ptr(projection));
        
        lightModel.Draw();
        
        
        shader.Use();
        processInput(window);
        
        
        glUniform1f(glGetUniformLocation(shader.Program,"p"),64.0f);
    glUniform3f(glGetUniformLocation(shader.Program,"LightPos"),lightPos.x,lightPos.y,lightPos.z);
    glUniform3f(glGetUniformLocation(shader.Program,"ViewPos"),camera.GetPosition().x,camera.GetPosition().y,camera.GetPosition().z);
        
         transform = glm::mat4(1.0f);//定义一个4阶矩阵
        transform = glm::translate(transform, glm::vec3(0.0f, 0.0f, -3.0f));
        
        transform = glm::scale(transform, glm::vec3(8.0f, 8.0f, 8.0f));//对矩阵进行伸缩变换
        //transform = glm::translate(transform, glm::vec3(0.0f, 2.0f, 0.0f));//平移变换
        
        
        
        GLuint transLoc = glGetUniformLocation(shader.Program, "model");//transform的位置
        glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(transform));//将位置赋值给他去做变换
        
        //view = camera.GetViewMatrix(); //获取相机矩阵
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        GLuint texLoc= glGetUniformLocation(shader.Program,"texture1");
        glUniform1i(texLoc,0);
        GLuint texLoc1= glGetUniformLocation(shader.Program,"texture2");
        glUniform1i(texLoc1,1);
        processInput(window);
        
        glUniform1f(glGetUniformLocation(shader.Program, "aMixValue"),mixValue);
        
        
        
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
        glfwSwapBuffers (window);
  }
            glDeleteVertexArrays(1, &VAO);
            glDeleteBuffers(1, &VBO);
            glfwTerminate();
            
            return 0;
        }

void DoMovement()
{
    if (keys[GLFW_KEY_W ]|| keys[GLFW_KEY_UP])
    {
        camera.ProcessMovement(FORWARD, deltaTime);
    }else if (keys[GLFW_KEY_S ]|| keys[GLFW_KEY_DOWN])
    {
        camera.ProcessMovement(BACKWARD, deltaTime);
    }else if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
    {
        camera.ProcessMovement(LEFT, deltaTime);
    }else if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
    {
        camera.ProcessMovement(RIGHT, deltaTime);
    }
}

void MouseCallback(GLFWwindow *window, double xPos, double yPos)
{
    if (firstMouse)
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }
    GLfloat xOffest = xPos - lastX;
    GLfloat yOffest = yPos - lastY;
    
    lastX = xPos;
    lastY = yPos;
    
    camera.ProcessOrientation(xOffest, yOffest);
}
void ScrollCallback(GLFWwindow *window, double xOffset, double yOffset)
{
    camera.ProcessFov(yOffset);
}
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode) {
    
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
        translation1 +=0.01f;
        
    }
    if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
        translation1 -=0.01f;
        
    }
    if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
        translation2 +=0.01f;
       
    }
    if (key == GLFW_KEY_4 && action == GLFW_PRESS) {
        translation2 -=0.01f;
        
    }
    
    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS) {
            keys[key] = true;
        }
        else if (action == GLFW_RELEASE) {
            keys[key] = false;
        }
        
    }
    
}


