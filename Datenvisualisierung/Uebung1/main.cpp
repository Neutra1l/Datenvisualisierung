#include <QCoreApplication>
#include "flowdatasource.h"
#include <iostream>
using namespace std;
int main()
{
    FlowDataSource objekt;
    objekt.createData(16,16,16,0);
    objekt.printValuesOfHorizontalSlice(0,0);

    //objekt.printHighestAndLowestSpeed();
    //cout << objekt.getDataValue(0,0,0,0) <<endl;
    //cout << objekt.getDataValue(0,0,0,1) <<endl;
    //cout << objekt.getDataValue(0,0,0,2) <<endl;
}
