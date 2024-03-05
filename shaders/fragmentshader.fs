#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float visible;

void main()
{
	if(TexCoord.x >= 0.4){
		FragColor = mix(texture(texture2, TexCoord), vec4(ourColor, 1.0), visible);
	}
	else{
		FragColor = mix(texture(texture1, TexCoord), vec4(ourColor, 1.0), visible);
	}
}
