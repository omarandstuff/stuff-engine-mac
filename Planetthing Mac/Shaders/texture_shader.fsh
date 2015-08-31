#version 330
uniform sampler2D textureSampler;
uniform float opasityComponent;

in vec2 finalTextureCoord;

out vec4 outputColor;

void main()
{
    outputColor = texture(textureSampler, finalTextureCoord);
    //outputColor.a *= opasityComponent;
}
