
#pragma once

GLfloat vertices_light[] =
{
-0.5f, -0.5f, -0.5f,
0.5f, -0.5f, -0.5f,
0.5f,  0.5f, -0.5f,
0.5f,  0.5f, -0.5f,
-0.5f,  0.5f, -0.5f,
-0.5f, -0.5f, -0.5f,

-0.5f, -0.5f,  0.5f,
0.5f, -0.5f,  0.5f,
0.5f,  0.5f,  0.5f,
0.5f,  0.5f,  0.5f,
-0.5f,  0.5f,  0.5f,
-0.5f, -0.5f,  0.5f,

-0.5f,  0.5f,  0.5f,
-0.5f,  0.5f, -0.5f,
-0.5f, -0.5f, -0.5f,
-0.5f, -0.5f, -0.5f,
-0.5f, -0.5f,  0.5f,
-0.5f,  0.5f,  0.5f,

0.5f,  0.5f,  0.5f,
0.5f,  0.5f, -0.5f,
0.5f, -0.5f, -0.5f,
0.5f, -0.5f, -0.5f,
0.5f, -0.5f,  0.5f,
0.5f,  0.5f,  0.5f,

-0.5f, -0.5f, -0.5f,
0.5f, -0.5f, -0.5f,
0.5f, -0.5f,  0.5f,
0.5f, -0.5f,  0.5f,
-0.5f, -0.5f,  0.5f,
-0.5f, -0.5f, -0.5f,

-0.5f,  0.5f, -0.5f,
0.5f,  0.5f, -0.5f,
0.5f,  0.5f,  0.5f,
0.5f,  0.5f,  0.5f,
-0.5f,  0.5f,  0.5f,
-0.5f,  0.5f, -0.5f
};

class Light
{
public:
    Light()
    {
        glGenVertexArrays(1, &this->VAO);//生成一个对象，存在VAO地址里
        glGenBuffers(1, &this->VBO);
        //将VAO与VBO绑定
        glBindVertexArray(this->VAO);
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);//GL_ARRAY_BUFFER存放顶点属性
        
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_light), vertices_light, GL_DYNAMIC_DRAW);
        
        
        
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3* sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        
        
    }
    void Draw()
    {
        glBindVertexArray(this->VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
    }
private:
    GLuint VAO,VBO;
};
