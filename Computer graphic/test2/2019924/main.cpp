//固定配置
#include <iostream>
#define GlEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <cmath>
//申明窗口大小常量
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//顶点着色器源代码
const GLchar*vertexShadersource = "#version 330 core\n"//设置版本为330
"layout (location = 0) in vec3 aPos;\n"//顶点位置参数
"layout (location = 1) in vec3 aColor;\n"//顶点颜色d参数
"out vec3 ourColor;\n"//向片段着色器传递颜色参数
"void main ()\n"
"{\n"
"   gl_Position = vec4(aPos.x, -aPos.y, aPos.z, 1.0);\n"
"   ourColor = aColor;\n"
"}\0";

//片段着色器源代码，橘色
const GLchar*fragmentShader1Source = "#version 330 core\n"//设置版本为330
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"//接收顶点着色器的的颜色参数
//在程序中控制着色程序的颜色
//"uniform vec4 ourColor;\n"
"void main ()\n"
"{\n"
"   FragColor = vec4(ourColor, 1.0f);\n"
//"   FragColor = ourColor;\n"
"}\n\0";

//片段着色器源代码，黄色
/*const GLchar*fragmentShader2Source = "#version 330 core\n"//设置版本为330
"out vec4 FragColor;\n"
"void main ()\n"
"{\n"
"   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"//输出为橘色
"}\n\0";*/


int main()
{
    glfwInit();//初始化
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//设置版本
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//设置版本
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//渲染模式设置
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);//must for mac
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);//禁止缩放
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "H16000429", nullptr, nullptr);//设置窗口大小，名称
    
    // next two lines are for mac retina display，适配macrbook retina屏幕
    int screenWidth, screenHeight;
    glfwGetFramebufferSize( window, &screenWidth, &screenHeight);

    //
    if(window == nullptr)//判断是否生成窗口
    {
        std::cout<<"Failed to create GLFW window"<<std::endl;
        return -1;
    }
    //切换上下文，创建的窗口当作当前窗口
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    
    if (GLEW_OK != glewInit()) //判断是否正常初始化
    {
        
        std::cout << "Failed to initialise GLEW" << std::endl;
        return -1;}
    glViewport(0, 0, screenWidth, screenHeight);//把显存内容映射到屏幕的过程 参数 0，0 是左下角 右边是右上角  左下角坐标（0，0），右上角（screenWidth, screenHeight）
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        
    
    //编译顶点着色器源代码
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShadersource,NULL);
    glCompileShader(vertexShader);
    
    //编译状态监测
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout<<"ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"<<infoLog<<std::endl;
    }
    
    //编译片段着色源代码1
    int fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader1, 1, &fragmentShader1Source,NULL);
    glCompileShader(fragmentShader1);
    
    //编译情况监测
    glGetShaderiv(fragmentShader1, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader1, 512, NULL, infoLog);
        std::cout<<"ERROR::SHADER1::FRAGMENT::COMPILATION_FAILED\n"<<infoLog<<std::endl;
    }
    
    //连接着色程序1
    int shaderProgram1 = glCreateProgram();
    glAttachShader(shaderProgram1, vertexShader);
    glAttachShader(shaderProgram1, fragmentShader1);
    glLinkProgram(shaderProgram1);
    
    //判断连接状态
    glGetProgramiv(shaderProgram1, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shaderProgram1, 512, NULL, infoLog);
        std::cout<<"ERROR::SHADER1::PROGRAM::LINKING_FAILED\n"<<infoLog<<std::endl;
        
    }
    
    
    //编译片段着色源代码2
    /*int fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader2, 1, &fragmentShader2Source,NULL);
    glCompileShader(fragmentShader2);
    
    //编译情况监测
    glGetShaderiv(fragmentShader2, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader2, 512, NULL, infoLog);
        std::cout<<"ERROR::SHADER2::FRAGMENT::COMPILATION_FAILED\n"<<infoLog<<std::endl;
    }
    
    //连接着色程序2
    int shaderProgram2 = glCreateProgram();
    glAttachShader(shaderProgram2, vertexShader);
    glAttachShader(shaderProgram2, fragmentShader2);
    glLinkProgram(shaderProgram2);
    
    //判断连接状态
    glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shaderProgram2, 512, NULL, infoLog);
        std::cout<<"ERROR::SHADER::PROGRAM::LINKING_FAILED\n"<<infoLog<<std::endl;
        
    }*/
    //释放三个着色器对象
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader1);
    //glDeleteShader(fragmentShader1);
    
    //第一个三角形的顶点坐标
    float  firstTriangle[] = {
           // positions         // colors
            0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
           -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
            0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,   // top
        
         0.5f, 0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
         -0.5f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,// top
        
        0.5f, 0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
        -0.5f, 0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
         0.0f,  1.0f, 0.0f,  0.0f, 0.0f, 1.0f// top
        
        

       };
    //第二个三角形的顶点坐标
    /*float secondTriangle[] = {
        0.0f, -0.5f, 0.0f,  // left
        0.9f, -0.5f, 0.0f,  // right
        0.45f, 0.5f, 0.0f   // top
    };*/
    
    //设置顶点缓存对象，顶点数组对象
    unsigned int VBOs[2], VAOs[2];
    glGenVertexArrays(2, VAOs);
    glGenBuffers(2,VBOs);
    
    //第一个顶点三角形
    glBindVertexArray(VAOs[0]);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
    
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    //第二个顶点三角形
    /*glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3* sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);*/
    

//循环渲染
while (!glfwWindowShouldClose(window)){
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    //画第一个三角形
    glUseProgram(shaderProgram1);
    glBindVertexArray(VAOs[0]);
    
    // update shader uniform
    /*float timeValue = glfwGetTime();
    float greenValue = sin(timeValue) / 2.0f + 0.5f;
    int vertexColorLocation = glGetUniformLocation(shaderProgram1, "ourColor");
    glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);*/
    
    
    glDrawArrays(GL_TRIANGLES, 0, 9);
    
    
    //画第二个三角形
    /*glUseProgram(shaderProgram2);
    glBindVertexArray(VAOs[1]);
    glDrawArrays(GL_TRIANGLES, 0, 3);*/
    
    glfwSwapBuffers(window);
    glfwPollEvents();
}
    //停止渲染
glfwTerminate();
return 0;
}
    
    
    
    

