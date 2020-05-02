//
//  Camera.cpp
//  openGLWork
//
//  Created by Hervé Schmit-Veiler on 4/24/20.
//  Copyright © 2020 Hervé Schmit-Veiler. All rights reserved.
//

#include "Camera.hpp"

Crude::Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) : m_front(glm::vec3(0.0f, 0.0f, -1.0f)), m_movementSpeed(SPEED), m_mouseSensitivity(SENSITIVITY), m_fov(FOV)
{
    m_position = position;
    m_worldUp = up;
    m_yaw = yaw;
    m_pitch = pitch;
    updateCameraVectors();
}
// Constructor with scalar values
Crude::Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : m_front(glm::vec3(0.0f, 0.0f, -1.0f)), m_movementSpeed(SPEED), m_mouseSensitivity(SENSITIVITY), m_fov(FOV)
{
    m_position = glm::vec3(posX, posY, posZ);
    m_worldUp = glm::vec3(upX, upY, upZ);
    m_yaw = yaw;
    m_pitch = pitch;
    updateCameraVectors();
}

// Returns the view matrix calculated using Euler Angles and the LookAt Matrix
glm::mat4 Crude::Camera::getViewMatrix()
{
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

glm::mat4 Crude::Camera::getProjectionMatrix()
{
    switch(m_type)
    {
        case CameraType::ORTHOGRAPHIC:
            return glm::ortho(0.0f, m_frustWidth, 0.0f, m_frustHeight);
            break;
        case CameraType::PERSPECTIVE:
            return glm::perspective(m_fov, m_frustAspectRatio, m_frustNear, m_frustFar);
            break;
    }
}



// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void Crude::Camera::processKeyboard(CameraMovement direction, float deltaTime)
{
    float velocity = m_movementSpeed * deltaTime;
    if (direction == FORWARD)
        m_position += m_front * velocity;
    if (direction == BACKWARD)
        m_position -= m_front * velocity;
    if (direction == LEFT)
        m_position -= m_right * velocity;
    if (direction == RIGHT)
        m_position += m_right * velocity;
}

// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
void Crude::Camera::processMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
    xoffset *= m_mouseSensitivity;
    yoffset *= m_mouseSensitivity;
    
    m_yaw   += xoffset;
    m_pitch += yoffset;
    
    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (m_pitch > 89.0f)
            m_pitch = 89.0f;
        if (m_pitch < -89.0f)
            m_pitch = -89.0f;
    }
    
    // Update m_front, m_right and m_up Vectors using the updated Euler angles
    updateCameraVectors();
}

// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
void Crude::Camera::processZoom(float zoomIncrement)
{
    if (m_fov >= 1.0f && m_fov <= 45.0f)
        m_fov -= zoomIncrement;
    if (m_fov <= 1.0f)
        m_fov = 1.0f;
    if (m_fov >= 45.0f)
        m_fov = 45.0f;
}

void Crude::Camera::setFov(float fov)
{
    m_fov = fov;
}


void Crude::Camera::setFovBounds(float min, float max)
{
    m_minFov = min;
    m_maxFov = max;
}

void Crude::Camera::setProjectionInfo(CameraType type, float width, float height, float near, float far)
{
    m_type = type;
    m_frustWidth = width;
    m_frustHeight = height;
    m_frustAspectRatio = (float)width/(float)height;
    m_frustNear = near;
    m_frustFar = far;
}

// Calculates the front vector from the Camera's (updated) Euler Angles
void Crude::Camera::updateCameraVectors()
{
    // Calculate the new m_front vector
    glm::vec3 front;
    front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    front.y = sin(glm::radians(m_pitch));
    front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_front = glm::normalize(front);
    // Also re-calculate the m_right and m_up vector
    m_right = glm::normalize(glm::cross(m_front, m_worldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    m_up    = glm::normalize(glm::cross(m_right, m_front));
    }
