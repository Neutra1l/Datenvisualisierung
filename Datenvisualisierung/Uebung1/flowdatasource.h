#ifndef FLOWDATASOURCE_H
#define FLOWDATASOURCE_H

class FlowDataSource
{
private:
    int xs,ys,zs;
    int time;
    float *dataGrid;
    float *magnitudes;
public:
    FlowDataSource();
    void createData(int xs, int ys, int zs, int time);
    float getDataValue(int iz, int iy, int ix, int ic);
    void printValuesOfHorizontalSlice(int iz, int ic);
    void calculateMagnitudeOfWind();
    void printHighestAndLowestSpeed();
};

#endif // FLOWDATASOURCE_H
