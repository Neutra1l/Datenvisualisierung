#include "streamlinemapper.h"
#include <QVector>
#include <QVector3D>
#include <iostream>
StreamlineMapper::StreamlineMapper() {}
StreamlineMapper::~StreamlineMapper()
{
    std::cout << " Stream line mapper destroyed" << std::endl;
}

QVector3D StreamlineMapper::getCoordinatesOfStreamObjects()
{
    QVector<QVector3D> streamlineCrossingPoints;
    QVector3D v0,v1,v2,v3,v4,v5,v6,v7;

    for(int z=0; z<zs-1;z++)
    {
        for(int y=0; y<ys-1;y++)
        {
            for(int x=0;x<xs-1;x++)
            {
                //"untere" Ebene
                v3 = getWindComponentsOfCurrentVertex(x,y+1,z);
                v2 = getWindComponentsOfCurrentVertex(x+1,y+1,z);
                v1 = getWindComponentsOfCurrentVertex(x+1,y,z);
                v0 = getWindComponentsOfCurrentVertex(x,y,z);
                //"obere" Ebene
                v7 = getWindComponentsOfCurrentVertex(x,y+1,z+1);
                v6 = getWindComponentsOfCurrentVertex(x+1,y+1,z+1);
                v5 = getWindComponentsOfCurrentVertex(x+1,y,z+1);
                v4 = getWindComponentsOfCurrentVertex(x,y,z+1);

                //currentPoint
                QVector3D currentPoint = QVector3D(x,y,z);

                if(eulerMethodChosen)
                {
                    while(currentPoint.x() < x+1 && currentPoint.y() < y+1 && currentPoint.z() < z+1)
                    {
                        QVector3D nextPoint = eulerStep(currentPoint);
                        streamlineCrossingPoints.append(nextPoint);
                        currentPoint=nextPoint;
                    }


                }


            }
        }
    }

}
QVector3D StreamlineMapper::eulerStep(QVector3D currentPoint)
{
    QVector3D nextPoint;
    QVector3D v_xt = getWindComponentsOfCurrentVertex(currentPoint.x(), currentPoint.y(), currentPoint.z());
    nextPoint = currentPoint + delta*v_xt;
    return nextPoint;

}
QVector3D StreamlineMapper::rungeKutta4thOrderStep(float a, float b, float c)
{
    //ToDo
}
QVector3D StreamlineMapper::getWindComponentsOfCurrentVertex(int x, int y, int z)
{
    QVector3D windComponents;
    float xComponent = data[((y*xs+x)+z*xs*ys)];
    float yComponent = data[((y*xs+x)+z*xs*ys+1)];
    float zComponent = data[((y*xs+x)+z*xs*ys+2)];

    windComponents = QVector3D(xComponent, yComponent, zComponent);
    return windComponents;
}
QVector3D StreamlineMapper::bilinearInterpolate()
{

}
QVector3D StreamlineMapper::linearInterpolate( )
{

}










