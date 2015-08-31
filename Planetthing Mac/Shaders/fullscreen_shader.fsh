#version 330
uniform sampler2D textureSampler;

in vec2 finalTextureCoord;

out vec4 outputColor;

void main()
{
    outputColor = texture(textureSampler, finalTextureCoord);
}