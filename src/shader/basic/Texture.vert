#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUv;

out vec2 ioUv;

void main()
{
    ioUv = aUv;
    gl_Position = vec4(aPos, 1.0);
}