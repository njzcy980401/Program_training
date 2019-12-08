#version 330 core
layout(location = 0) in vec3 position; //输入三个数的浮点数x,y,z
//layout(location = 1) in vec3 color;
layout(location = 2) in vec2 texcoords;
//uniform mat4 transform;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec2 Texcoords;
out vec3 ourColor; //输出
void main()
{
    
    gl_Position = projection*view*model*vec4(position,1.0f);
    //transform*vec4(position.x, position.y, position.z,1.0f); //齐次坐标系
    //ourColor= color;
    Texcoords=vec2(texcoords.x, 1-texcoords.y);
}
