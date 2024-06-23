#version 330
uniform mat4 mvpMatrix;
in vec4 vertexPosition;
#define x vertexPosition.x
#define y vertexPosition.y
void main()
{
 float alpha = -3.141592654;
 vec4 newVertexPosition = vec4(-x * cos(alpha)+ y * sin(alpha), sin(alpha)*x + y*cos(alpha)+1,vertexPosition.z, vertexPosition.w);
// vec4 ultranewVertexPosition = vec4(1.0-vertexPosition.x, )
 //vec4 newVertexPosition = vec4(1-x, 1-y,vertexPosition.z, vertexPosition.w);
 gl_Position = mvpMatrix * newVertexPosition;

}

