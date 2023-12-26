#version 460 core

uniform vec3 ballColors[30];  // 每个小球的颜色
//uniform bool useTexture[30];   每个小球是否使用纹理
uniform unsigned int ballTextures[30]; //每个小球使用的纹理索引
uniform sampler2D texture1;
uniform sampler2D texture2;

flat in int ballIndex;  // 小球索引
in vec2 TexCoord;

out vec4 FragColor;

void main()
{
//	if(useTexture[ballIndex])
//		FragColor = texture(texture1, TexCoord);
//	else
//		FragColor = vec4(ballColors[ballIndex], 1.0);
//	FragColor = vec4(1.0f,1.0f,1.0f, 1.0);
	if(ballTextures[ballIndex] == 0)
		FragColor = vec4(texture(texture1, TexCoord).rgb * ballColors[ballIndex],1.0f);
	else
		FragColor = vec4(texture(texture2, TexCoord).rgb * ballColors[ballIndex],1.0f);
}