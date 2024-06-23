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
    int caseDecider(float iso,float a, float b, float c, float d);
    int setZPosition(int z);
    int getZPosition();
    void setIsoValue(float f);
    QVector3D isoCrossingBetweenVertices(QVector3D p, float p_val, QVector3D q, float q_val, float iso);
private:
    float isoValue;
    float *dataSlice;
    float *magnitudes;
    int xs;
    int ys;
    int zPosition;
};

#endif // HORIZONTALSLICETOCONTOURLINEMAPPER_H
