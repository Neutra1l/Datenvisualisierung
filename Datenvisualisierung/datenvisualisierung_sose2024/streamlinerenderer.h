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
    void setValues(int seeds);
    void draw(QMatrix4x4 mvpMatrix);
    void render(QVector<QVector3D> vectors, QMatrix4x4 mvpMatrix);
private:
    StreamlineMapper *streamlineMapper;
    QOpenGLShaderProgram shaderProgram;
    QOpenGLBuffer vertexBuffer;
    QOpenGLVertexArrayObject vertexArrayObject;
    int zPosition;

    int num_seeds;



    void initOpenGLShaders();
    void initStreamlineGeometry();
};

#endif // STREAMLINERENDERER_H
