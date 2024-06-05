#include "horizontalslicetocontourlinemapper.h"
#include <QVector>
#include <QVector3D>
#include <list>
HorizontalSliceToContourLineMapper::HorizontalSliceToContourLineMapper() {}

QVector<QVector3D> HorizontalSliceToContourLineMapper::mapSliceToContourLineSegments(){
    QVector <QVector3D> contourCrossingPoints;

    for(int i = 0; i<ys-1; i++)
    {
        for(int j = 0;j<xs-1;j++)
        {
           float vertex3 = dataSlice[i*xs+j];
           float vertex2 = dataSlice[i*xs+j+1];
           float vertex1 = dataSlice[i*xs+j+1+xs];
           float vertex0 = dataSlice[i*xs+j+xs];

           int configuration = caseDecider(vertex3, vertex2, vertex1, vertex0);


           switch (configuration) {
           case 1:
           case 15:
           {
               float crossPoint30 = abs((0-vertex3)/(vertex0-vertex3));
               float crossPoint10 = abs((0-vertex1)/(vertex0-vertex1));
               QVector3D vector1(crossPoint10, crossPoint30, zPosition);

               contourCrossingPoints.append(vector1);
               break;
           }

            case 2:
            case 14:
            {
                float crossPoint01 = abs((0-vertex1)/(vertex0-vertex1));
                float crossPoint21 = abs((0-vertex1)/(vertex2-vertex1));
                QVector3D vector2(crossPoint01, crossPoint21, zPosition);

                contourCrossingPoints.append(vector2);
                break;
            }



            case 3|13:

           case 4|12:

           case 5|11:

           case 6|10:

           case 7|9:


               // code block
**/
           }
        }
    }

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
int HorizontalSliceToContourLineMapper::setZPosition(int z)
{
    zPosition = z;
}


