#ifndef HORIZONTALSLICERENDERER_H
#define HORIZONTALSLICERENDERER_H
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

#include "horizontalslicetoimagemapper.h"
class HorizontalSliceRenderer
{
public:
    HorizontalSliceRenderer();
    void setMapper(HorizontalSliceToImageMapper *mapper);
    void drawImage(QMatrix4x4);

    void initImageSliceGeometry();
    ~HorizontalSliceRenderer();
    void moveSlice(int steps);
    void setZPosition(int z);
    int getZPosition();
    void updateZPosition(int steps);
    void incrementZPosition(int steps);
private:
    void initOpenGLShaders();
    void initBoundingBoxGeometry();

    HorizontalSliceToImageMapper *imageMapper;
    QOpenGLShaderProgram shaderProgram;
    QOpenGLBuffer vertexBuffer;
    QOpenGLVertexArrayObject vertexArrayObject;
    int zPosition;
};

#endif // HORIZONTALSLICERENDERER_H
