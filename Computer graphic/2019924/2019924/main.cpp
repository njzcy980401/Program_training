#include <iostream>
//GLEW
#define GLEW_STATIC
#include <GL/glew.h>
//GLFW
#include <GLFW/glfw3.h>
const GLint WIDTH = 800, HEIGHT = 600;

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//设置版本
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//设置版本
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);//设置渲染模式
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // must for Mac，mac需要
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);//禁止缩放
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "H16000429",nullptr, nullptr);//创建窗口对象，存放相关数据
    
// next two lines are for mac retina display，适配macrbook retina屏幕
    int screenWidth, screenHeight;
    glfwGetFramebufferSize( window, &screenWidth, &screenHeight);
    
    if (nullptr == window)//驱动GLFW，判断是否生成窗口
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    //切换上下文，创建的窗口当作当前窗口
    glfwMakeContextCurrent( window );
    glewExperimental = GL_TRUE;
    if (GLEW_OK != glewInit() )
        //查看是否正常初始化窗口
    {
        std::cout << "Failed to initialise GLEW" << std::endl;
        return -1;
    }
    //设置视口
    glViewport( 0, 0, screenWidth, screenHeight );
    //渲染循环，判断窗口是否打开，如果打开则一直刷新屏幕
    while (!glfwWindowShouldClose (window)) {
        glfwPollEvents();//是否有事件
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//设置颜色 底色--- RGB+透明度（这里设置不透明）
        glClear (GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers (window);
        }
    //渲染结束
    glfwTerminate();
    return 0;
}
