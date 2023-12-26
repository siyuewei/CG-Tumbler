#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out VS_OUT {
    vec2 TexCoords;
    vec3 Normal;
    vec3 FragPos;
    vec3 FragPosLightSpace;
} vs_out;


uniform mat4 modelMatrixs[5];

layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
    mat4 lightSpaceMatrix;
};

void main()
{
    vs_out.TexCoords = aTexCoords;    
    gl_Position = projection * view * modelMatrixs[gl_InstanceID] * vec4(aPos, 1.0);
    vs_out.Normal = mat3(transpose(inverse(modelMatrixs[gl_InstanceID]))) * aNormal;
	vs_out.FragPos = vec3(modelMatrixs[gl_InstanceID] * vec4(aPos,1.0));
    vs_out.FragPosLightSpace = vec3(lightSpaceMatrix * vec4(vs_out.FragPos, 1.0));
}