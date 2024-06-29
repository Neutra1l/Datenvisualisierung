#ifndef HORIZONTALSTREAMLINEMAPPER_H
#define HORIZONTALSTREAMLINEMAPPER_H

class HorizontalStreamlineMapper
{
public:
    HorizontalStreamlineMapper();
    ~HorizontalStreamlineMapper();

private:
    float *dataSlice;
    int xs;
    int ys;
    int zPosition;
    bool eulerMethodChosen;
    float delta;
};

#endif // HORIZONTALSTREAMLINEMAPPER_H
