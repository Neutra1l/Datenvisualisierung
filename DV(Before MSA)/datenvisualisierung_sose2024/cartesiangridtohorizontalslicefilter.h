#ifndef CARTESIANGRIDTOHORIZONTALSLICEFILTER_H
#define CARTESIANGRIDTOHORIZONTALSLICEFILTER_H
#include "flowdatasource.h"
#include "horizontalslicetoimagemapper.h"

class CartesianGridToHorizontalSliceFilter
{
public:
    CartesianGridToHorizontalSliceFilter();
    void setSlice(int iz);
    void setWindComponent(int ic);
    void setDataSource(float *flowdatasource);
    float* transferDataToMapper(int xs, int ys);
    int getSlice();
    void moveSlice(int steps);
    void changeWindComponent(int ic);
    void setMagnitude(float *magnitude);
    int getCurrentWindComponent();
    float *transferMagnitudeOfCurrentSliceToMapper(int xs, int ys);
private:
    float* magnitude;
    float* datenQuelle;
    int slice;
    int windComponent;
};

#endif // CARTESIANGRIDTOHORIZONTALSLICEFILTER_H
