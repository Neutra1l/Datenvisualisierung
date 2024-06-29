#include "horizontalstreamlinerenderer.h"
#include <iostream>
#include <QOpenGLFunctions>
#include <QOpenGLContext>
HorizontalStreamlineRenderer::HorizontalStreamlineRenderer() {}

void HorizontalStreamlineRenderer::initOpenGLShaders()
{
    // For the contours
    if (!shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                               "lines_vshader_streamline.glsl"))
    {
        std::cout << "Vertex shader error:\n"
                  << shaderProgram.log().toStdString() << "\n" << std::flush;
        return;
    }

    if (!shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                               "lines_fshader_streamline.glsl"))
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


void HorizontalStreamlineRenderer::initContourLinesGeometry()
{

    vertexBuffer.create(); // Make sure to destroy it in the destructor!
}


void HorizontalStreamlineRenderer::drawStreamlines(QMatrix4x4 mvpMatrix)
{
    QVector<QVector3D> streamlines;
    QVector3D v1 = QVector3D(0,0,0);
    QVector3D v2 = QVector3D(0.5,0,0);
    streamlines << v1 << v2;

    vertexBuffer.bind();
    vertexBuffer.allocate(streamlines.data(), streamlines.size() * sizeof(QVector3D));
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
    shaderProgram.setUniformValue("mvpMatrix", mvpMatrix);

    // Issue OpenGL draw commands.
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glLineWidth(5);
    f->glDrawArrays(GL_LINES, 0, streamlines.size());
    // Release objects until next render cycle.
    vertexArrayObject.release();
    shaderProgram.release();
}
