#version 330
in vec3 positionCoord;
in vec2 textureCoord;

out vec2 finalTextureCoord;

void main()
{
    gl_Position = vec4(positionCoord, 1.0);
    finalTextureCoord = textureCoord;
}