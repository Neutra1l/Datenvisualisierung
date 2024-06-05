#include "flowdatasource.h"
#include "gen_tornado.c"
#include <iostream>
#include <cmath>

FlowDataSource::FlowDataSource() {}

FlowDataSource::~FlowDataSource()
{
    std::cout << "Hallo" << std::endl;
}

void FlowDataSource::createData(int x, int y, int z, int t)
{
    xs = x;
    ys = y;
    zs = z;
    time = t;
    dataGrid = new float [x*y*z*3];
    gen_tornado(xs,ys,zs,time,dataGrid);
}
float FlowDataSource::getDataValue(int iz, int iy, int ix, int ic)
{
    int index = xs * ys * iz + iy*xs + ix;
    return dataGrid[3*index + ic];
}
void FlowDataSource::printValuesOfHorizontalSlice(int iz, int ic)
{
    for(int i = 0; i<ys; i++)
    {
        for(int j = 0; j<xs; j++)
        {
            std::cout << dataGrid[(xs*ys*iz + i*xs + j)*3+ic] << std::endl;
        }
    }
}
void FlowDataSource::calculateMagnitudeOfWind()
{
    magnitudes = new float[xs*ys*zs];

    for(int z = 0; z<zs; z++)
    {
        for(int y=0; y<ys;y++)
        {

            for(int x = 0; x<xs; x++)
            {
                float xKomponent = dataGrid[(z*xs*ys+y*xs+x)*3];
                float yKomponent = dataGrid[(z*xs*ys+y*xs+x)*3+1];
                float zKomponent = dataGrid[(z*xs*ys+y*xs+x)*3+2];

                float xsquared = pow(xKomponent, 2);
                float ysquared = pow(yKomponent, 2);
                float zsquared = pow(zKomponent, 2);

               // *magnitudes++ = sqrt(xsquared+ysquared+zsquared);
                magnitudes[xs*ys*z+xs*y+x] = sqrt(xsquared+ysquared+zsquared);
            }

        }
    }
}
void FlowDataSource::printHighestAndLowestSpeed()
{
    float maxSpeed = magnitudes[1];
    float minSpeed = magnitudes[0];
    /*
    for(int i = 0; i<xs*ys*zs; i++)
    {
        if(magnitudes[i]<magnitudes[i+1])
        {
            maxSpeed = magnitudes[i+1];
        }
    }
    for(int j = 0; j<xs*ys*zs; j++)
    {
        if(magnitudes[j] > magnitudes[j+1])
        {
            minSpeed = magnitudes[j+1];
        }
    }
    */
    //std::cout << "Höchste Geschwindigkeit beim Zeitschritt 0 beträgt: "  << maxSpeed <<std::endl;
    // std::cout << "Kleinste Geschwindigkeit beim Zeitschritt 0 beträgt: "  << minSpeed <<std::endl;
    std::cout << maxSpeed;
}
float* FlowDataSource::getDatenQuelle()
{
        return dataGrid;
}
float* FlowDataSource::getMagnitude()
{
    return magnitudes;
}
