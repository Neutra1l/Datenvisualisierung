#ifndef HORIZONTALSLICETOIMAGEMAPPER_H
#define HORIZONTALSLICETOIMAGEMAPPER_H

#include "cartesiangridtohorizontalslicefilter.h"
#include <QImage>
class HorizontalSliceToImageMapper
{
public:
    HorizontalSliceToImageMapper();
    QImage mapSliceToImage();
    void printDataSlice();
    QImage mapSliceToImage(QString path);
    QImage mapMagnitudeToImage();
    void setDataSlice(float *dataFromFilter, int x, int y);
    void setZPosition(int z);
    void setMagnitude(float* magnitudeFromFilter);

    ~HorizontalSliceToImageMapper();
    void increaseZPosition(int steps);
    int getZPosition();
private:
    float *magnitude;
    float *dataSlice;
    int xs;
    int ys;
    int zPosition;
};


#endif // HORIZONTALSLICETOIMAGEMAPPER_H
