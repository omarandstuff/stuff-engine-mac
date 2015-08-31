#version 330
layout (location = 0) in vec3 positionCoord;

uniform mat4 modelViewProjectionMatrix;

void main()
{
    gl_Position = modelViewProjectionMatrix * vec4(positionCoord, 1.0);
}