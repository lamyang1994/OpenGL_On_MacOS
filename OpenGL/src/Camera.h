#pragma once

#include "GLFW/glfw3.h"
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"

enum CameraMovement{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// default camera setting
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;

class Camera{    
private:
    glm::vec3 m_Position, m_Front, m_Up, m_Right, m_WordUp;
    float m_Yaw, m_Pitch;
    float m_Speed, m_Sensitivity, m_Zoom;

public:
    Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH, float zoom = ZOOM);
    ~Camera();
    
    void ProcessKeyboard(CameraMovement direction, float deltaTime);
    void ProcessMouseMovement(float offset_x, float offset_y, GLboolean constrainPitch = true);
    void ProcessMouseScroll(float offset);
    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(m_Position, m_Position + m_Front , m_Up);
    }

    float GetZoom()
    {
        return glm::radians(m_Zoom);
    }

    inline glm::vec3 GetPos() const { return m_Position; }
    inline glm::vec3 GetFront() const { return m_Front; }

private:
    void updateCameraVectors();

};
