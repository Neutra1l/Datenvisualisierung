#include "horizontalslicetoimagemapper.h"
#include "cartesiangridtohorizontalslicefilter.h"
#include <QImage>
#include <iostream>

HorizontalSliceToImageMapper::HorizontalSliceToImageMapper() {

}

HorizontalSliceToImageMapper::~HorizontalSliceToImageMapper()
{
    std::cout << "Mapper destroyed" << std::endl;
    std::cout << static_cast<float>(1)/6;
}
QImage HorizontalSliceToImageMapper::mapSliceToImage()
{
    QImage img(xs,ys,QImage::Format_RGB32);

    for(int i = 0; i<ys; i++)
    {
        for(int j = 0;j<xs;j++)
        {
            if(magnitude == false)
            {
             float pixelValue = dataSlice[i*xs+j];
             if(pixelValue>0)
             {
                img.setPixelColor(j,i,QColor(0,0,int(pixelValue*255*3)));
             }
             else
             {
                img.setPixelColor(j,i,QColor(int(pixelValue*(-255)*3),0,0));
             }
            }
            else
            {
                float pixelValue = magnitudes[i*xs+j];
                if(pixelValue>0)
                {
                    img.setPixelColor(j,i,QColor(0,0,int(pixelValue*255*3)));
                }
                else
                {
                    img.setPixelColor(j,i,QColor(int(pixelValue*(-255)*3),0,0));
                }

            }

        }
    }
    return img;
}


QImage HorizontalSliceToImageMapper::mapSliceToImage(QString path)
{
    QImage img;
    img.load(path);
    return img;
}
void HorizontalSliceToImageMapper::setDataSlice(float* dataFromFilter,int x, int y)
{

    dataSlice = dataFromFilter;
    xs = x;
    ys = y;
}
void HorizontalSliceToImageMapper::setMagnitude(float* magnitudeFromFilter)
{
    magnitudes = magnitudeFromFilter;
}
void HorizontalSliceToImageMapper::setZPosition(int z)
{
    zPosition = z;
}
void HorizontalSliceToImageMapper::increaseZPosition(int steps)
{
    zPosition += steps;
}
int HorizontalSliceToImageMapper::getZPosition()
{
    return zPosition;
}
void HorizontalSliceToImageMapper::imageAndMagnitudeSwitch(bool a)
{
    magnitude = a;
}

