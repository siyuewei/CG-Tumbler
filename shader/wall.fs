#version 460 core

in VS_OUT {
    vec2 TexCoords;
    vec3 Normal;
    vec3 FragPos;
    vec4 FragPosLightSpace;
} fs_in;

uniform bool useTexture;
uniform vec3 color;
uniform sampler2D texture1;
uniform sampler2D shadowMap;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

out vec4 FragColor;


float ShadowCalculation(vec4 fragPosLightSpace)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // check whether current frag pos is in shadow
    float shadow = currentDepth > closestDepth  ? 1.0 : 0.0;

    return shadow;
}

void main()
{
    //ambient
    float ambient_coefficient = 0.1;
    vec3 ambient = lightColor * ambient_coefficient;
    vec3 normal = normalize(fs_in.Normal);

    //diffuse
    float diffuse_coefficient = 1;
    vec3 lightDir = normalize(lightPos - fs_in.FragPos);
    vec3 diffuse = lightColor * max(0,dot(normal,lightDir)) * diffuse_coefficient;

    //specular
    float specular_coefficient = 0.5;
    vec3 viewDir = normalize(viewPos - fs_in.FragPos);
    vec3 reflect = reflect(-lightDir,normal);
    vec3 specular = lightColor * pow(max(0,dot(viewDir,reflect)),32) * specular_coefficient;

    vec3 objectColor = texture(texture1, fs_in.TexCoords).rgb;
    if(!useTexture)
		objectColor = color;

    float shadow = ShadowCalculation(fs_in.FragPosLightSpace); 
    vec3 lighting = (ambient + (1 -shadow) * (diffuse + specular)) * objectColor;

    FragColor = vec4(lighting, 1.0);
}
