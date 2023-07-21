#version 330 core
out vec4 FragColor;

in vec3 TexCoord;  // Changed to vec3

uniform sampler2D texture1;

void main()
{
    FragColor = texture(texture1, TexCoord.xy); // Use .xy swizzle for 2D texture look-up
}
