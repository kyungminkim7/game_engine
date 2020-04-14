#version 330 core
layout (location = 0) in vec3 vertexPosition;

layout (std140) uniform Matrices {
    mat4 view;
    mat4 projection;
};

out vec3 fragTextureCoordinates;

void main(void)
{
    vec4 position = projection * view * vec4(vertexPosition, 1.0);
    gl_Position = position.xyww;

    fragTextureCoordinates = vertexPosition;
}
