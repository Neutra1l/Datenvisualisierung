#include "opengldisplaywidget.h"

#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <iostream>
#include "math.h"
#include <QOpenGLShader>
#include "flowdatasource.h"
#include "cartesiangridtohorizontalslicefilter.h"
#include "horizontalslicerenderer.h"
#include "horizontalslicetoimagemapper.h"


OpenGLDisplayWidget::OpenGLDisplayWidget(QWidget *parent)
    : QOpenGLWidget(parent),
      distanceToCamera(-8.0)
{
    setFocusPolicy(Qt::StrongFocus);
}


OpenGLDisplayWidget::~OpenGLDisplayWidget()
{
    // Clean up visualization pipeline.
    delete bboxRenderer;
    delete sliceRenderer;
    delete mapper;
    delete flowdatasource;
    delete sliceFilter;

}


QString OpenGLDisplayWidget::openGLString()
{
    QString profileStr;
    switch (format().profile())
    {
    case QSurfaceFormat::NoProfile:
        profileStr = "no profile";
        break;
    case QSurfaceFormat::CompatibilityProfile:
        profileStr = "compatibility profile";
        break;
    case QSurfaceFormat::CoreProfile:
        profileStr = "core profile";
        break;
    }

    return QString("%1.%2 (%3)").arg(format().majorVersion())
            .arg(format().minorVersion()).arg(profileStr);
}


void OpenGLDisplayWidget::initializeGL()
{
    // Query and display some information about the used OpenGL context.
    std::cout << "Initializing OpenGLDisplayWidget with OpenGL version "
              <<  openGLString().toStdString() << ".\n" << std::flush;

    // Set the backgound color of the OpenGL display enable the depth buffer.
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClearColor(255, 255, 255, 1);
    f->glEnable(GL_DEPTH_TEST);

    // Our own initialization of the visualization pipeline.
    initVisualizationPipeline();
}


void OpenGLDisplayWidget::resizeGL(int w, int h)
{
    // Calculate aspect ratio of the current viewport.
    float aspectRatio = float(w) / std::max(1, h);

    // Reset projection and set new perspective projection.
    projectionMatrix.setToIdentity();
    projectionMatrix.perspective(45.0, aspectRatio, 0.05, 25.0);

    // Update model-view-projection matrix with new projection.
    updateMVPMatrix();
}


void OpenGLDisplayWidget::paintGL()
{
    // Clear color and depth buffer.
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Call renderer modules.
    bboxRenderer->drawBoundingBox(mvpMatrix);
    sliceRenderer->drawImage(mvpMatrix);

    // ....
}


void OpenGLDisplayWidget::mousePressEvent(QMouseEvent *e)
{
    // Save the current position of the mouse pointer for subsequent use
    // in mouseMoveEvent().
    lastMousePosition = QVector2D(e->localPos());
}


void OpenGLDisplayWidget::mouseMoveEvent(QMouseEvent *e)
{
    // If the user holds the left mouse button while moving the mouse, update
    // the rotation angles that specify from which side the grid visualization
    // is viewed.
    if (e->buttons() & Qt::LeftButton)
    {
        // Vector that points from the last stored position of the mouse
        // pointer to the current position.
        QVector2D mousePosDifference = QVector2D(e->localPos()) - lastMousePosition;

        // Update rotation angles in x and y direction. The factor "10" is an
        // arbitrary scaling constant that controls the sensitivity of the
        // mouse.
        rotationAngles.setX(
                    fmod(rotationAngles.x() + mousePosDifference.x()/10.,
                         360.));
        rotationAngles.setY(
                    fmod(rotationAngles.y() + mousePosDifference.y()/10.,
                         360.));

        // Store current position of mouse pointer for next call to this method.
        lastMousePosition = QVector2D(e->localPos());

        // Update model-view-projection matrix with new rotation angles.
        updateMVPMatrix();

        // Redraw OpenGL.
        update();
    }
}


void OpenGLDisplayWidget::wheelEvent(QWheelEvent *e)
{
    // Update distance of the camera to the rendered visualization. The factor
    // "500" is arbitrary and controls that sensitivity of the mouse.
    distanceToCamera += e->angleDelta().x() / 500.;

    // Update model-view-projection matrix with new distance to camera.
    updateMVPMatrix();

    // Redraw OpenGL.
    update();
}


void OpenGLDisplayWidget::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Up)
    {
        if(sliceFilter->getSlice()<15)
        {
         sliceFilter->moveSlice(1);
         mapper->increaseZPosition(1);
         mapper->setDataSlice(sliceFilter->transferDataToMapper(16,16), 16,16);

        }

    }
    else if (e->key() == Qt::Key_Down)
    {
        if(sliceFilter->getSlice()>0)
        {
            sliceFilter->moveSlice(-1);
            mapper->increaseZPosition(-1);
            mapper->setDataSlice(sliceFilter->transferDataToMapper(16,16), 16,16);

        }

    }
    else if (e->key() == Qt::Key_X)
    {
        if(sliceFilter->getCurrentWindComponent() != 0)
        {
            sliceFilter->changeWindComponent(0);
            mapper->setDataSlice(sliceFilter->transferDataToMapper(16,16), 16,16);
        }

    }
    else if (e->key() == Qt::Key_Y)
    {
        if(sliceFilter->getCurrentWindComponent() != 1)
        {
            sliceFilter->changeWindComponent(1);
            mapper->setDataSlice(sliceFilter->transferDataToMapper(16,16), 16,16);
        }

    }
    else if (e->key() == Qt::Key_Z)
    {
        if(sliceFilter->getCurrentWindComponent() != 2)
        {
            sliceFilter->changeWindComponent(2);
            mapper->setDataSlice(sliceFilter->transferDataToMapper(16,16), 16,16);

        }

    }
    else if(e->key() == Qt::Key_M)
    {
       mapper->setMagnitude(sliceFilter->transferMagnitudeOfCurrentSliceToMapper(16,16));

    }

    // Redraw OpenGL.
    update();
}


void OpenGLDisplayWidget::updateMVPMatrix()
{
    // Calculate a simple model view transformation from rotation angles
    // and distance to camera.
    // NOTE: Read from bottom to top.

    QMatrix4x4 mvMatrix;
    mvMatrix.translate(0.0, 0.0, distanceToCamera);
    mvMatrix.rotate(rotationAngles.y(), QVector3D(1.0, 0.0, 0.0));
    mvMatrix.rotate(rotationAngles.x(), QVector3D(0.0, 1.0, 0.0));
    mvMatrix.translate(-1.0, -1.0, -1.0);
    mvMatrix.scale(2.0);

    mvpMatrix = projectionMatrix * mvMatrix;
}


void OpenGLDisplayWidget::initVisualizationPipeline()
{
    // Initialize the visualization pipeline:

    // Initialize data source(s).
    flowdatasource = new FlowDataSource();
    flowdatasource->createData(16,16,16,0);
    flowdatasource->calculateMagnitudeOfWind();

    // Initialize filter modules.
    sliceFilter = new CartesianGridToHorizontalSliceFilter();
    sliceFilter->setWindComponent(0);
    sliceFilter->setSlice(0);
    sliceFilter->setDataSource(flowdatasource->getDatenQuelle());
    sliceFilter->setMagnitude(flowdatasource->getMagnitude());


    // Initialize mapper modules.
    mapper = new HorizontalSliceToImageMapper();
    mapper->setDataSlice(sliceFilter->transferDataToMapper(16,16), 16,16);
    mapper->setZPosition(sliceFilter->getSlice());

    // Initialize rendering modules.
    bboxRenderer = new DataVolumeBoundingBoxRenderer();
    sliceRenderer = new HorizontalSliceRenderer();
    sliceRenderer->setMapper(mapper);
    sliceRenderer->setZPosition(mapper->getZPosition());

    // ....
}
