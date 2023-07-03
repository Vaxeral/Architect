#version 460 core
out vec4 FragColor;

in vec2 texturePosition;
in vec3 fragPos;
in vec3 normal;

uniform sampler2D texture1;

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
};

uniform Light light;

void main()
{
    vec3 lightColor = vec3(1.0, 1.0, 1.0);
    float ambientStrength = 0.1;
    vec3 ambient = light.ambient * texture(texture1, texturePosition).rgb;

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(texture1, texturePosition).rgb;

    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);

    ambient *= attenuation;
    diffuse *= attenuation;

    vec3 result = ambient + diffuse;
    FragColor = vec4(result, texture(texture1, texturePosition).a);
}
