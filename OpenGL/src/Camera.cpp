#include "Camera.h"
#include <iostream>

Camera::Camera(glm::vec3 pos, glm::vec3 up, float yaw, float pitch, float zoom)
    :m_Front(glm::vec3(0.0f, 0.0f, -1.0f)), m_Speed(SPEED), m_Sensitivity(SENSITIVITY) 
{
    m_Position = pos; 
    m_WordUp = up;
    m_Yaw = yaw;
    m_Pitch = pitch; 
    m_Zoom = zoom;
    // m_Right and m_Up is initialized here 
    Camera::updateCameraVectors();
}

Camera::~Camera()
{
}

void Camera::ProcessKeyboard(CameraMovement direction, float deltaTime)
{
    float velocity = m_Speed * deltaTime;
    if (direction == FORWARD)
        m_Position += m_Front * velocity;
    if (direction == BACKWARD)
        m_Position -= m_Front * velocity;
    if (direction == LEFT)
        m_Position -= m_Right * velocity;
    if (direction == RIGHT)
        m_Position += m_Right * velocity;
}

void Camera::ProcessMouseMovement(float offset_x, float offset_y, GLboolean constrainPitch)
{
    m_Yaw  += offset_x * m_Sensitivity;
    m_Pitch += offset_y * m_Sensitivity;
    
    std::cout << constrainPitch << std::endl;
    if (constrainPitch)
    {
        if (m_Pitch > 89.0f)
            m_Pitch = 89.0;
        else if (m_Pitch < -89.0)
            m_Pitch = -89.0;
    }
    updateCameraVectors();
}

void Camera::ProcessMouseScroll(float offset)
{
    if (m_Zoom >= 1.0f && m_Zoom <= 45.0f)
        m_Zoom -= offset;
    if (m_Zoom <= 1.0f)
        m_Zoom = 1.0f;
    if (m_Zoom >= 45.0f)
        m_Zoom = 45.0f;
}

void Camera::updateCameraVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(m_Pitch)) * glm::cos(glm::radians(m_Yaw));
    front.y = sin(glm::radians(m_Pitch));
    front.z = cos(glm::radians(m_Pitch)) * glm::sin(glm::radians(m_Yaw));

    m_Front = glm::normalize(front);
    m_Right = glm::normalize(glm::cross(m_Front, m_WordUp));
    m_Up    = glm::normalize(glm::cross(m_Right, m_Front));
}