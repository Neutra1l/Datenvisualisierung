#include "horizontalslicetocontourlinemapper.h"
#include <QVector>
#include <QVector3D>

HorizontalSliceToContourLineMapper::HorizontalSliceToContourLineMapper() {}

QVector<QVector3D> HorizontalSliceToContourLineMapper::mapSliceToContourLineSegments(){
    QVector <QVector3D> contourCrossingPoints;
    QVector3D vector1(0,0,0);
    QVector3D vector2(0.9,0,0);
    QVector3D vector3(0,0,0);
    QVector3D vector4(0,0.9,0);

    contourCrossingPoints << vector1 << vector2 << vector3 << vector4;

    /**
    for(int y = 0; y<ys-1; y++)
    {
        for(int x = 0;x<xs-1;x++)
        {
           float vertex3 = dataSlice[y*xs+x];
           float vertex2 = dataSlice[y*xs+x+1];
           float vertex1 = dataSlice[y*xs+x+1+xs];
           float vertex0 = dataSlice[y*xs+x+xs];

           QVector3D vector1;
           QVector3D vector2;

           int configuration = caseDecider(vertex3, vertex2, vertex1, vertex0);

           /**
            * Wichtig: Benennung alphaxy bedeutet: die Distanz wird berechnet aus der Sicht von Vertex x

           if(configuration == 1 || configuration == 14)
           {
               float alpha30 = isoCrossingBetweenVertices(isoValue, vertex3, vertex0);
               float alpha01 = isoCrossingBetweenVertices(isoValue, vertex0, vertex1);

               vector1 = QVector3D((float)x/16, (float)y/16 + alpha30, zPosition);
               vector2 = QVector3D((float)x/16 + alpha01, (float)y/16, zPosition);

               contourCrossingPoints.append(vector1);
               contourCrossingPoints.append(vector2);
           }
           else if(configuration == 2 || configuration == 13)
           {
               float alpha01 = isoCrossingBetweenVertices(isoValue, vertex0, vertex1);
               float alpha21 = isoCrossingBetweenVertices(isoValue, vertex2, vertex1);

               vector1 = QVector3D((float)x/16 + 1.0, (float)y/16 + alpha21, zPosition);
               vector2 = QVector3D((float)x/16 + alpha01, (float)y/16, zPosition);

               contourCrossingPoints.append(vector1);
               contourCrossingPoints.append(vector2);
           }
           else if(configuration == 3 || configuration == 12)
           {
               float alpha30 = isoCrossingBetweenVertices(isoValue, vertex3, vertex0);
               float alpha21 = isoCrossingBetweenVertices(isoValue, vertex2, vertex1);

               vector1 = QVector3D((float)x/16, (float)y/16 + alpha30, zPosition);
               vector2 = QVector3D((float)x/16, (float)y/16 + alpha21, zPosition);

               contourCrossingPoints.append(vector1);
               contourCrossingPoints.append(vector2);
           }
           else if(configuration == 4 || configuration == 11)
           {
               float alpha32 = isoCrossingBetweenVertices(isoValue, vertex3, vertex2);
               float alpha21 = isoCrossingBetweenVertices(isoValue, vertex2, vertex1);

               vector1 = QVector3D((float)x/16 + alpha32, (float)y/16, zPosition);
               vector2 = QVector3D((float)x/16, (float)y/16 + alpha21, zPosition);

               contourCrossingPoints.append(vector1);
               contourCrossingPoints.append(vector2);
           }
           else if(configuration == 5 || configuration == 10)
           {
               float alpha32 = isoCrossingBetweenVertices(isoValue, vertex3, vertex2);
               float alpha21 = isoCrossingBetweenVertices(isoValue, vertex2, vertex1);
               float alpha30 = isoCrossingBetweenVertices(isoValue, vertex3, vertex0);
               float alpha01 = isoCrossingBetweenVertices(isoValue, vertex0, vertex1);

               vector1 = QVector3D((float)x/16, (float)y/16 + alpha30, zPosition);
               vector2 = QVector3D((float)x/16 + alpha01, (float)y/16, zPosition);

               QVector3D vector3 = QVector3D((float)x/16 + alpha32, (float)y/16, zPosition);
               QVector3D vector4 = QVector3D((float)x/16, (float)y/16 + alpha21, zPosition);

               contourCrossingPoints.append(vector1);
               contourCrossingPoints.append(vector2);
               contourCrossingPoints.append(vector3);
               contourCrossingPoints.append(vector4);

           }
           else if(configuration == 6 || configuration == 10)
           {
               float alpha32 = isoCrossingBetweenVertices(isoValue, vertex3, vertex2);
               float alpha01 = isoCrossingBetweenVertices(isoValue, vertex0, vertex1);

               vector1 = QVector3D((float)x/16 + alpha32, (float)y/16 , zPosition);
               vector2 = QVector3D((float)x/16 + alpha01, (float)y/16, zPosition);

               contourCrossingPoints.append(vector1);
               contourCrossingPoints.append(vector2);
           }
           else if(configuration == 7 || configuration == 9)
           {
               float alpha32 = isoCrossingBetweenVertices(isoValue, vertex3, vertex2);
               float alpha30 = isoCrossingBetweenVertices(isoValue, vertex3, vertex0);

               vector1 = QVector3D((float)x/16, (float)y/16 + alpha30 , zPosition);
               vector2 = QVector3D((float)x/16 + alpha32, (float)y/16, zPosition);

               contourCrossingPoints.append(vector1);
               contourCrossingPoints.append(vector2);
           }
        }
        **/

    return contourCrossingPoints;

}
void HorizontalSliceToContourLineMapper::setDataSlice(float* dataFromFilter,int x, int y)
{
    dataSlice = dataFromFilter;
    xs = x;
    ys = y;
}
int HorizontalSliceToContourLineMapper::caseDecider(float a, float b, float c, float d)
{
    if(a >= 0){a = 1;} else {a = 0;};
    if(b >= 0){b = 1;} else {b = 0;};
    if(c >= 0){c = 1;} else {c = 0;};
    if(d >= 0){d = 1;} else {d = d;};

    return 8*a+4*b+2*c+d;

}
float HorizontalSliceToContourLineMapper::isoCrossingBetweenVertices(float isoValue,float a, float b)
{
    if(a >= 0 && b >= 0 || a < 0 && b < 0)
    {
        return 0;
    }
    else return (isoValue - a)/((b-a) * (float)15);
}
int HorizontalSliceToContourLineMapper::setZPosition(int z)
{
    zPosition = z;
}


