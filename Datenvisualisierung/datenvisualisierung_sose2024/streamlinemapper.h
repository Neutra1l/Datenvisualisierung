#ifndef STREAMLINEMAPPER_H
#define STREAMLINEMAPPER_H
#include <QVector>
#include <QVector3D>

class StreamlineMapper
{
public:
    StreamlineMapper();
    ~StreamlineMapper();
    void getData(float *source, int x, int y, int z);
    QVector<QVector3D> ComputeStreamlines();
    void SetSourcePoints(float *points, int num);
    float bilinearInterpolation(float x_i, float y_i, int z_slice, int i);
    float trilinearInterpolation(float x_i, float y_i, float z_i, int i);
    QVector3D euler2D(QVector3D coordinate, float deltaT);
    QVector3D euler3D(QVector3D coordinate, float deltaT);
    QVector3D rungeKutta2D(QVector3D coordinate, float deltaT);
    QVector3D rungeKutta3D(QVector3D coordinate, float deltaT);
    void setValues(int seeds, int interpolation_length);
    QVector<QVector<QVector3D>> computeStreamlines();
    int get_num_seeds();
private:
    float* source;
    float* sourcepoints;
    int numPoints;
    int xs, ys, zs;
    int num_seeds;
    int num_steps;
};

#endif // STREAMLINEMAPPER_H
