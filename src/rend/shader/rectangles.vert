#version 330 core

in vec2 position;
in vec2 texturePosition;

in vec2 offset;
in vec2 size;
in float textureOffset;
in float textureWidth;

out vec2 vTexturePosition;

uniform mat4 projection;
uniform mat4 view;

void main() {
	vec2 originPosition = position * size * 0.5;

   gl_Position = vec4(originPosition + offset, 0.0, 1.0);

	if (position.x < 0.5)	// position.x is 0.0, thus < 0.5
		vTexturePosition.x = abs(textureOffset);
	else					// position.x is 1.0, thus >= 0.5
		vTexturePosition.x = abs(textureOffset) + textureWidth;
	vTexturePosition.y = texturePosition.y;
}