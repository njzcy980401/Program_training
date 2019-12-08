#version 330 core

//in vec2 Texcoords;
in vec3 ourColor;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D texture1;/*sampler采样器 纹理对象数据类型*/
uniform sampler2D texture2;
uniform float aMixValue;/*作为mix函数的第三个参数调整两个纹理的可见度*/
uniform float p;
uniform vec3 LightPos;
uniform vec3 ViewPos;

out vec4 color; //输出
void main()
{
    //color = vec4(ourColor.r, ourColor.g, ourColor.b, 1.0f); //透明度,需要调用函数
    color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
    
    //color=mix(texture(texture1,Texcoords),texture(texture2,Texcoords),aMixValue);
    
    //ambient
    float Ia = 0.8f;
    vec3 ambient =0.4f*Ia*color.rgb;
    
    //diffuse漫反射
    vec3 lightDir=normalize(LightPos-FragPos);
    vec3 norm=normalize(Normal);
    float diff =0.6f*Ia*max(dot(norm,lightDir),0.0f);
    vec3 diffuse=diff*color.rgb;
    
    //specular
    vec3 viewDir = normalize(ViewPos-FragPos);
    vec3 halfAngle=normalize(viewDir+lightDir);
    float spec= 3.0f*pow(max(dot(norm,halfAngle),0.0f),p);
    vec3 specular=spec*color.rgb;
    
    color=vec4(ambient+diffuse+specular,1.0f);
    
}
