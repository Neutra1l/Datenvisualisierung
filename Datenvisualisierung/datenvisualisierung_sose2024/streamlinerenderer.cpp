#include "streamlinerenderer.h"
#include <iostream>
#include <QOpenGLFunctions>
#include <QOpenGLContext>
StreamlineRenderer::StreamlineRenderer():vertexBuffer(QOpenGLBuffer::VertexBuffer)
{
    initOpenGLShaders();
    initStreamlineGeometry();
}
StreamlineRenderer::~StreamlineRenderer() {
    vertexBuffer.destroy();
    std::cout << "Destructor called";
}

void StreamlineRenderer::initOpenGLShaders()
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


void StreamlineRenderer::initStreamlineGeometry()
{

    vertexBuffer.create(); // Make sure to destroy it in the destructor!
}


void StreamlineRenderer::setValues(int seeds) {
    num_seeds = seeds;
}

void StreamlineRenderer::draw(QMatrix4x4 mvpMatrix)
{
    QVector<QVector<QVector3D>> vector_list = streamlineMapper->computeStreamlines();
    for (int i = 0; i<num_seeds; i++) {
        render(vector_list.at(i), mvpMatrix);
    }
}

void StreamlineRenderer::render(QVector<QVector3D> vectors, QMatrix4x4 mvpMatrix) {
    //std::cout << vectors.size() << std::endl;
    vertexBuffer.bind();
    vertexBuffer.allocate(vectors.data(), vectors.size() * sizeof(QVector3D));
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
    f->glLineWidth(10);
    f->glDrawArrays(GL_LINE_STRIP, 0, vectors.size()); // GL_LINES verbindet Vektore paarenweise, wahrend GL_LINE_STRIP jeden Vektor mit seinen 2 Nachbarn im Array verbindet

    // Release objects until next render cycle.
    vertexArrayObject.release();
    shaderProgram.release();
}

void StreamlineRenderer::setStreamlineMapper(StreamlineMapper *streamlineMapper){
    this->streamlineMapper = streamlineMapper;
    num_seeds = streamlineMapper->get_num_seeds();
}
