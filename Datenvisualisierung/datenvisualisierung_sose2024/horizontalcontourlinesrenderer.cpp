#include "horizontalcontourlinesrenderer.h"
#include <QOpenGLFunctions>
#include <QOpenGLContext>
#include <iostream>


HorizontalContourLinesRenderer::HorizontalContourLinesRenderer()
    : vertexBuffer(QOpenGLBuffer::VertexBuffer)
{
    initOpenGLShaders();
    initContourLinesGeometry();
}

HorizontalContourLinesRenderer::~HorizontalContourLinesRenderer()
{
    vertexBuffer.destroy();
}

void HorizontalContourLinesRenderer::setContourMapper(HorizontalSliceToContourLineMapper* mapper) {
    contourMapper = mapper;
}



void HorizontalContourLinesRenderer::initOpenGLShaders()
{
    // For the contours
    if (!shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                               "lines_vshader_contour.glsl"))
    {
        std::cout << "Vertex shader error:\n"
                  << shaderProgram.log().toStdString() << "\n" << std::flush;
        return;
    }

    if (!shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                               "lines_fshader_contour.glsl"))
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

    vertexBuffer.create(); // Make sure to destroy it in the destructor!
}


void HorizontalContourLinesRenderer::drawContourLines(QMatrix4x4 mvpMatrix)
{
    QVector<QVector3D> vectors = contourMapper->mapSliceToContourLineSegments(); //THIS CAUSES THE CRASH

    vertexBuffer.bind();
    vertexBuffer.allocate(vectors.data(), vectors.size() * sizeof(QVector3D)); //the .constData() is from a forum post, very strange, idk what it does... hmm but where can we use data()?
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
    f->glLineWidth(4);
    f->glDrawArrays(GL_LINES, 0, vectors.size()); // GL_LINES verbindet Vektore paarenweise, wahrend GL_LINE_STRIP jeden Vektor mit seinen 2 Nachbarn im Array verbindet

    // Release objects until next render cycle.
    vertexArrayObject.release();
    shaderProgram.release();
}
