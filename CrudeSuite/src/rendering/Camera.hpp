//
//  Camera.hpp
//  openGLWork
//
//  Created by Hervé Schmit-Veiler on 4/24/20.
//  Copyright © 2020 Hervé Schmit-Veiler. All rights reserved.
//

#ifndef CAMERA_H
#define CAMERA_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>


namespace Crude
{
    // Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
    enum Camera_Movement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };

    // Default camera values
    const float YAW         = -90.0f;
    const float PITCH       =  0.0f;
    const float SPEED       =  2.5f;
    const float SENSITIVITY =  0.1f;
    const float ZOOM        =  45.0f;


    // An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
    class Camera
    {
    public:
        // Camera Attributes
        glm::vec3 m_position;
        glm::vec3 m_front;
        glm::vec3 m_up;
        glm::vec3 m_right;
        glm::vec3 m_worldUp;
        // Euler Angles
        float m_yaw;
        float m_pitch;
        // Camera options
        float m_movementSpeed;
        float m_mouseSensitivity;
        float m_fov;
        
        // Constructor with vectors
        Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
        
        // Constructor with scalar values
        Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
        
        // Returns the view matrix calculated using Euler Angles and the LookAt Matrix
        glm::mat4 getViewMatrix();
        
        // Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
        void processKeyboard(Camera_Movement direction, float deltaTime);
        
        // Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
        void processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
        
        // Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
        void processMouseScroll(float yoffset);
        
    private:
        // Calculates the front vector from the Camera's (updated) Euler Angles
        void updateCameraVectors();
    };
    
}
#endif
