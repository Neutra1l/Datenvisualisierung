#ifndef HORIZONTALSLICETOCONTOURLINEMAPPER_H
#define HORIZONTALSLICETOCONTOURLINEMAPPER_H
#include <QVector>
#include <QVector3D>

class HorizontalSliceToContourLineMapper
{
public:
    HorizontalSliceToContourLineMapper();
    QVector<QVector3D> mapSliceToContourLineSegments();

    void setDataSlice(float *dataFromFilter, int x, int y);
    int caseDecider(float a, float b, float c, float d);
    int setZPosition(int z);
    float isoCrossingBetweenVertices(float isoValue, float a, float b);
private:
    float isoValue;
    float *dataSlice;
    float *magnitudes;
    int xs;
    int ys;
    int zPosition;
};

#endif // HORIZONTALSLICETOCONTOURLINEMAPPER_H
