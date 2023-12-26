#version 460 core

uniform bool useTexture;
uniform vec3 color;
uniform sampler2D texture1;

in vec2 TexCoord;

out vec4 FragColor;

void main()
{
	if(useTexture)
		FragColor = texture(texture1, TexCoord);
	else
		FragColor = vec4(color, 1.0);
}
