#include <iostream>

//GLEW 两个库

#define GLEW_STATIC
#include <GL/glew.h>

//GLFW
#include <GLFW/glfw3.h>

#include "Shader.h"

#include "SOIL2/SOIL2.h"
#include "SOIL2/stb_image.h"
const GLint WIDTH = 800, HEIGHT = 600; //窗口、GL变量
void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
float  mixValue = 0.0f;//设置初始值

int main()
{
    glfwInit(); //初始化设置
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //OpenGL3.3及以后的版本
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE); //用OpenGL，版本号，用来画图的
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // must for Mac 3.3版本之前的版本都兼容，向前兼容
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); //禁止窗口缩放
    
     GLFWwindow*window = glfwCreateWindow(WIDTH, HEIGHT, "H16000429", nullptr, nullptr); //创建窗口 是否全屏，是否多屏显示 共享
    
    if (nullptr == window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;//报错
    } //判断帧是否为空
    
    int screenWidth, screenHeight;
    glfwGetFramebufferSize( window, &screenWidth, &screenHeight); //获得实际的屏幕像素个数, 获得多少缓存空间 frame buffer: 1。color 2. depth buffer,会不会有遮挡 靠前 3. stenet 添框 阴影计算
    glfwMakeContextCurrent( window ); //创建窗口指定作为当前窗口
    
    glewExperimental = GL_TRUE;
    
    if (GLEW_OK != glewInit() )
    {
        std::cout << "Failed to initialise GLEW" << std::endl;
        return -1;
    } //初始化
    
 Shader shader = Shader("res/shaders/core.vs", "res/shaders/core.frag");
    
    GLfloat vertices[] =
    {
        //position       //coler            //texcoords
        0.5f, 0.5f,0.0f, 1.0f, 0.0f, 0.0f,  1.0f,1.0f,
        -0.5f,0.5f,0.0f, 0.0f, 1.0f, 0.0f,  0.0f,1.0f,
        -0.5f,-0.5f,0.0f,0.0f, 0.0f, 1.0f, 0.0f,0.0f,
        
        0.5f,-0.5f,0.0f, 1.0f, 0.0f, 0.0f,  1.0f,0.0f,
        0.5f, 0.5f,0.0f, 1.0f, 0.0f, 0.0f,  1.0f,1.0f,
        -0.5f,-0.5f,0.0f,0.0f, 0.0f, 1.0f, 0.0f,0.0f
    };
    //使用EBO画
    /*unsigned int indices[] =
    {
        0,1,2,
        0,2,3,
       
    };*/
    
    //transfer the data to the Graphics Card
    // 输入数据进入显卡
    GLuint VAO, VBO; //VAO将存在显存的数据与着色器联系在一起，即如何解读使用VBO中的数据
    glGenVertexArrays(1, &VAO); //生成一个对象，存在VAO地址里
    glGenBuffers(1, &VBO);  //将VAO与VBO绑定
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO); //GL_ARRAY_BUFFER存放顶点属性
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//static 表示静态不会写入
    
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);//读位置，读三个元素，每隔8个元素读一次
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));//读颜色，读三个元素，每隔8个元素读一次
    glEnableVertexAttribArray(1);
    
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6*sizeof(GLfloat)));//读纹理，读三个元素，每隔8个元素读一次
    glEnableVertexAttribArray(2);
    
    
   /* GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);*/
    
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    //两个纹理的固定申明
    GLuint texture1,texture2;
    int width,height;
    
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    unsigned char*image= SOIL_load_image("res/images/image1.png", &width, &height, 0, SOIL_LOAD_RGBA);//unsigned 非负数
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);//0 第零级图片 不断缩小
    glGenerateMipmap(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    SOIL_free_image_data(image);
    
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
    
    int i=1;
    while (!glfwWindowShouldClose (window) && i++)
    {
        
        glfwPollEvents();
        glViewport( 0, 0, screenWidth, screenHeight ); //映射到 不同屏幕 （起点左下角坐标位置，宽，高）
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear (GL_COLOR_BUFFER_BIT); //底色
        if (i % 1000 < 500) {
            //glBindTexture(GL_TEXTURE_2D, texture);  //前一半时间是第一张图，后一半时间是第二张图
            mixValue = 0.0f;
        }
        else {
            //glBindTexture(GL_TEXTURE_2D, texture1);
            mixValue = 1.0f;
        }
        shader.Use();
        
        //纹理的固定配置
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        
        GLuint texLoc= glGetUniformLocation(shader.Program,"texture1");
        glUniform1i(texLoc,0);
        GLuint texLoc1= glGetUniformLocation(shader.Program,"texture2");
        glUniform1i(texLoc1,1);
        processInput(window);
        
 
        
        //shader.setFloat("aMixValue", 0.1f);
       glUniform1f(glGetUniformLocation(shader.Program, "aMixValue"),mixValue);
        
        
        
        //glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        /*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);//第二个参数控制点的个数*/
        glDrawArrays(GL_TRIANGLES, 0, 6); //(图形，起点，几个)
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
        glfwSwapBuffers (window);
    }
    
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    
    glfwTerminate();
    
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    
    /*if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        mixValue += 1.0f; // change this value accordingly (might be too slow or too fast based on system hardware)
        if (mixValue >= 1.0f)
            mixValue = 1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        mixValue -= 1.0f; // change this value accordingly (might be too slow or too fast based on system hardware)
        if (mixValue <= 0.0f)
            mixValue = 0.0f;
    }*/
    //--------------------------------------------------------------------------
}
