#version 330
uniform mat4 mvpMatrix;
in vec4 vertexPosition;

smooth out vec2 texCoord;

void main()
{
 gl_Position = mvpMatrix * vertexPosition;
 //texCoord = vertexPosition.xy;
 texCoord = vec2(vertexPosition.x,1-vertexPosition.y);
}

