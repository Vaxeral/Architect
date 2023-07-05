#version 460 core
out vec4 FragColor;

in vec2 texturePosition;

uniform sampler2D texture1;

void main()
{
    FragColor = texture(texture1, texturePosition);
    if (FragColor.a < 1.0)
        discard;
}
