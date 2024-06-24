#include "horizontalslicetocontourlinemapper.h"
#include "cartesiangridtohorizontalslicefilter.h"
#include <QVector>
#include <QVector3D>
#include <iostream>
#define zNorm (float)zPosition/16

HorizontalSliceToContourLineMapper::HorizontalSliceToContourLineMapper() {}
HorizontalSliceToContourLineMapper::~HorizontalSliceToContourLineMapper()
{
    std::cout << " Contour mapper destroyed" << std::endl;
}

QVector<QVector3D> HorizontalSliceToContourLineMapper::mapSliceToContourLineSegments(){
    QVector <QVector3D> contourCrossingPoints;
    QVector3D vector2;
    QVector3D vector1;
    int configuration = 0; // Initialization to avoid any dumb random value being assigned
    float v0, v1, v2, v3;
    float x_value, y_value;
    for(int k = 0; k < 3; k++)
    {
        float iso = isoValue[k];
        for (int y=0; y< ys-1; y++) {
            for (int x=0; x< xs-1; x++) {
                if(magnitude == false){
                v3 = dataSlice[((y+1)*xs+x)];
                v2 = dataSlice[((y+1)*xs+x+1)];
                v1 = dataSlice[(y*xs+x+1)];
                v0 = dataSlice[(y*xs+x)];
                }
                else{
                    v3 = magnitudes[((y+1)*xs+x)];
                    v2 = magnitudes[((y+1)*xs+x+1)];
                    v1 = magnitudes[(y*xs+x+1)];
                    v0 = magnitudes[(y*xs+x)];
                }

                configuration = caseDecider(iso, v0, v1, v2, v3);

                if (configuration==1 || configuration==14) {

                    x_value = float(x)/(xs-1);
                    y_value = float(y)/(ys-1)+isoCrossingBetweenVertices(iso, v3,v0);
                    vector1 = QVector3D(x_value,y_value,zNorm);

                    x_value = float(x)/(xs-1)+isoCrossingBetweenVertices(iso, v1,v0);
                    y_value = float(y)/(ys-1);
                    vector2 = QVector3D(x_value, y_value,zNorm);


                } else if (configuration==2 || configuration==13) {

                    x_value = float(x+1)/(xs-1);
                    y_value = float(y)/(ys-1)+isoCrossingBetweenVertices(iso, v2,v1);
                    vector1 = QVector3D(x_value,y_value,zNorm);

                    x_value = float(x)/(xs-1)+isoCrossingBetweenVertices(iso, v1,v0);
                    y_value = float(y)/(ys-1);
                    vector2 = QVector3D(x_value, y_value,zNorm);


                } else if (configuration==3 || configuration==12) {
                    x_value = float(x)/(xs-1);
                    y_value = float(y)/(ys-1)+isoCrossingBetweenVertices(iso, v3,v0);
                    vector1 = QVector3D(x_value,y_value,zNorm);

                    x_value = float(x+1)/(xs-1);
                    y_value = float(y)/(ys-1)+isoCrossingBetweenVertices(iso, v2,v1);
                    vector2 = QVector3D(x_value,y_value,zNorm);

                } else if (configuration==4 || configuration==11) {

                    x_value = float(x+1)/(xs-1);
                    y_value = float(y)/(ys-1)+isoCrossingBetweenVertices(iso, v2,v1);
                    vector1 = QVector3D(x_value, y_value, zNorm);

                    x_value = float(x)/(xs-1)+isoCrossingBetweenVertices(iso, v2,v3);
                    y_value = float(y+1)/(ys-1);
                    vector2 = QVector3D(x_value,y_value,zNorm);

                } else if (configuration==5) {

                    if (0.25*(v0+v1+v2+v3)>iso) {
                        vector1 = QVector3D(float(x+1)/(xs-1),float(y)/(ys-1)+(iso-v1)/((ys-1)*(v2-v1)),zNorm);
                        vector2 = QVector3D(float(x)/(xs-1)+(iso-v3)/((xs-1)*(v2-v3)),float(y+1)/(ys-1),zNorm);
                        contourCrossingPoints << vector1 << vector2;
                        vector1 = QVector3D(float(x)/(xs-1),float(y)/(ys-1)+(iso-v0)/((ys-1)*(v3-v0)),zNorm);
                        vector2 = QVector3D(float(x)/(xs-1)+(iso-v0)/((xs-1)*(v1-v0)),float(y)/(ys-1),zNorm);

                    } else {
                        vector1 = QVector3D(float(x)/(xs-1)+isoCrossingBetweenVertices(iso, v2,v3),float(y+1)/(ys-1),zNorm);
                        vector2 = QVector3D(float(x)/(xs-1),float(y)/(ys-1)+isoCrossingBetweenVertices(iso, v3,v0),zNorm);
                        contourCrossingPoints << vector1 << vector2;
                        vector1 = QVector3D(float(x+1)/(xs-1),float(y)/(ys-1)+isoCrossingBetweenVertices(iso, v2,v3),zNorm);
                        vector2 = QVector3D(float(x)/(xs-1)+isoCrossingBetweenVertices(iso, v1,v0),float(y)/(ys-1),zNorm);

                    }
                } else if (configuration==10) {

                    if (0.25*(v0+v1+v2+v3)>iso) {
                        vector1 = QVector3D(float(x)/(xs-1)+isoCrossingBetweenVertices(iso, v2,v3),float(y+1)/(ys-1),zNorm);
                        vector2 = QVector3D(float(x)/(xs-1),float(y)/(ys-1)+isoCrossingBetweenVertices(iso, v3,v0),zNorm);
                        contourCrossingPoints << vector1 << vector2;
                        vector1 = QVector3D(float(x+1)/(xs-1),float(y)/(ys-1)+isoCrossingBetweenVertices(iso, v2,v3),zNorm);
                        vector2 = QVector3D(float(x)/(xs-1)+isoCrossingBetweenVertices(iso, v1,v0),float(y)/(ys-1),zNorm);

                    } else {

                        vector1 = QVector3D(float(x+1)/(xs-1),float(y)/(ys-1)+isoCrossingBetweenVertices(iso, v2,v1),zNorm);
                        vector2 = QVector3D(float(x)/(xs-1)+isoCrossingBetweenVertices(iso, v2,v3),float(y+1)/(ys-1),zNorm);
                        contourCrossingPoints << vector1 << vector2;
                        vector1 = QVector3D(float(x)/(xs-1),float(y)/(ys-1)+isoCrossingBetweenVertices(iso, v3,v0),zNorm);
                        vector2 = QVector3D(float(x)/(xs-1)+isoCrossingBetweenVertices(iso, v1,v0),float(y)/(ys-1),zNorm);
                    }

                } else if (configuration==6 || configuration==9) {

                    vector1 = QVector3D(float(x)/(xs-1)+isoCrossingBetweenVertices(iso, v1,v0),float(y)/(ys-1),zNorm);
                    vector2 = QVector3D(float(x)/(xs-1)+isoCrossingBetweenVertices(iso, v2,v3),float(y+1)/(ys-1),zNorm);

                } else if (configuration==7 || configuration==8) {
                    vector1 = QVector3D(float(x)/(xs-1)+isoCrossingBetweenVertices(iso, v2,v3) ,float(y+1)/(ys-1),zNorm);
                    vector2 = QVector3D(float(x)/(xs-1),float(y)/(ys-1)+isoCrossingBetweenVertices(iso, v3,v0),zNorm);
                } else continue;

                contourCrossingPoints << vector1 << vector2;
            }
        }
    }
    return contourCrossingPoints;
}
float HorizontalSliceToContourLineMapper::isoCrossingBetweenVertices(float iso, float a, float b)
{
    return (iso-b)/((xs-1)*(a-b));
}
void HorizontalSliceToContourLineMapper::setDataSlice(float* dataFromFilter,int x, int y)
{
    dataSlice = dataFromFilter;
    xs = x;
    ys = y;
}
int HorizontalSliceToContourLineMapper::caseDecider(float iso, float a, float b, float c, float d)
{
    int v0, v1, v2, v3;
    if(a >= iso){v0 = 1;} else {v0 = 0;};
    if(b >= iso){v1 = 1;} else {v1 = 0;};
    if(c >= iso){v2 = 1;} else {v2 = 0;};
    if(d >= iso){v3 = 1;} else {v3 = d;};

    return v0+2*v1+4*v2+8*v3;

}

void HorizontalSliceToContourLineMapper::setZPosition(int z)
{
    zPosition = z;
}
int HorizontalSliceToContourLineMapper::getZPosition()
{
    return zPosition;
}
void HorizontalSliceToContourLineMapper::setIsoValue(float *f)
{
    isoValue = f;
}
void HorizontalSliceToContourLineMapper::incrementZPosition(int steps)
{
    zPosition += steps;
}
void HorizontalSliceToContourLineMapper::setMagnitudes(float* magnitudeFromFilter)
{
    magnitudes = magnitudeFromFilter;
}
void HorizontalSliceToContourLineMapper::imageAndMagnitudeSwitch(bool a)
{
    magnitude = a;
}

