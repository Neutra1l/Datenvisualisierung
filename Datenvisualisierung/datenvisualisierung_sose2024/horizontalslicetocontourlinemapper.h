#ifndef HORIZONTALSLICETOCONTOURLINEMAPPER_H
#define HORIZONTALSLICETOCONTOURLINEMAPPER_H
#include "cartesiangridtohorizontalslicefilter.h"
#include <QVector>
#include <QVector3D>

class HorizontalSliceToContourLineMapper
{
public:
    HorizontalSliceToContourLineMapper();
    QVector<QVector3D> mapSliceToContourLineSegments();

    void setDataSlice(float *dataFromFilter, int x, int y);
    int caseDecider(float iso,float a, float b, float c, float d);
    int getZPosition();
    void setIsoValue(float f [3]);
    float isoCrossingBetweenVertices(float iso, float a, float b);
    void setZPosition(int z);
    void incrementZPosition(int steps);
    void setMagnitudes(float* sliceFilter);
    void imageAndMagnitudeSwitch(bool a);
    ~HorizontalSliceToContourLineMapper();
private:
    float *isoValue;
    float *dataSlice;
    float *magnitudes;
    bool magnitude;
    int xs;
    int ys;
    int zPosition;
};

#endif // HORIZONTALSLICETOCONTOURLINEMAPPER_H
