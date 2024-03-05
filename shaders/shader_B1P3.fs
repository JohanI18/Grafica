#version 330 core
out vec4 FragColor;

in vec3 ourColor;

uniform float time;

void main()
{    
    FragColor = sin(time)+vec4(ourColor, 0.0f);
}