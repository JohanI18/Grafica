#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

uniform float time;

void main()
{
    gl_Position = vec4(aPos.x + (sin(time)*1.8), aPos.y, aPos.z, 2);
    ourColor = aColor;
}
