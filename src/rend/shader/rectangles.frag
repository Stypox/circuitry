#version 330 core

in vec2 vTexturePosition;

out vec4 outColor;

uniform sampler2D rectanglesTexture;

void main() {
    outColor = texture(rectanglesTexture, vTexturePosition);
}