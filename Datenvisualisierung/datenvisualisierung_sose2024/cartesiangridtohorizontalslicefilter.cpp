#include "cartesiangridtohorizontalslicefilter.h"
#include "flowdatasource.h"
#include "horizontalslicetoimagemapper.h"

#include <iostream>

CartesianGridToHorizontalSliceFilter::CartesianGridToHorizontalSliceFilter(){}

int CartesianGridToHorizontalSliceFilter::getSlice()
{
    return slice;
}
void CartesianGridToHorizontalSliceFilter::setSlice(int iz)
{
    slice = iz;
}

void CartesianGridToHorizontalSliceFilter::setWindComponent(int ic)
{
    windComponent = ic;
}
int CartesianGridToHorizontalSliceFilter::getCurrentWindComponent()
{
    return windComponent;
}

void CartesianGridToHorizontalSliceFilter::setDataSource(float *flowdatasource)
{
    datenQuelle = flowdatasource;
}
void CartesianGridToHorizontalSliceFilter::setMagnitude(float* magnitude)
{
    this->magnitude = magnitude;
}

float* CartesianGridToHorizontalSliceFilter::transferAllData(int xs,int ys, int zs)
{
    return datenQuelle;
}

float* CartesianGridToHorizontalSliceFilter::transferDataToMapper(int xs, int ys)
{

    float *dataSlice = new float[xs*ys];
    for (int i = 0; i<ys;i++)   //y-achse
    {
        for(int j = 0; j<xs;j++) //x-achse
        {
            //*dataSlice++ = datenQuelle[(xs*ys*slice+ xs*i+j)*3+windComponent];
            dataSlice[xs*i+j] = datenQuelle[(xs*ys*slice+ xs*i+j)*3+windComponent];
        }
    }
    return dataSlice;
}
float* CartesianGridToHorizontalSliceFilter::transferMagnitudeOfCurrentSliceToMapper(int xs, int ys)
{
    float *magnitudeOfCurrentSlice = new float[xs*ys];
    for(int i = 0; i <xs*ys; i++)
    {
       magnitudeOfCurrentSlice[i] = magnitude[slice*xs*ys+i];
    }

    return magnitudeOfCurrentSlice;
}
void CartesianGridToHorizontalSliceFilter::moveSlice(int steps)
{
    slice += steps;
}
void CartesianGridToHorizontalSliceFilter::changeWindComponent(int ic)
{
    windComponent = ic;
}



