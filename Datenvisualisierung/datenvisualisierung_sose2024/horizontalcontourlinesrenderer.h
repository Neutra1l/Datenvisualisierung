#ifndef HORIZONTALCONTOURLINESRENDERER_H
#define HORIZONTALCONTOURLINESRENDERER_H

#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

#include "horizontalslicetocontourlinemapper.h"


class HorizontalContourLinesRenderer
{
public:
    void drawContourLines(QMatrix4x4 matrix);
    void setZPosition(int z);
    void setMapper(HorizontalSliceToContourLineMapper *mapper);
    ~HorizontalContourLinesRenderer();
    HorizontalContourLinesRenderer();
private:
    HorizontalSliceToContourLineMapper *contourMapper;
    QOpenGLShaderProgram shaderProgram;
    QOpenGLBuffer vertexBuffer;
    QOpenGLVertexArrayObject vertexArrayObject;
    int zPosition;
    QVector<QVector3D>* contourLineCuts;

    void initOpenGLShaders();
    void initContourLinesGeometry();

};

#endif // HORIZONTALCONTOURLINESRENDERER_H
