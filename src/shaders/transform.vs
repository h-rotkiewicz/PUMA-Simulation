#version 330 core

layout (location = 0) in vec3 aPos;      
layout (location = 1) in vec3 aNormal;   
layout (location = 2) in vec2 aTexCoord; 

out vec2 TexCoord; 
out vec3 FragPos;  
out vec3 Normal;   

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 transform;

void main() {
    // Calculate the position of the vertex in world space
    FragPos = vec3(model * vec4(aPos, 1.0));
    
    // Calculate the normal in world space and normalize it
    Normal = mat3(transpose(inverse(model))) * aNormal;
    
    // Pass texture coordinates to the fragment shader
    TexCoord = aTexCoord;
    
    // Calculate the final vertex position in clip space
    gl_Position = projection * view * vec4(FragPos, 1.0);
}
