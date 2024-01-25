#version 460 core
out vec4 FragColor;

in vec2 TexCoords;
uniform sampler2D textureMap;

void main()
{
    vec3 color=texture(textureMap,TexCoords).rgb;
    color=color/(1.0+color);
    color=pow(color,vec3(1.0/2.2));
    FragColor = vec4(color, 1.0);
}