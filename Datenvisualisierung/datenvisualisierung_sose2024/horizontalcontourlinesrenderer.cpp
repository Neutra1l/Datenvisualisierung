#include "horizontalcontourlinesrenderer.h"
#include <iostream>
#include <QOpenGLFunctions>
#include <QOpenGLContext>
#include <QOpenGLShader>

HorizontalContourLinesRenderer::HorizontalContourLinesRenderer(): vertexBuffer(QOpenGLBuffer::VertexBuffer) {
    initOpenGLShaders();
    initContourLinesGeometry();
}

HorizontalContourLinesRenderer::~HorizontalContourLinesRenderer()
{
    vertexBuffer.destroy();
}

void HorizontalContourLinesRenderer::setMapper(HorizontalSliceToContourLineMapper *mapper)
{
    contourMapper = mapper;
}
void HorizontalContourLinesRenderer::setZPosition(int z)
{
    zPosition = z;
}

void HorizontalContourLinesRenderer::drawContourLines(QMatrix4x4 matrix)
{
    //QVector<QVector3D> isoLineCrossingPoints = contourMapper->mapSliceToContourLineSegments();
    //QImage image2 = (*imageMapper).mapMagnitudeToImage();
    //QImage img = (*imageMapper).mapSliceToImage("uhhlogo.png");
    QVector<QVector3D> isoLineCrossingPoints;

    isoLineCrossingPoints = (*contourMapper).mapSliceToContourLineSegments();

    vertexBuffer.bind();
    vertexBuffer.allocate(isoLineCrossingPoints.constData(), isoLineCrossingPoints.size()*sizeof(QVector3D));
    vertexBuffer.release();

    QOpenGLVertexArrayObject::Binder vaoBinder(&vertexArrayObject);
    if (vertexArrayObject.isCreated())
    {
        vertexBuffer.bind();
        shaderProgram.setAttributeBuffer("vertexPosition", GL_FLOAT, 0, 3, sizeof(QVector3D));
        shaderProgram.enableAttributeArray("vertexPosition");
        vertexBuffer.release();
    }

    // Tell OpenGL to use the shader program of this class.
    shaderProgram.bind();

    // Bind the vertex array object that links to the bounding box vertices.
    vertexArrayObject.bind();

    // Set the model-view-projection matrix as a uniform value.
    shaderProgram.setUniformValue("mvpMatrix",matrix);

    //Issue OpenGL draw commands.
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glLineWidth(5);
    f->glDrawArrays(GL_LINES, 1, isoLineCrossingPoints.size());

    // Release objects until next render cycle.
    vertexArrayObject.release();
    shaderProgram.release();

}

void HorizontalContourLinesRenderer::initOpenGLShaders()
{
    if (!shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                               "lines_vshader.glsl"))
    {
        std::cout << "Vertex shader error:\n"
                  << shaderProgram.log().toStdString() << "\n" << std::flush;
        return;
    }

    if (!shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                               "lines_fshader.glsl"))
    {
        std::cout << "Fragment shader error:\n"
                  << shaderProgram.log().toStdString() << "\n" << std::flush;
        return;
    }

    if (!shaderProgram.link())
    {
        std::cout << "Shader link error:\n"
                  << shaderProgram.log().toStdString() << "\n" << std::flush;
        return;
    }
}

void HorizontalContourLinesRenderer::initContourLinesGeometry()
{
    // Vertices of a unit square that represents the image.


    // Create vertex buffer and upload vertex data to buffer.

    vertexBuffer.create(); // make sure to destroy in destructor!

    /**
    vertexBuffer.bind();
    vertexBuffer.allocate(unitSquareVertices, numVertices * 3 * sizeof(float));
    vertexBuffer.release();
    **/

    // Store the information OpenGL needs for rendering the vertex buffer
    // in a "vertex array object". This can easily be bound to the OpenGL
    // pipeline during rendering.
    /**
    QOpenGLVertexArrayObject::Binder vaoBinder(&vertexArrayObject);
    if (vertexArrayObject.isCreated())
    {
        vertexBuffer.bind();
        shaderProgram.setAttributeBuffer("vertexPosition", GL_FLOAT, 0, 3, 3*sizeof(float));
        shaderProgram.enableAttributeArray("vertexPosition");
        vertexBuffer.release();
    }
    **/
}
