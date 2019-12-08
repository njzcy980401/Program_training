

#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>

class Shader
{
    GLuint vertex, fragment;
public:
    GLuint Program;
    //Constructor
    Shader(const GLchar *vertexPath, const GLchar *fragmentPath)
    {
        //1.Retrieve the source code 获取文件中的源代码
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        
        vShaderFile.exceptions(std::ifstream::badbit);
        
        fShaderFile.exceptions(std::ifstream::badbit);
        
        try
        {
            //Open File
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            
            //Stream the file
            std::stringstream vShaderStream, fShaderStream;
            vShaderStream<<vShaderFile.rdbuf();
            fShaderStream<<fShaderFile.rdbuf();
            
            //Close the file
            vShaderFile.close();
            fShaderFile.close();
            
            //Convert to the string type
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
            
        }
        
        catch(std::ifstream::failure e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
        }
//        const GLchar *vShaderCode = vertexCode.c_str();
//        const GLchar *fShaderCode = fragmentCode.c_str();
        const GLchar *vShaderCode = vertexCode.c_str();
        const GLchar *fShaderCode = fragmentCode.c_str();
        
        
        //2.Compile shaders
        vertex = glCreateShader(GL_VERTEX_SHADER);//生成顶点着色器
        glShaderSource(vertex, 1, &vShaderCode, NULL);//导入一个文件成顶点着色器
        glCompileShader(vertex);
        
        GLint success;
        GLchar infoLog[512];
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        
        if (!success)
        {
            glGetShaderInfoLog(vertex, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        
        fragment = glCreateShader(GL_FRAGMENT_SHADER);//生成片源着色器
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        
        if (!success)
        {
            glGetShaderInfoLog(fragment, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        
        //create the program and link the program
        this->Program = glCreateProgram();
        
        glAttachShader(this->Program, vertex);
        glAttachShader(this->Program, fragment);
        glLinkProgram(this->Program);
        
        glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
        
        if (!success)
        {
            glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
            std::cout << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }
        
    }
    //Deconstructor
    ~Shader()
    {
        glDetachShader(this->Program, vertex);
        glDetachShader(this->Program, fragment);
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        glDeleteProgram(this->Program);
    }
    
    void Use()
    {
        glUseProgram(this->Program);
    }
};
