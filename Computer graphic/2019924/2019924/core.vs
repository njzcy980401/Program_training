#version 330 core
layout(location = 0) in vec3 position;//输入三个数的浮点数x,y,z
//!
layout(location = 1) in vec3 color;
out vec3 ourColor;
void main()
{
gl_Position = vec4(position.x, position.y, position.z, 1.0f);//齐次坐标系
ourColor=color;
}
