#version 330 core
layout(location = 0) in vec3 position; //输入三个数的浮点数x,y,z
//layout(location = 1) in vec3 color;
layout(location = 1) in vec3 normal;
//layout(location = 2) in vec2 texcoords;
//layout(location = 2) in vec3 normal;
layout(location = 2) in vec2 texCoords;
//uniform mat4 transform;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

//out vec2 Texcoords;
out vec3 ourColor; //输出
out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoords;
void main()
{
    
    gl_Position = projection*view*model*vec4(position,1.0f);
    //transform*vec4(position.x, position.y, position.z,1.0f); //齐次坐标系
    TexCoords=texCoords;
    //Texcoords=vec2(texcoords.x, 1-texcoords.y);
    Normal=mat3(transpose(inverse(model)))*normal;
    FragPos=vec3(model*vec4(position,1.0f));
}

