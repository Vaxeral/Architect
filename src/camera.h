#ifndef CAMERA_H
#define CAMERA_H

#include <cglm/cglm.h>

typedef enum CameraMovement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
}
CameraMovement;

typedef struct Camera
{
    vec3 position;
    vec3 front;
    vec4 up;
    vec3 right;

    float yaw;
    float pitch;

    float speed;
    float sensitivity;
    float zoom;
}
Camera;

Camera cameraCreate(vec3 position, float yaw, float pitch);
void cameraGetViewMatrix(Camera *camera, mat4 dest);
void cameraProcessKeyboard(Camera *camera, CameraMovement direction, float deltaTime);
void cameraProcessMouseMovement(Camera *camera, float xoffset, float yoffset);
void cameraProcessMouseScroll(Camera *camera, float yoffset);

#endif
