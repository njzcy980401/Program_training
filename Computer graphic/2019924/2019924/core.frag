#version 330 core
in vec3 ourColor;
out vec4 color;//输出
void main()
{
color = vec4(ourColor.r, ourColor.g, ourColor.b, 1.0f);
//color = vec4(1.0f, 1.0f, 0.0f, 0.9f);
}
