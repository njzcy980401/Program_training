
#version 330 core

in vec2 Texcoords;
//in vec3 ourColor;

uniform sampler2D texture1;/*sampler采样器 纹理对象数据类型*/
uniform sampler2D texture2;
uniform float aMixValue;/*作为mix函数的第三个参数调整两个纹理的可见度*/

out vec4 color; //输出
void main()
{
    //color = vec4(ourColor.r, ourColor.g, ourColor.b, 1.0f); //透明度,需要调用函数
    //color = vec4(1.0f, 0.0f, 0.0f, 1.0f);

    color=mix(texture(texture1,Texcoords), vec4(1.0f, 0.0f, 0.0f, 1.0f),aMixValue);
    
}
