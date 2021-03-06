#version 330
layout (location = 0) in vec3 positionCoord;
layout (location = 1) in vec2 textureCoord;

uniform mat4 modelViewProjectionMatrix;
uniform vec2 textureCompression;

out vec2 finalTextureCoord;

void main()
{
    gl_Position = modelViewProjectionMatrix * vec4(positionCoord, 1.0);
    finalTextureCoord = textureCoord * textureCompression;
}
