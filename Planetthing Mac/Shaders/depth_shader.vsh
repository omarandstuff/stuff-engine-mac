#version 330
in vec4 positionCoord;

uniform mat4 modelViewProjectionMatrix;

void main()
{
    gl_Position = modelViewProjectionMatrix * positionCoord;
}