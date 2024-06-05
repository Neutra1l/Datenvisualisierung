#include "gen_tornado.c"
using namespace std;

class FlowDataSource{
private:
    inline const static int xs, ys,zs;
    int time;
    float dataGrid [xs*ys*zs*3];
public:
    FlowDataSource(int x, int y, int z,int t)
    {
        xs = x;
        ys = y;
        zs = z;
        time = t;
    }

    #include <math.h>

public:
    gen_tornado(int, int, int,int ,float);
    void createData()
    {
    gen_tornado(16,16,16,time,*dataGrid);
    }

    float getDataValue(int iz, int iy, int ix, int ic)
    {
      int index = ((iz * ys) + iy) * xs + ix;
       return dataGrid[3*index + ic];

    }
    void printValuesOfHorizontalSlice(int iz, int ic)
    {

        for(int i = 0; i < ys; i++)
        {
            for(int i = 0; i<xs; i++)
            {
                int index = ((iz * ys) + iy) * xs + ix;
                cout <<
            }
        }
    }

};
