#ifndef HORIZONTALSTREAMLINERENDERER_H
#define HORIZONTALSTREAMLINERENDERER_H

#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

#include "horizontalstreamlinemapper.h"
class HorizontalStreamlineRenderer
{
public:
    HorizontalStreamlineRenderer();

    void drawStreamlines(QMatrix4x4 mvpMatrix);
private:
    HorizontalStreamlineMapper *streamlineMapper;
    QOpenGLShaderProgram shaderProgram;
    QOpenGLBuffer vertexBuffer;
    QOpenGLVertexArrayObject vertexArrayObject;
    int zPosition;


    void initOpenGLShaders();
    void initContourLinesGeometry();
};

#endif // HORIZONTALSTREAMLINERENDERER_H
