#version 460 core
out vec4 FragColor;

in vec3 position;

uniform vec4 ourColor;

void main()
{
    FragColor = vec4(position, 1.0);
}
