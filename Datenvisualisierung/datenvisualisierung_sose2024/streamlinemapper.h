#ifndef STREAMLINEMAPPER_H
#define STREAMLINEMAPPER_H

#include <QVector>
#include <QVector3D>
class StreamlineMapper
{
public:
    StreamlineMapper();


    QVector3D rungeKutta4thOrderStep(float a, float b, float c);
    ~StreamlineMapper();
    QVector3D getWindComponentsOfCurrentVertex(int x, int y, int z);
    QVector3D eulerStep(QVector3D currentPoint);

    QVector3D getCoordinatesOfStreamObjects();
    QVector3D bilinearInterpolate();
    QVector3D linearInterpolate();
private:
    float *data;
    float delta;

    bool eulerMethodChosen;
    int xs;
    int ys;
    int zs;
};

#endif // STREAMLINEMAPPER_H
