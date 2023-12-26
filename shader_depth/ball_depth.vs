#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

uniform mat4 modelMatrixs[30];
layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
    mat4 lightSpaceMatrix;
};

flat out int ballIndex;  // Ð¡ÇòË÷Òý
out vec2 TexCoord;

void main()
{
	gl_Position = projection * view * modelMatrixs[gl_InstanceID] * vec4(aPos, 1.0);
    ballIndex = gl_InstanceID;
    TexCoord = aTexCoords;
}