#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} vs_out;

// 144
layout (std140) uniform Camera{
	mat4 view;			// 64	0
	mat4 projection;	// 64	64
	vec3 viewPos;		// 12	128
};
uniform mat4 model;

uniform bool invertedNormals;

void main()
{
    vec4 worldPos = model * vec4(aPos, 1.0);
    vs_out.FragPos = worldPos.xyz; 
    vs_out.TexCoords = aTexCoords;
    
    mat3 normalMatrix = transpose(inverse(mat3(model)));
    vs_out.Normal = normalize(normalMatrix * (invertedNormals ? -aNormal : aNormal));

    gl_Position = projection * view * worldPos;
}