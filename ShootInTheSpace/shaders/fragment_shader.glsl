#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D texture_diffuse1;

void main() {
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(vec3(0.0, 0.0, 10.0) - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);

    vec3 diffuse = diff * vec3(1.0);

    vec3 result = diffuse * texture(texture_diffuse1, TexCoords).rgb;
    FragColor = vec4(result, 1.0);
}
