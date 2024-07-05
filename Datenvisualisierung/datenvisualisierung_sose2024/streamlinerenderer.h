#ifndef STREAMLINERENDERER_H
#define STREAMLINERENDERER_H

#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include "streamlinemapper.h"
class StreamlineRenderer
{
public:
    void drawStreamlines(QMatrix4x4 matrix);
    void setStreamlineMapper(StreamlineMapper *mapper);
    ~StreamlineRenderer();
    StreamlineRenderer();
private:
    StreamlineMapper *streamlineMapper;
    QOpenGLShaderProgram shaderProgram;
    QOpenGLBuffer vertexBuffer;
    QOpenGLVertexArrayObject vertexArrayObject;
    int zPosition;


    void initOpenGLShaders();
    void initStreamlineGeometry();
};

#endif // STREAMLINERENDERER_H
