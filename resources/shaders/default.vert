#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec3 aNormal;


out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;  
out vec3 Color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    FragPos = vec3(model * vec4(aPos, 1.0));
    //vec3 objectPos = vec3(model[0][3], model[1][3], model[2][3]);
    //FragPos = objectPos * aPos;
    TexCoord = aTexCoord;
    Normal = mat3(transpose(inverse(model))) * aNormal; 
    Color = aColor;
}