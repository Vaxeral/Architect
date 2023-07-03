#include "camera.h"

void cameraUpdateVectors(Camera *camera);

Camera cameraCreate(vec3 position, float yaw, float pitch)
{
    Camera camera;
    glm_vec3_copy(position, camera.position);
    camera.yaw = yaw;
    camera.pitch = pitch;
    camera.sensitivity = 0.1;
    camera.zoom = 45.0;
    camera.speed = 2.5;
    cameraUpdateVectors(&camera);
    return camera;
}
void cameraGetViewMatrix(Camera *camera, mat4 dest)
{
    vec3 target;
    glm_vec3_add(camera->position, camera->front, target);
    glm_lookat(camera->position, target, (vec3){0.0, 1.0, 0.0}, dest);
}
void cameraUpdateVectors(Camera *camera)
{
    float yaw = camera->yaw * M_PI / 180.0;
    float pitch = camera->pitch * M_PI / 180.0;
    camera->front[0] = cos(yaw) * cos(pitch);
    camera->front[1] = sin(pitch);
    camera->front[2] = sin(yaw) * cos(pitch);
    glm_vec3_normalize(camera->front);
    glm_vec3_cross(camera->front, (vec3){0.0, 1.0, 0.0}, camera->right);
    glm_vec3_normalize(camera->right);
    glm_vec3_cross(camera->right, camera->front, camera->up);
}
void cameraProcessKeyboard(Camera *camera, CameraMovement direction, float deltaTime)
{
    float velocity = camera->speed * deltaTime;
    vec3 movement;
    if (direction == FORWARD)
    {
        glm_vec3_scale(camera->front, velocity, movement);
        glm_vec3_add(camera->position, movement, camera->position);
    }
    if (direction == BACKWARD)
    {
        glm_vec3_scale(camera->front, velocity, movement);
        glm_vec3_sub(camera->position, movement, camera->position);
    }
    if (direction == LEFT)
    {
        glm_vec3_scale(camera->right, velocity, movement);
        glm_vec3_sub(camera->position, movement, camera->position);
    }
    if (direction == RIGHT)
    {
        glm_vec3_scale(camera->right, velocity, movement);
        glm_vec3_add(camera->position, movement, camera->position);
    }
}
void cameraProcessMouseMovement(Camera *camera, float xoffset, float yoffset)
{
    xoffset *= camera->sensitivity;
    yoffset *= camera->sensitivity;

    camera->yaw += xoffset;
    camera->pitch += yoffset;

    if (camera->pitch > 89.0)
    {
        camera->pitch = 89.0;
    }
    if (camera->pitch < -89.0)
    {
        camera->pitch = -89.0;
    }

    cameraUpdateVectors(camera);
}

void cameraProcessMouseScroll(Camera *camera, float yoffset)
{
    camera->zoom -= (float)yoffset;
    if (camera->zoom < 1.0)
    {
        camera->zoom = 1.0;
    }
    if (camera->zoom > 45.0)
    {
        camera->zoom = 45.0;
    }
}
