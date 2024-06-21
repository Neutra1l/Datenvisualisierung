#include "horizontalslicetocontourlinemapper.h"
#include <QVector>
#include <QVector3D>

HorizontalSliceToContourLineMapper::HorizontalSliceToContourLineMapper() {}

QVector<QVector3D> HorizontalSliceToContourLineMapper::mapSliceToContourLineSegments(){
    QVector <QVector3D> contourCrossingPoints;

    QVector3D vector1 = QVector3D(0,0,0);
    QVector3D vector2 = QVector3D(0.5,0.5,0);
    contourCrossingPoints << vector1 << vector2;

    /**
    for(int y = 0; y<ys-1; y++)
    {
        for(int x = 0;x<xs-1;x++)
        {
            float v0 = dataSlice[xs*y+x];
            float v1 = dataSlice[xs*y+x+1];
            float v2 = dataSlice[y*xs+x+xs+1];
            float v3 = dataSlice[y*xs+x+xs];

            QVector3D p0(x,     y,zPosition/16);
            QVector3D p1(x + 1, y, zPosition/16);
            QVector3D p2(x + 1, y + 1, zPosition/16);
            QVector3D p3(x,     y + 1, zPosition/16);

            int configuration = caseDecider(v3, v2, v1, v0);

            if(configuration == 1 || configuration == 14)
            {
                contourCrossingPoints.append(isoCrossingBetweenVertices(p0, v0, p1, v1, isoValue));
                contourCrossingPoints.append(isoCrossingBetweenVertices(p0, v0, p3, v3, isoValue));
            }
            else if(configuration == 2 || configuration == 13)
            {
                contourCrossingPoints.append(isoCrossingBetweenVertices(p0, v0, p1, v1, isoValue));
                contourCrossingPoints.append(isoCrossingBetweenVertices(p1, v1, p2, v2, isoValue));
            }
            else if(configuration == 3 || configuration == 12)
            {
                contourCrossingPoints.append(isoCrossingBetweenVertices(p0, v0, p3, v3, isoValue));
                contourCrossingPoints.append(isoCrossingBetweenVertices(p1, v1, p2, v2, isoValue));
            }
            else if(configuration == 4 || configuration == 11)
            {
                contourCrossingPoints.append(isoCrossingBetweenVertices(p1, v1, p2, v2, isoValue));
                contourCrossingPoints.append(isoCrossingBetweenVertices(p3, v3, p2, v2, isoValue));
            }
            else if(configuration == 5 || configuration == 10)
            {
                contourCrossingPoints.append(isoCrossingBetweenVertices(p0, v0, p1, v1, isoValue));
                contourCrossingPoints.append(isoCrossingBetweenVertices(p0, v0, p3, v3, isoValue));

                contourCrossingPoints.append(isoCrossingBetweenVertices(p3, v3, p2, v2, isoValue));
                contourCrossingPoints.append(isoCrossingBetweenVertices(p1, v1, p2, v2, isoValue));
            }
            else if(configuration == 6 || configuration == 9)
            {
                contourCrossingPoints.append(isoCrossingBetweenVertices(p0, v0, p1, v1, isoValue));
                contourCrossingPoints.append(isoCrossingBetweenVertices(p3, v3, p2, v2, isoValue));
            }
            else if(configuration == 7 || configuration == 8)
            {
                contourCrossingPoints.append(isoCrossingBetweenVertices(p0, v0, p3, v3, isoValue));
                contourCrossingPoints.append(isoCrossingBetweenVertices(p3, v3, p2, v2, isoValue));
            }
            else continue;

            return contourCrossingPoints;



        }
    }
**/


    /**
    for(int y = 0; y<ys-1; y++)
    {
        for(int x = 0;x<xs-1;x++)
        {

           float vertex0 = dataSlice[y*xs+x];
           float vertex1 = dataSlice[y*xs+x+1];
           float vertex3 = dataSlice[y*xs+x+xs];
           float vertex2 = dataSlice[y*xs+x+xs+1];

           QVector3D vector1;
           QVector3D vector2;

           int configuration = caseDecider(vertex3, vertex2, vertex1, vertex0);


           if(configuration == 1 || configuration == 14)
           {
               float alpha03 = isoCrossingBetweenVertices(isoValue, vertex0, vertex3);
               float alpha01 = isoCrossingBetweenVertices(isoValue, vertex0, vertex1);

               vector1 = QVector3D((float)x/16, (float)y/16 + alpha03, zPosition/16);
               vector2 = QVector3D((float)x/16 + alpha01, (float)y/16, zPosition/16);

               contourCrossingPoints.append(vector1);
               contourCrossingPoints.append(vector2);
           }
           else if(configuration == 2 || configuration == 13)
           {
               float alpha01 = isoCrossingBetweenVertices(isoValue, vertex0, vertex1);
               float alpha12 = isoCrossingBetweenVertices(isoValue, vertex1, vertex2);

               vector1 = QVector3D((float)x/16+alpha01, (float)y/16, zPosition/16);
               vector2 = QVector3D((float)x/16 +1/16, (float)y/16+alpha12, zPosition/16);

               contourCrossingPoints.append(vector1);
               contourCrossingPoints.append(vector2);
           }
           else if(configuration == 3 || configuration == 12)
           {
               float alpha03 = isoCrossingBetweenVertices(isoValue, vertex0, vertex3);
               float alpha12 = isoCrossingBetweenVertices(isoValue, vertex1, vertex2);

               vector1 = QVector3D((float)x/16, (float)y/16 + alpha03, zPosition/16);
               vector2 = QVector3D((float)x/16+1/16, (float)y/16 + alpha12, zPosition/16);

               contourCrossingPoints.append(vector1);
               contourCrossingPoints.append(vector2);
           }
           else if(configuration == 4 || configuration == 11)
           {
               float alpha32 = isoCrossingBetweenVertices(isoValue, vertex3, vertex2);
               float alpha12 = isoCrossingBetweenVertices(isoValue, vertex1, vertex2);

               vector1 = QVector3D((float)x/16 + alpha32, (float)y/16+1/16, zPosition/16);
               vector2 = QVector3D((float)x + 1/16, (float)y/16 + alpha12, zPosition/16);

               contourCrossingPoints.append(vector1);
               contourCrossingPoints.append(vector2);
           }
           else if(configuration == 5 || configuration == 10)
           {
               float alpha32 = isoCrossingBetweenVertices(isoValue, vertex3, vertex2);
               float alpha12 = isoCrossingBetweenVertices(isoValue, vertex1, vertex2);
               float alpha03 = isoCrossingBetweenVertices(isoValue, vertex0, vertex3);
               float alpha01 = isoCrossingBetweenVertices(isoValue, vertex0, vertex1);

               vector1 = QVector3D((float)x/16, (float)y/16 + alpha03, zPosition/16);
               vector2 = QVector3D((float)x/16 + alpha01, (float)y/16, zPosition/16);

               QVector3D vector3 = QVector3D((float)x/16 + alpha32, (float)y/16+1/16, zPosition/16);
               QVector3D vector4 = QVector3D((float)x + 1/16, (float)y/16 + alpha12, zPosition/16);

               contourCrossingPoints.append(vector1);
               contourCrossingPoints.append(vector2);
               contourCrossingPoints.append(vector3);
               contourCrossingPoints.append(vector4);

           }
           else if(configuration == 6 || configuration == 10)
           {
               float alpha32 = isoCrossingBetweenVertices(isoValue, vertex3, vertex2);
               float alpha01 = isoCrossingBetweenVertices(isoValue, vertex0, vertex1);

               vector1 = QVector3D((float)x/16 + alpha32, (float)y/16 + 1/16, zPosition/16);
               vector2 = QVector3D((float)x/16 + alpha01, (float)y/16, zPosition/16);

               contourCrossingPoints.append(vector1);
               contourCrossingPoints.append(vector2);
           }
           else if(configuration == 7 || configuration == 9)
           {
               float alpha32 = isoCrossingBetweenVertices(isoValue, vertex3, vertex2);
               float alpha03 = isoCrossingBetweenVertices(isoValue, vertex0, vertex3);

               vector1 = QVector3D((float)x/16, (float)y/16 + alpha03 , zPosition/16);
               vector2 = QVector3D((float)x/16 + alpha32, (float)y/16 + 1/16, zPosition/16);

               contourCrossingPoints.append(vector1);
               contourCrossingPoints.append(vector2);
           }
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
QVector3D HorizontalSliceToContourLineMapper::isoCrossingBetweenVertices(QVector3D p, float p_val, QVector3D q, float q_val, float iso)
{
    float alpha = (iso - p_val) / (q_val - p_val);
    return (p * (1 - alpha) + q * alpha)/16;
}
int HorizontalSliceToContourLineMapper::setZPosition(int z)
{
    zPosition = z;
}
int HorizontalSliceToContourLineMapper::getZPosition()
{
    return zPosition;
}
void HorizontalSliceToContourLineMapper::setIsoValue(float f)
{
    isoValue = f;
}


