

#pragma once

enum Camera_Movement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

const GLfloat YAW =-90.0f;//初始化 偏航角 左右
const GLfloat PITCH=0.0f;//俯仰角 上下
const GLfloat ZOOM =45.0f;//缩放
const GLfloat SPEED=6.0f;
const GLfloat SENSITIVITY=0.25f;
class Camera
{
public:
    Camera(glm::vec3 position = glm::vec3(0.0f,0.0f,0.0f), glm::vec3 up= glm::vec3(0.0f,1.0f,0.0f),GLfloat yaw=YAW,GLfloat pitch =PITCH)
    :front(glm::vec3(0.0f,0.0f,-1.0f)),zoom(ZOOM),movementSpeed(SPEED),sensitivity(SENSITIVITY)
    {
        this ->position = position;
        this ->worldUp=up;
        this ->yaw=yaw;
        this ->pitch=pitch;
        updateCameraVectors();
        
    }
    
    
    glm::mat4 GetViewMatrix()
    {
        //float radius = 10.0f;
        //float camX = sin(glfwGetTime()) * radius;
        //float camZ = cos(glfwGetTime()) * radius;
        return
        glm::lookAt(this->position,this->position+this->front,this->up);
        
        //glm::lookAt(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        
        // Camera is at (4,3,3), in World Space
        // and looks at the origin
        // Head is up (set to 0,-1,0 to look upside-down)
        //glm::LookAt函数需要一个位置、目标和上向量。
        
    }
    
    GLfloat GetZoom()
    {
        return this->zoom;
    }
    
    glm::mat4 model;
    

    
    glm::vec3 GetPosition(){
    return this->position;
}
    
    void ProcessMovement(Camera_Movement direction, GLfloat deltaTime)
    {
        GLfloat velocity= this->movementSpeed*deltaTime;
        if(direction==FORWARD){
            this->position+= this->front*velocity;
        }
        if(direction==BACKWARD){
            this->position-= this->front*velocity;
        }
        if(direction==RIGHT){
            this->position+= this->right*velocity;
        }
        if(direction==LEFT){
            this->position-= this->right*velocity;
        }
        
    }
    
    
    
    void ProcessOrientation(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch=true)
    {
        xOffset*= this->sensitivity;
        yOffset*= this->sensitivity;
        
        this->yaw+=xOffset;
        this->pitch-=yOffset;
        
        if(constrainPitch) {
            if(this->pitch>89.0f){
                this->pitch=89.0f;
            }
            if(this->pitch<-89.0f){
                this->pitch=-89.0f;
            }
        }
        
        updateCameraVectors();
    }
    
    void ProcessFov(GLfloat yOffset){
        if (zoom >= 1.0f && zoom <= 45.0f)
            zoom -= yOffset;
        if (zoom <= 1.0f)
            zoom = 1.0f;
        if (zoom >= 45.0f)
            zoom = 45.0f;
    }
    
private:
    glm::vec3 position;//相机位置
    glm::vec3 front;//坐标系
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;
    
    GLfloat yaw;//左右转90度
    GLfloat pitch;//俯仰角
    GLfloat zoom;//视域
    
    GLfloat movementSpeed;
    GLfloat sensitivity;
    //roll：degree of freedom
    
    void updateCameraVectors()
    {
        glm::vec3 front;
        front.x=cos(glm::radians(this->pitch))*cos(glm::radians(this->yaw));
        front.y=sin(glm::radians(this->pitch));
        front.z=cos(glm::radians(this->pitch))*sin(glm::radians(this->yaw));
        
        this->front=glm::normalize(front);
        this->right=glm::normalize(glm::cross(this->front,this->worldUp));
        this->up=glm::normalize(glm::cross(this->right,this->front));
    }
    
    
};

