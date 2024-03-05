#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform int selector;
// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;
uniform sampler2D texture4;

void main()
{
	if (selector ==1){
		FragColor = texture(texture1, TexCoord);}
	else if (selector ==2 ){
		FragColor = texture(texture2, TexCoord);}
	else if (selector ==3 ){
		FragColor = texture(texture3, TexCoord);}
	else if (selector ==4 ){
		FragColor = texture(texture4, TexCoord);}
}