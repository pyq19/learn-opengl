#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1; // 采样器1
uniform sampler2D texture2; // 采样器2

void main()
{
    // FragColor = vec4(ourColor, 1.0) * mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
}
