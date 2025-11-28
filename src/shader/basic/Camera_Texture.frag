#version 330 core
out vec4 FragColor;

in vec2 ioUv;

uniform sampler2D uSlot;

void main()
{
    FragColor = texture(uSlot, ioUv);
} 