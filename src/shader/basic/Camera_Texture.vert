#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUv;

out vec2 ioUv;

uniform mat4 uProj;
uniform mat4 uView;
uniform mat4 uModel;

void main()
{
    ioUv = aUv;
    gl_Position = uProj * uView * uModel * vec4(aPos, 1.0);
}