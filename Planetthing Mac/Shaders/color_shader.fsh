#version 330
uniform vec4 colorComponent;

out vec4 outputColor;

void main()
{
    // Color of the texture by the color component.
    outputColor = colorComponent;
}