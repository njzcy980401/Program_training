
#pragma once //或者， 计数
/* #ifndef Shader_h //如果还没定义出现过
 #define Shader_h
 
 /* #endif /* Shader_h */

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
    Shader(const GLchar*vertexPath,const GLchar*fragmentPath)
    {
        //1.Retrieve thesource code
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        vShaderFile.exceptions(std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::badbit);
        try{
            //open file
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            //stream the file
            std::stringstream vShaderStream,fShaderStream;
            vShaderStream<<vShaderFile.rdbuf();
            fShaderStream<<fShaderFile.rdbuf();
            
            //close the file
            vShaderFile.close();
            fShaderFile.close();
            
            //convert to the string type
            vertexCode = vShaderStream.str();
            fragmentCode= fShaderStream.str();
            
        }
        catch(std::ifstream::failure e){
            std::cout <<
            "ERROR::SHADER::FILE_NOT_SUCCESSFFULLY_READ" <<std::endl;
        }//报错
        const GLchar *vShaderCode = vertexCode.c_str();
        const GLchar *fShaderCode = fragmentCode.c_str();
        
        //2. compile shaders
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        
        
        GLint success;//编译是否成功
        GLchar infoLog[512];
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        
        if(!success) {
            glGetShaderInfoLog(vertex, 512, NULL, infoLog);
            std::cout<<
            "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog
            << std::endl;
        }
        
        GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        
        
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        
        if(!success) {
            glGetShaderInfoLog(fragment, 512, NULL, infoLog);
            std::cout<<
            "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog
            << std::endl;
        }
        
        //create the program and link the program
        
        this->Program =
        glCreateProgram();
        glAttachShader(this->Program, vertex);
        glAttachShader(this->Program, fragment);
        glLinkProgram(this->Program);
        
        glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
        
        if(!success) {
            
            glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
            std::cout<<
            "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog
            << std::endl;
        }
    }
    //Deconstructor
    ~Shader()
    {
        glDetachShader(this->Program,vertex);
        glDetachShader(this->Program,fragment);
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        glDeleteProgram(this->Program);
    }
    
    void Use()
    {
        glUseProgram(this->Program);
    }
};
